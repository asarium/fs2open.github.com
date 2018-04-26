//
//

#include "ShipEditorDialogModel.h"

#include <globalincs/linklist.h>
#include <mission/missionmessage.h>
#include <mission/object.h>
#include <mission/util.h>

namespace fso {
namespace fred {
namespace dialogs {

ShipEditorDialogModel::ShipEditorDialogModel(QObject* parent, EditorViewport* viewport) :
	AbstractDialogModel(parent, viewport) {
	initialize_data();
}
bool ShipEditorDialogModel::apply() {
	return true;
}
void ShipEditorDialogModel::reject() {

}
const SCP_string& ShipEditorDialogModel::getShipName() const {
	return m_ship_name;
}
void ShipEditorDialogModel::setShipName(const SCP_string& ship_name) {
	modify(m_ship_name, ship_name);
}

// called to initialize the dialog box to reflect what ships we currently have marked.  Any
// time what we have marked changes, this should get called again.
//
// Notes: player_count is the number of player starts marked, when we are in a non-multiplayer
// mission (NMM).  In a multiplayer mission (MM), player_count will always be zero.
// ship_count in NMM is the number of ships (i.e. not player starts) that are marked.  In MM,
// ship_count is the number of ships and player starts.  Total_count is the sum of ship_count
// and player_count in all cases.  The reason player_count isn't used in MM, and ship_count
// is used instead to track player starts is because in MM, player starts can be edited as
// freely as AI ships, and are very likely to be AI ships sometimes.  Thus, treating them like
// AI ships instead of player starts simplifies processing.
//
void ShipEditorDialogModel::initialize_data()
{
	int mission_type;
	if (The_mission.game_type & MISSION_TYPE_MULTI){
		mission_type = 0;  // multi player mission
	} else {
		mission_type = 1;  // non-multiplayer mission (implies single player mission I guess)
	}

	// figure out what all we are editing.
	auto ship_count = 0;
	auto player_count = 0;
	auto escort_count = 0;
	auto pship_count = 0;
	auto pvalid_count = 0;

	auto base_ship = -1;
	auto base_player = -1;
	auto enable = 1;
	auto p_enable = 1;
	auto objp = GET_FIRST(&obj_used_list);
	while (objp != END_OF_LIST(&obj_used_list)) {
		if ((objp->type == OBJ_SHIP) && (Ships[objp->instance].flags[Ship::Ship_Flags::Escort])){
			escort_count++;  // get a total count of escort ships
		}

		if (objp->type == OBJ_START){
			pship_count++;  // count all player starts in mission
		}

		if (objp->flags[Object::Object_Flags::Marked]) {
			auto type = objp->type;
			if ((type == OBJ_START) && !mission_type){  // in multiplayer missions, starts act like ships
				type = OBJ_SHIP;
			}

			auto i = -1;
			if (type == OBJ_START) {
				player_count++;
				// if player_count is 1, base_player will be the one and only player
				i = base_player = objp->instance;

			} else if (type == OBJ_SHIP) {
				ship_count++;
				// if ship_count is 1, base_ship will be the one and only ship
				i = base_ship = objp->instance;
			}

			if (i >= 0){
				if (Ship_info[Ships[i].ship_info_index].flags[Ship::Info_Flags::Player_ship]){
					pvalid_count++;
				}
			}
		}

		objp = GET_NEXT(objp);
	}

	auto total_count = ship_count + player_count;  // get total number of objects being edited.
	if (total_count > 1){
		multi_edit = true;
	} else {
		multi_edit = false;
	}

	auto a_cue = -1;
	auto d_cue = -1;
	m_arrival_location = -1;
	m_arrival_target = -1;
	m_departure_location = -1;
	m_departure_target = -1;

	auto player_ship = -1;
	auto single_ship = -1;
	auto ship_orders = 0;				// assume they are all the same type
	if (ship_count) {
		box = (CComboBox *) GetDlgItem(IDC_SHIP_CARGO1);
		box->ResetContent();
		for (auto i=0; i<Num_cargo; i++){
			box->AddString(Cargo_names[i]);
		}

		if (!multi_edit) {
			Assert((ship_count == 1) && (base_ship >= 0));
			m_ship_name = Ships[base_ship].ship_name;
		} else {
			m_ship_name = "";
		}

		m_update_arrival = m_update_departure = 1;
		base_player = 0;
		objp = GET_FIRST(&obj_used_list);

		if (multi_edit) {
			m_arrival_tree.clear_tree("");
			m_departure_tree.clear_tree("");
		}

		if (cue_init) {
			m_arrival_tree.load_tree(a_cue);
			m_departure_tree.load_tree(d_cue, "false");

		} else {
			m_arrival_tree.clear_tree();
			m_arrival_tree.DeleteAllItems();
			m_departure_tree.clear_tree();
			m_departure_tree.DeleteAllItems();
		}

		m_player_ship.SetCheck(pship);
		m_no_arrival_warp.SetCheck(no_arrival_warp);
		m_no_departure_warp.SetCheck(no_departure_warp);

		if (!multi_edit) {
			auto i = m_arrival_tree.select_sexp_node;
			if (i != -1) {
				w = GetDlgItem(IDC_ARRIVAL_TREE);
				m_arrival_tree.hilite_item(i);

			} else {
				i = m_departure_tree.select_sexp_node;
				if (i != -1) {
					w = GetDlgItem(IDC_DEPARTURE_TREE);
					m_departure_tree.hilite_item(i);
				}
			}
		}

		m_persona++;
		if (m_persona > 0) {
			int persona_index = 0;
			for (int i = 0; i < m_persona; i++) {
				if (Personas[i].flags & PERSONA_FLAG_WINGMAN)
					persona_index++;
			}
			m_persona = persona_index;
		}

	} else {  // no ships selected, 0 or more player ships selected
		if (player_count > 1) {  // multiple player ships selected
			Assert(base_player >= 0);
			m_ship_name = "";
			m_player_ship.SetCheck(TRUE);
			objp = GET_FIRST(&obj_used_list);
			while (objp != END_OF_LIST(&obj_used_list)) {
				if ((objp->type == OBJ_START) && (objp->flags[Object::Object_Flags::Marked])) {
					auto i = objp->instance;
					if (base_player >= 0) {
						m_ship_class = Ships[i].ship_info_index;
						m_team = Ships[i].team;
						base_player = -1;

					} else {
						if (Ships[i].ship_info_index != m_ship_class)
							m_ship_class = -1;
						if (Ships[i].team != m_team)
							m_team = -1;
					}
				}

				objp = GET_NEXT(objp);
			}

			// only 1 player selected..
		} else if (query_valid_object(_editor->currentObject) && (Objects[_editor->currentObject].type == OBJ_START)) {
			Assert((player_count == 1) && !multi_edit);
			player_ship = Objects[_editor->currentObject].instance;
			m_ship_name = Ships[player_ship].ship_name;
			m_ship_class = Ships[player_ship].ship_info_index;
			m_team = Ships[player_ship].team;
			m_player_ship.SetCheck(TRUE);

		} else {  // no ships or players selected..
			m_ship_name = "";
			m_ship_class = -1;
			m_team = -1;
			m_persona = -1;
			m_player_ship.SetCheck(FALSE);
		}

		m_ai_class = -1;
		m_cargo1 = "";
		m_hotkey = 0;
		m_score.blank();  // cause control to be blank
		m_assist_score.blank();
		m_arrival_location = -1;
		m_departure_location = -1;
		m_arrival_delay.blank();
		m_departure_delay.blank();
		m_arrival_dist.blank();
		m_arrival_target = -1;
		m_departure_target = -1;
		m_arrival_tree.clear_tree();
		m_arrival_tree.DeleteAllItems();
		m_departure_tree.clear_tree();
		m_departure_tree.DeleteAllItems();
		m_no_arrival_warp.SetCheck(0);
		m_no_departure_warp.SetCheck(0);
		enable = p_enable = 0;
		GetDlgItem(IDC_WING)->SetWindowText(_T("None"));
	}

	box = (CComboBox *) GetDlgItem(IDC_ARRIVAL_TARGET);
	// must put the appropriate ships into the list depending on arrival location
	if ( m_arrival_location != ARRIVE_FROM_DOCK_BAY ){
		management_add_ships_to_combo( box, SHIPS_2_COMBO_SPECIAL | SHIPS_2_COMBO_ALL_SHIPS );
	} else {
		management_add_ships_to_combo( box, SHIPS_2_COMBO_DOCKING_BAY_ONLY );
	}

	// set the internal variable appropriatly
	// Goober5000 - gah, this is ridiculous!  Prior to this point in the function (and only in this function),
	// m_arrival_target seems to refer to the arrival anchor.  The rest of the time, it refers to the index
	// of the drop-down list.
	if (m_arrival_target >= 0)
	{
		if (m_arrival_target & SPECIAL_ARRIVAL_ANCHOR_FLAG)
		{
			// figure out what the box represents this as
			char tmp[NAME_LENGTH + 15];
			stuff_special_arrival_anchor_name(tmp, m_arrival_target, 0);

			// find it in the box
			m_arrival_target = box->FindStringExact(-1, tmp);
		}
		else
		{
			// find it in the box
			m_arrival_target = box->FindStringExact(-1, Ships[m_arrival_target].ship_name);
		}
	}

	box = (CComboBox *)GetDlgItem(IDC_DEPARTURE_TARGET);
	// must put the appropriate ships into the list depending on departure location
	if ( m_departure_location == DEPART_AT_DOCK_BAY ){
		management_add_ships_to_combo( box, SHIPS_2_COMBO_DOCKING_BAY_ONLY );
	} else {
		box->ResetContent();
	}

	if ( m_departure_target >= 0 ){
		m_departure_target = box->FindStringExact( -1, Ships[m_departure_target].ship_name );
	}

	initialized = 1;
	if (player_count) {
		box = (CComboBox *) GetDlgItem(IDC_SHIP_TEAM);
		if (!mission_type){  // multiplayer mission
			box->EnableWindow(TRUE);
		}

		else {
			box->EnableWindow(FALSE);
			m_team = -1;
		}

		box->ResetContent();
		for (auto i=0; i<MAX_TVT_TEAMS; i++)
			box->AddString(Iff_info[i].iff_name);
	} else {
		box = (CComboBox *) GetDlgItem(IDC_SHIP_TEAM);
		box->EnableWindow(enable);
		box->ResetContent();
		for (auto i=0; i<Num_iffs; i++){
			box->AddString(Iff_info[i].iff_name);
		}
	}

	m_score.display();
	m_assist_score.display();
	m_arrival_dist.display();
	m_arrival_delay.display();
	m_departure_delay.display();

	if (full_update)
		UpdateData(FALSE);

	if (!cue_init) {
		GetDlgItem(IDC_ARRIVAL_LOCATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_ARRIVAL_DELAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_ARRIVAL_DISTANCE)->EnableWindow(FALSE);
		GetDlgItem(IDC_ARRIVAL_TARGET)->EnableWindow(FALSE);
		GetDlgItem(IDC_ARRIVAL_DELAY_SPIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_ARRIVAL_TREE)->EnableWindow(FALSE);
		GetDlgItem(IDC_DEPARTURE_LOCATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_DEPARTURE_TARGET)->EnableWindow(FALSE);
		GetDlgItem(IDC_DEPARTURE_DELAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_DEPARTURE_DELAY_SPIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_DEPARTURE_TREE)->EnableWindow(FALSE);
		GetDlgItem(IDC_NO_ARRIVAL_WARP)->EnableWindow(FALSE);
		GetDlgItem(IDC_NO_DEPARTURE_WARP)->EnableWindow(FALSE);

		GetDlgItem(IDC_RESTRICT_ARRIVAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_RESTRICT_DEPARTURE)->EnableWindow(FALSE);

	} else {
		GetDlgItem(IDC_ARRIVAL_LOCATION)->EnableWindow(enable);
		if (m_arrival_location) {
			GetDlgItem(IDC_ARRIVAL_DISTANCE)->EnableWindow(enable);
			GetDlgItem(IDC_ARRIVAL_TARGET)->EnableWindow(enable);
		} else {
			GetDlgItem(IDC_ARRIVAL_DISTANCE)->EnableWindow(FALSE);
			GetDlgItem(IDC_ARRIVAL_TARGET)->EnableWindow(FALSE);
		}
		if (m_arrival_location == ARRIVE_FROM_DOCK_BAY) {
			GetDlgItem(IDC_RESTRICT_ARRIVAL)->EnableWindow(enable);
		} else {
			GetDlgItem(IDC_RESTRICT_ARRIVAL)->EnableWindow(FALSE);
		}

		GetDlgItem(IDC_DEPARTURE_LOCATION)->EnableWindow(enable);
		if ( m_departure_location ) {
			GetDlgItem(IDC_DEPARTURE_TARGET)->EnableWindow(enable);
		} else {
			GetDlgItem(IDC_DEPARTURE_TARGET)->EnableWindow(FALSE);
		}
		if (m_departure_location == DEPART_AT_DOCK_BAY) {
			GetDlgItem(IDC_RESTRICT_DEPARTURE)->EnableWindow(enable);
		} else {
			GetDlgItem(IDC_RESTRICT_DEPARTURE)->EnableWindow(FALSE);
		}

		GetDlgItem(IDC_ARRIVAL_DELAY)->EnableWindow(enable);
		GetDlgItem(IDC_ARRIVAL_DELAY_SPIN)->EnableWindow(enable);
		GetDlgItem(IDC_ARRIVAL_TREE)->EnableWindow(enable);
		GetDlgItem(IDC_DEPARTURE_LOCATION)->EnableWindow(enable);
		GetDlgItem(IDC_DEPARTURE_DELAY)->EnableWindow(enable);
		GetDlgItem(IDC_DEPARTURE_DELAY_SPIN)->EnableWindow(enable);
		GetDlgItem(IDC_DEPARTURE_TREE)->EnableWindow(enable);
		GetDlgItem(IDC_NO_ARRIVAL_WARP)->EnableWindow(enable);
		GetDlgItem(IDC_NO_DEPARTURE_WARP)->EnableWindow(enable);
	}

	if (total_count) {
		GetDlgItem(IDC_SHIP_NAME)->EnableWindow(!multi_edit);
		GetDlgItem(IDC_SHIP_CLASS)->EnableWindow(TRUE);
		GetDlgItem(IDC_SHIP_ALT)->EnableWindow(TRUE);
		GetDlgItem(IDC_INITIAL_STATUS)->EnableWindow(TRUE);
		GetDlgItem(IDC_WEAPONS)->EnableWindow(m_ship_class >= 0);
		GetDlgItem(IDC_FLAGS)->EnableWindow(TRUE);
		GetDlgItem(IDC_TEXTURES)->EnableWindow(TRUE);
		GetDlgItem(IDC_ALT_SHIP_CLASS)->EnableWindow(TRUE);
		GetDlgItem(IDC_SPECIAL_EXP)->EnableWindow(TRUE);
		GetDlgItem(IDC_SPECIAL_HITPOINTS)->EnableWindow(TRUE);
	} else {
		GetDlgItem(IDC_SHIP_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_SHIP_CLASS)->EnableWindow(FALSE);
		GetDlgItem(IDC_SHIP_ALT)->EnableWindow(FALSE);
		GetDlgItem(IDC_INITIAL_STATUS)->EnableWindow(FALSE);
		GetDlgItem(IDC_WEAPONS)->EnableWindow(FALSE);
		GetDlgItem(IDC_FLAGS)->EnableWindow(FALSE);
		GetDlgItem(IDC_TEXTURES)->EnableWindow(FALSE);
		GetDlgItem(IDC_ALT_SHIP_CLASS)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPECIAL_EXP)->EnableWindow(FALSE);
		GetDlgItem(IDC_SPECIAL_HITPOINTS)->EnableWindow(FALSE);
	}

	// disable textures for multiple ships
	if (multi_edit)
	{
		GetDlgItem(IDC_TEXTURES)->EnableWindow(FALSE);
	}

	GetDlgItem(IDC_AI_CLASS)->EnableWindow(enable);
	GetDlgItem(IDC_SHIP_CARGO1)->EnableWindow(enable);
	GetDlgItem(IDC_HOTKEY)->EnableWindow(enable);
	if ((m_ship_class >= 0) && !(Ship_info[m_ship_class].flags[Ship::Info_Flags::Cargo]) && !(Ship_info[m_ship_class].flags[Ship::Info_Flags::No_ship_type]))
		GetDlgItem(IDC_GOALS)->EnableWindow(enable);
	else if (multi_edit)
		GetDlgItem(IDC_GOALS)->EnableWindow(enable);
	else
		GetDlgItem(IDC_GOALS)->EnableWindow(FALSE);

	// !pship_count used because if allowed to clear, we would have no player starts
	// mission_type 0 = multi, 1 = single
	if (mission_type || !pship_count || (pship_count + total_count > MAX_PLAYERS) || (pvalid_count < total_count))
		m_player_ship.EnableWindow(FALSE);
	else
		m_player_ship.EnableWindow(TRUE);

	// show the "set player" button only if single player
	if (mission_type)
		GetDlgItem(IDC_SET_AS_PLAYER_SHIP)->ShowWindow(TRUE);
	else
		GetDlgItem(IDC_SET_AS_PLAYER_SHIP)->ShowWindow(FALSE);

	// enable the "set player" button only if single player, single edit, and ship is in player wing
	{
		int marked_ship = (player_ship >= 0) ? player_ship : single_ship;

		if (mission_type && total_count && !multi_edit && wing_is_player_wing(Ships[marked_ship].wingnum))
			GetDlgItem(IDC_SET_AS_PLAYER_SHIP)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_SET_AS_PLAYER_SHIP)->EnableWindow(FALSE);
	}

	GetDlgItem(IDC_DELETE_SHIP)->EnableWindow(enable);
	GetDlgItem(IDC_SHIP_RESET)->EnableWindow(enable);
	GetDlgItem(IDC_SCORE)->EnableWindow(enable);
	GetDlgItem(IDC_ASSIST_SCORE)->EnableWindow(enable);

//#ifndef NDEBUG
	GetDlgItem(IDC_SHIP_TBL)->EnableWindow(m_ship_class >= 0);
//#else
//	GetDlgItem(IDC_SHIP_TBL)->EnableWindow(0);
//	GetDlgItem(IDC_SHIP_TBL)->ShowWindow(SW_HIDE);
//#endif

	if (cue_init > 1) {  // more than one ship (players don't have cues to edit)
		GetDlgItem(IDC_UPDATE_ARRIVAL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_UPDATE_DEPARTURE)->ShowWindow(SW_SHOW);

	} else {
		GetDlgItem(IDC_UPDATE_ARRIVAL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_UPDATE_DEPARTURE)->ShowWindow(SW_HIDE);
	}

	if (multi_edit || (total_count > 1)) {
		// we will allow the ignore orders dialog to be multi edit if all selected
		// ships are the same type.  the ship_type (local) variable holds the ship types
		// for all ships.  Determine how may bits set and enable/diable window
		// as appropriate
		if ( /*(m_team == -1) ||*/ (ship_orders == -1) ){
			GetDlgItem(IDC_IGNORE_ORDERS)->EnableWindow(FALSE);
		} else {
			GetDlgItem(IDC_IGNORE_ORDERS)->EnableWindow(TRUE);
		}
	} else
		// always enabled when one ship is selected
		GetDlgItem(IDC_IGNORE_ORDERS)->EnableWindow(enable);

	// always enabled if >= 1 ship selected
	GetDlgItem(IDC_SHIP_PERSONA)->EnableWindow(enable);

	if (multi_edit){
		SetWindowText("Edit Marked Ships");
	} else if (player_count) {
		SetWindowText("Edit Player Ship");
	} else {
		SetWindowText("Edit Ship");
	}

	// setup alternate name and callsign stuff
	if(player_ship >= 0){
		ship_alt_name_init(player_ship);
		ship_callsign_init(player_ship);
	} else {
		ship_alt_name_init(single_ship);
		ship_callsign_init(single_ship);
	}

	modified = 0;
	if (w){
		w->SetFocus();
	}
}


}
}
}
