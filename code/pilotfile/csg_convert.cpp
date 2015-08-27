
/* WARNING:
 *    This is magic-number central, but these numbers are set specifically
 *    to the acceptable defaults or range values that were used when the
 *    pl2/plr files were created.  Standard game defines should not be used in
 *    place of these major numbers for /any/ reason, *ever*!
 */

#include "cutscene/cutscenes.h"
#include "menuui/techmenu.h"
#include "pilotfile/pilotfile_convert.h"
#include "ship/ship.h"
#include "stats/medals.h"
#include "weapon/weapon.h"

#include <iostream>
#include <sstream>

// copy of old scoring struct  * NORMAL PILOTS *
typedef struct scoring_conv_t {
	int flags;

	int score;
	int rank;
	int medals[18];

	int kills[130];
	int assists;
	int kill_count;
	int kill_count_ok;
	unsigned int p_shots_fired;
	unsigned int s_shots_fired;

	unsigned int p_shots_hit;
	unsigned int s_shots_hit;

	unsigned int p_bonehead_hits;
	unsigned int s_bonehead_hits;
	int bonehead_kills;

	unsigned int missions_flown;
	unsigned int flight_time;
	_fs_time_t last_flown;
	_fs_time_t last_backup;

	// Mission total
	int m_medal_earned;
	int m_badge_earned;
	int m_promotion_earned;

	int m_score;
	int m_kills[130];
	int m_okKills[130];
	int m_kill_count;
	int m_kill_count_ok;
	int m_assists;
	unsigned int mp_shots_fired;
	unsigned int ms_shots_fired;
	unsigned int mp_shots_hit;
	unsigned int ms_shots_hit;
	unsigned int mp_bonehead_hits;
	unsigned int ms_bonehead_hits;
	int m_bonehead_kills;
	int m_player_deaths;

	int m_dogfight_kills[12];
} scoring_conv_t;

static const size_t SCORING_SIZE = 1808;

// copy of old scoring struct  * INFERNO PILOTS *
typedef struct scoring_conv_INF_t {
	int flags;

	int score;
	int rank;
	int medals[18];

	int kills[250];
	int assists;
	int kill_count;
	int kill_count_ok;
	unsigned int p_shots_fired;
	unsigned int s_shots_fired;

	unsigned int p_shots_hit;
	unsigned int s_shots_hit;

	unsigned int p_bonehead_hits;
	unsigned int s_bonehead_hits;
	int bonehead_kills;

	unsigned int missions_flown;
	unsigned int flight_time;
	_fs_time_t last_flown;
	_fs_time_t last_backup;

	// Mission total
	int m_medal_earned;
	int m_badge_earned;
	int m_promotion_earned;

	int m_score;
	int m_kills[250];
	int m_okKills[250];
	int m_kill_count;
	int m_kill_count_ok;
	int m_assists;
	unsigned int mp_shots_fired;
	unsigned int ms_shots_fired;
	unsigned int mp_shots_hit;
	unsigned int ms_shots_hit;
	unsigned int mp_bonehead_hits;
	unsigned int ms_bonehead_hits;
	int m_bonehead_kills;
	int m_player_deaths;

	int m_dogfight_kills[12];
} scoring_conv_INF_t;

static const size_t SCORING_INF_SIZE = 3248;


csg_data::csg_data()
{
	sig = 0;
	cutscenes = 0;

	main_hall = "";
	prev_mission = -1;
	next_mission = -1;
	loop_reentry = 0;
	loop_enabled = 0;
	num_completed = 0;

	last_ship_flown_index = -1;
}

csg_data::~csg_data()
{

}

void pilotfile_convert::csg_import_ships_weapons()
{
	index_list_t ilist;
	char name[35];
	int idx;
	int list_size = 0;

	int ship_count = cfile::io::read<int>(cfp);
	int weap_count = cfile::io::read<int>(cfp);

	for (idx = 0; idx < ship_count; idx++) {
		ubyte allowed = cfile::io::read<ubyte>(cfp);
		csg->ships_allowed.push_back( (allowed != 0) );

		cfile::io::readStringLen(name, sizeof(name), cfp);

		ilist.name = name;
		ilist.index = ship_info_lookup(name);

		if (ilist.index < 0) {
			std::ostringstream error_msg;
			error_msg << "Data mismatch (ship lookup: " << ilist.name << ")!";
			throw std::runtime_error(error_msg.str().c_str());
		}

		csg->ship_list.push_back( ilist );
	}

	for (idx = 0; idx < weap_count; idx++) {
		ubyte allowed = cfile::io::read<ubyte>(cfp);
		csg->weapons_allowed.push_back( allowed != 0 );

		cfile::io::readStringLen(name, sizeof(name), cfp);

		ilist.name = name;
		ilist.index = weapon_info_lookup(name);

		if (ilist.index < 0) {
			std::ostringstream error_msg;
			error_msg << "Data mismatch (weapon lookup: " << ilist.name << ")!";
			throw std::runtime_error(error_msg.str().c_str());
		}

		csg->weapon_list.push_back( ilist );
	}

	// get last ship flown index
	for (idx = 0; idx < ship_count; idx++) {
		if ( csg->ship_list[idx].name.compare(plr->last_ship_flown) == 0 ) {
			csg->last_ship_flown_index = idx;
			break;
		}
	}

	if (csg->last_ship_flown_index < 0) {
		std::ostringstream error_msg;
		error_msg << "Data mismatch (player ship: " << csg->last_ship_flown_index << ")!";
		throw std::runtime_error(error_msg.str().c_str());
	}

	// create list of medals (since it's missing from the old files)
	list_size = Num_medals;

	for (idx = 0; idx < list_size; idx++) {
		ilist.name = Medals[idx].name;
		ilist.index = idx;

		csg->medals_list.push_back( ilist );
	}

	// stuff intel list as well (present but burried in old files)
	list_size = Intel_info_size;

	for (idx = 0; idx < list_size; idx++) {
		ilist.name = Intel_info[idx].name;
		ilist.index = idx;

		csg->intel_list.push_back( ilist );
	}
}

void pilotfile_convert::csg_import_missions(bool inferno)
{
	cmission_conv_t miss;
	int idx, j;
	int count;
	int list_size = 0, k;
	scoring_conv_t t_score;
	scoring_conv_INF_t t_inf_score;

	Assert( sizeof(scoring_conv_t) == SCORING_SIZE );
	Assert( sizeof(scoring_conv_INF_t) == SCORING_INF_SIZE );

	int ship_list_size = (int)csg->ship_list.size();

	int num_missions = cfile::io::read<int>(cfp);

	csg->missions.reserve(num_missions);

	for (idx = 0; idx < num_missions; idx++) {
		miss.index = cfile::io::read<int>(cfp);

		// goals
		count = cfile::io::read<int>(cfp);

		if (count > 0) {
			mgoal n_goal;

			miss.goals.reserve(count);

			for (j = 0; j < count; j++) {
				memset(&n_goal, 0, sizeof(mgoal));

				cfile::io::readStringLen(n_goal.name, sizeof(n_goal.name), cfp);
				n_goal.status = cfile::io::read<char>(cfp);

				miss.goals.push_back( n_goal );
			}
		}

		// events
		count = cfile::io::read<int>(cfp);

		if (count > 0) {
			mevent n_event;

			miss.events.reserve(count);

			for (j = 0; j < count; j++) {
				memset(&n_event, 0, sizeof(mevent));

				cfile::io::readStringLen(n_event.name, sizeof(n_event.name), cfp);
				n_event.status = cfile::io::read<char>(cfp);

				miss.events.push_back( n_event );
			}
		}

		// variables
		count = cfile::io::read<int>(cfp);

		if (count > 0) {
			sexp_variable n_variable;

			miss.variables.reserve(count);

			for (j = 0; j < count; j++) {
				memset(&n_variable, 0, sizeof(sexp_variable));

				n_variable.type = cfile::io::read<int>(cfp);
				cfile::io::readStringLen(n_variable.text, sizeof(n_variable.text), cfp);
				cfile::io::readStringLen(n_variable.variable_name, sizeof(n_variable.variable_name), cfp);

				miss.variables.push_back( n_variable );
			}
		}

		// stats
		miss.stats.ship_kills = csg->ship_list;
		miss.stats.medals_earned = csg->medals_list;

		if (inferno) {
			cfile::io::read(&t_inf_score, sizeof(scoring_conv_INF_t), 1, cfp);

			for (j = 0; j < ship_list_size; j++) {
				miss.stats.ship_kills[j].val = INTEL_INT(t_inf_score.kills[j]);
			}

			miss.stats.score = INTEL_INT(t_inf_score.score);
			miss.stats.rank = INTEL_INT(t_inf_score.rank);
			miss.stats.assists = INTEL_INT(t_inf_score.assists);
			miss.stats.kill_count = INTEL_INT(t_inf_score.kill_count);
			miss.stats.kill_count_ok = INTEL_INT(t_inf_score.kill_count_ok);
			miss.stats.p_shots_fired = INTEL_INT(t_inf_score.p_shots_fired);
			miss.stats.s_shots_fired = INTEL_INT(t_inf_score.s_shots_fired);
			miss.stats.p_shots_hit = INTEL_INT(t_inf_score.p_shots_hit);
			miss.stats.s_shots_hit = INTEL_INT(t_inf_score.s_shots_hit);
			miss.stats.p_bonehead_hits = INTEL_INT(t_inf_score.p_bonehead_hits);
			miss.stats.s_bonehead_hits = INTEL_INT(t_inf_score.s_bonehead_hits);
			miss.stats.bonehead_kills = INTEL_INT(t_inf_score.bonehead_kills);

			for (j = 0; j < 18; j++) {
				miss.stats.medals_earned[j].val = INTEL_INT(t_inf_score.medals[j]);
			}
		} else {
			cfile::io::read(&t_score, sizeof(scoring_conv_t), 1, cfp);

			for (j = 0; j < ship_list_size; j++) {
				miss.stats.ship_kills[j].val = INTEL_INT(t_score.kills[j]);
			}

			miss.stats.score = INTEL_INT(t_score.score);
			miss.stats.rank = INTEL_INT(t_score.rank);
			miss.stats.assists = INTEL_INT(t_score.assists);
			miss.stats.kill_count = INTEL_INT(t_score.kill_count);
			miss.stats.kill_count_ok = INTEL_INT(t_score.kill_count_ok);
			miss.stats.p_shots_fired = INTEL_INT(t_score.p_shots_fired);
			miss.stats.s_shots_fired = INTEL_INT(t_score.s_shots_fired);
			miss.stats.p_shots_hit = INTEL_INT(t_score.p_shots_hit);
			miss.stats.s_shots_hit = INTEL_INT(t_score.s_shots_hit);
			miss.stats.p_bonehead_hits = INTEL_INT(t_score.p_bonehead_hits);
			miss.stats.s_bonehead_hits = INTEL_INT(t_score.s_bonehead_hits);
			miss.stats.bonehead_kills = INTEL_INT(t_score.bonehead_kills);

			for (j = 0; j < 18; j++) {
				miss.stats.medals_earned[j].val = INTEL_INT(t_score.medals[j]);
			}
		}

		// flags
		miss.flags = cfile::io::read<int>(cfp);


		// now add to list
		csg->missions.push_back( miss );
	}

	// finally, convert old mission variables to proper campaign variables
	for (idx = 0; idx < num_missions; idx++) {
		count = (int)csg->missions[idx].variables.size();

		for (j = 0; j < count; j++) {
			bool add_it = true;

			list_size = (int)csg->variables.size();

			for (k = 0; k < list_size; k++) {
				if ( !stricmp(csg->variables[k].variable_name, csg->missions[idx].variables[j].variable_name) ) {
					csg->variables[k] = csg->missions[idx].variables[j];
					add_it = false;
					break;
				}
			}

			if (add_it) {
				csg->variables.push_back( csg->missions[idx].variables[j] );
			}
		}
	}
}

void pilotfile_convert::csg_import_red_alert()
{
	int idx, i, j;
	int count;
	char t_string[35] = { '\0' };
	float val;
	wep_t weapons;

	count = cfile::io::read<int>(cfp);

	if (count <= 0) {
		return;
	}

	csg->wingman_status.reserve( count );

	cfile::io::readString(t_string, sizeof(t_string)-1, cfp);
	csg->precursor_mission = t_string;

	int ship_list_size = (int)csg->ship_list.size();
	int weapon_list_size = (int)csg->weapon_list.size();

	for (idx = 0; idx < count; idx++) {
		red_alert_ship_status ras;

		// ship name
		cfile::io::readString(t_string, sizeof(t_string)-1, cfp);
		ras.name = t_string;

		ras.hull = cfile::io::read<float>(cfp);
		ras.ship_class = cfile::io::read<int>(cfp);

		if (ras.ship_class >= ship_list_size) {
			throw std::runtime_error("Data failure (RedAlert-ship)!");
		}

		// system status
		ras.subsys_current_hits.reserve(64);

		for (j = 0; j < 64; j++) {
			val = cfile::io::read<float>(cfp);
			ras.subsys_current_hits.push_back( val );
		}

		ras.subsys_aggregate_current_hits.reserve(12);

		for (j = 0; j < 12; j++) {
			val = cfile::io::read<float>(cfp);
			ras.subsys_aggregate_current_hits.push_back( val );
		}

		// loadout
		ras.primary_weapons.reserve(3);

		for (j = 0; j < 3; j++) {
			i = cfile::io::read<int>(cfp);

			if (i >= weapon_list_size || i < -1) {
				throw std::runtime_error("Data check failure (RedAlert-weapon)!");
			} else if (i >= 0) {
				weapons.index = csg->weapon_list[i].index;
			} else {
				weapons.index = -1;
			}

			weapons.count = cfile::io::read<int>(cfp);

			if (weapons.index >= 0) {
				ras.primary_weapons.push_back( weapons );
			}
		}

		ras.secondary_weapons.reserve(4);

		for (j = 0; j < 4; j++) {
			i = cfile::io::read<int>(cfp);

			if (i >= weapon_list_size || i < -1) {
				throw std::runtime_error("Data check failure (RedAlert-weapon)!");
			} else if (i >= 0) {
				weapons.index = csg->weapon_list[i].index;
			} else {
				weapons.index = -1;
			}

			weapons.count = cfile::io::read<int>(cfp);

			if (weapons.index >= 0) {
				ras.secondary_weapons.push_back( weapons );
			}
		}

		// add to list
		csg->wingman_status.push_back( ras );
	}
}

void pilotfile_convert::csg_import_techroom()
{
	int idx, list_size = 0;
	bool visible;
	unsigned char in = 0;

	// intel entry count
	int intel_count = cfile::io::read<int>(cfp);

	csg->ships_techroom.reserve( csg->ship_list.size() );
	csg->weapons_techroom.reserve( csg->weapon_list.size() );
	csg->intel_techroom.reserve( intel_count );

	// ships
	list_size = (int)csg->ship_list.size();

	for (idx = 0; idx < list_size; idx++) {
		in = cfile::io::read<ubyte>(cfp);

		if (in > 1) {
			throw std::runtime_error("Data check failure (techroom-ship)!");
		}

		visible = (in == 1) ? true : false;

		csg->ships_techroom.push_back( visible );
	}

	// weapons
	list_size = (int)csg->weapon_list.size();

	for (idx = 0; idx < list_size; idx++) {
		in = cfile::io::read<ubyte>(cfp);

		if (in > 1) {
			throw std::runtime_error("Data check failure (techroom-weapon)!");
		}

		visible = (in == 1) ? true : false;

		csg->weapons_techroom.push_back( visible );
	}

	// intel
	list_size = intel_count;

	for (idx = 0; idx < list_size; idx++) {
		in = cfile::io::read<ubyte>(cfp);

		if (in > 1) {
			throw std::runtime_error("Data check failure (techroom-intel)!");
		}

		visible = (in == 1) ? true : false;

		csg->intel_techroom.push_back( visible );
	}
}

void pilotfile_convert::csg_import_loadout()
{
	int idx, j;
	int list_size = 0, count;
	char t_string[50] = { '\0' };

	// mission name/status
	cfile::io::readStringLen(t_string, sizeof(t_string), cfp);
	csg->loadout.filename = t_string;

	cfile::io::readStringLen(t_string, sizeof(t_string), cfp);
	csg->loadout.last_modified = t_string;

	// ship pool
	list_size = csg->ship_list.size();
	csg->loadout.ship_pool.reserve(list_size);

	for (idx = 0; idx < list_size; idx++) {
		count = cfile::io::read<int>(cfp);
		csg->loadout.ship_pool.push_back( count );
	}

	// weapon pool
	list_size = csg->weapon_list.size();
	csg->loadout.weapon_pool.reserve(list_size);

	for (idx = 0; idx < list_size; idx++) {
		count = cfile::io::read<int>(cfp);
		csg->loadout.weapon_pool.push_back( count );
	}

	// loadout info
	for (idx = 0; idx < MAX_WSS_SLOTS_CONV; idx++) {
		csg->loadout.slot[idx].ship_index = cfile::io::read<int>(cfp);

		for (j = 0; j < MAX_SHIP_WEAPONS_CONV; j++) {
			csg->loadout.slot[idx].wep[j] = cfile::io::read<int>(cfp);
			csg->loadout.slot[idx].wep_count[j] = cfile::io::read<int>(cfp);
		}
	}
}

void pilotfile_convert::csg_import_stats()
{
	int list_size = 0;
	int idx;

	csg->stats.score = cfile::io::read<int>(cfp);
	csg->stats.rank = cfile::io::read<int>(cfp);
	csg->stats.assists = cfile::io::read<int>(cfp);

	csg->stats.medals_earned = csg->medals_list;

	list_size = (int)csg->stats.medals_earned.size();

	for (idx = 0; idx < list_size; idx++) {
		csg->stats.medals_earned[idx].val = cfile::io::read<int>(cfp);
	}

	csg->stats.ship_kills = csg->ship_list;

	list_size = cfile::io::read<int>(cfp);

	// NOTE: could be less, but never greater than
	if ( list_size > (int)csg->stats.ship_kills.size() ) {
		throw std::runtime_error("Data check failure (kills size)!");
	}

	for (idx = 0; idx < list_size; idx++) {
		csg->stats.ship_kills[idx].val = (int)cfile::io::read<ushort>(cfp);
	}

	csg->stats.kill_count = cfile::io::read<int>(cfp);
	csg->stats.kill_count_ok = cfile::io::read<int>(cfp);

	csg->stats.p_shots_fired = cfile::io::read<uint>(cfp);
	csg->stats.s_shots_fired = cfile::io::read<uint>(cfp);
	csg->stats.p_shots_hit = cfile::io::read<uint>(cfp);
	csg->stats.s_shots_hit = cfile::io::read<uint>(cfp);

	csg->stats.p_bonehead_hits = cfile::io::read<uint>(cfp);
	csg->stats.s_bonehead_hits = cfile::io::read<uint>(cfp);
	csg->stats.bonehead_kills = cfile::io::read<uint>(cfp);
}

void pilotfile_convert::csg_import(bool inferno)
{
	Assert( cfp != NULL );

	char name[35];

	unsigned int csg_id = cfile::io::read<uint>(cfp);

	if (csg_id != 0xbeefcafe) {
		throw std::runtime_error("Invalid file signature!");
	}

	fver = cfile::io::read<uint>(cfp);

	if (fver != 15) {
		throw std::runtime_error("Unsupported file version!");
	}

	// campaign type (single/multi)
	csg->sig = cfile::io::read<int>(cfp);

	// trash
	cfile::io::readStringLen(name, sizeof(name), cfp);

	csg->prev_mission = cfile::io::read<int>(cfp);
	csg->next_mission = cfile::io::read<int>(cfp);
	csg->loop_reentry = cfile::io::read<int>(cfp);
	csg->loop_enabled = cfile::io::read<int>(cfp);

	csg_import_ships_weapons();

	csg_import_missions(inferno);

	csg->main_hall = cfile::io::read<ubyte>(cfp);

	csg_import_red_alert();

	csg_import_techroom();

	csg_import_loadout();

	csg_import_stats();

	csg->cutscenes = cfile::io::read<int>(cfp);

	// final data checks
	if ( csg->ship_list.size() != csg->ships_allowed.size() ) {
		throw std::runtime_error("Data check failure (ship size)!");
	} else if ( csg->ship_list.size() != csg->ships_techroom.size() ) {
		throw std::runtime_error("Data check failure (ship size)!");
	} else if ( csg->weapon_list.size() != csg->weapons_allowed.size() ) {
		throw std::runtime_error("Data check failure (weapon size)!");
	} else if ( csg->weapon_list.size() != csg->weapons_techroom.size() ) {
		throw std::runtime_error("Data check failure (weapon size)!");
	} else if ( csg->intel_list.size() != csg->intel_techroom.size() ) {
		throw std::runtime_error("Data check failure (intel size)!");
	}


	// and... we're done!
}

void pilotfile_convert::csg_export_flags()
{
	startSection(Section::Flags);

	// tips
	cfile::io::write<ubyte>((ubyte)plr->tips, cfp);

	// special rank
	cfile::io::write<int>(csg->stats.rank, cfp);

	endSection();
}

void pilotfile_convert::csg_export_info()
{
	int list_size = 0;
	int idx;
	ubyte visible;

	startSection(Section::Info);

	// ship list
	list_size = (int)csg->ship_list.size();
	cfile::io::write<int>(list_size, cfp);

	for (idx = 0; idx < list_size; idx++) {
		cfile::io::writeStringLen(csg->ship_list[idx].name.c_str(), cfp);
	}

	// weapon list
	list_size = (int)csg->weapon_list.size();
	cfile::io::write<int>(list_size, cfp);

	for (idx = 0; idx < list_size; idx++) {
		cfile::io::writeStringLen(csg->weapon_list[idx].name.c_str(), cfp);
	}

	// intel list
	list_size = (int)csg->intel_list.size();
	cfile::io::write<int>(list_size, cfp);

	for (idx = 0; idx < list_size; idx++) {
		cfile::io::writeStringLen(csg->intel_list[idx].name.c_str(), cfp);
	}

	// medals list
	list_size = (int)csg->stats.medals_earned.size();
	cfile::io::write<int>(list_size, cfp);

	for (idx = 0; idx < list_size; idx++) {
		cfile::io::writeStringLen(csg->stats.medals_earned[idx].name.c_str(), cfp);
	}

	// last ship flown
	cfile::io::write<int>(csg->last_ship_flown_index, cfp);

	// progression state
	cfile::io::write<int>(csg->prev_mission, cfp);
	cfile::io::write<int>(csg->next_mission, cfp);

	// loop state
	cfile::io::write<int>(csg->loop_enabled, cfp);
	cfile::io::write<int>(csg->loop_reentry, cfp);

	// missions completed
	list_size = (int)csg->missions.size();
	cfile::io::write<int>(list_size, cfp);

	// allowed ships
	list_size = (int)csg->ships_allowed.size();
	for (idx = 0; idx < list_size; idx++) {
		visible = csg->ships_allowed[idx] ? 1 : 0;
		cfile::io::write<ubyte>(visible, cfp);
	}

	// allowed weapons
	list_size = (int)csg->weapons_allowed.size();
	for (idx = 0; idx < list_size; idx++) {
		visible = csg->weapons_allowed[idx] ? 1 : 0;
		cfile::io::write<ubyte>(visible, cfp);
	}

	// single/campaign squad name & image, make it the same as multi
	cfile::io::writeStringLen(plr->squad_name, cfp);
	cfile::io::writeStringLen(plr->squad_filename, cfp);

	endSection();
}

void pilotfile_convert::csg_export_missions()
{
	int idx, j;
	int list_size = 0;
	int count = 0;

	startSection(Section::Missions);

	list_size = csg->missions.size();

	for (idx = 0; idx < list_size; idx++) {
		cfile::io::write<int>(csg->missions[idx].index, cfp);

		// flags
		cfile::io::write<int>(csg->missions[idx].flags, cfp);

		// goals
		count = (int)csg->missions[idx].goals.size();
		cfile::io::write<int>(count, cfp);

		for (j = 0; j < count; j++) {
			cfile::io::writeStringLen(csg->missions[idx].goals[j].name, cfp);
			cfile::io::write<char>(csg->missions[idx].goals[j].status, cfp);
		}

		// events
		count = (int)csg->missions[idx].events.size();
		cfile::io::write<int>(count, cfp);

		for (j = 0; j < count; j++) {
			cfile::io::writeStringLen(csg->missions[idx].events[j].name, cfp);
			cfile::io::write<char>(csg->missions[idx].events[j].status, cfp);
		}

		// variables
		count = (int)csg->missions[idx].variables.size();
		cfile::io::write<int>(count, cfp);

		for (j = 0; j < count; j++) {
			cfile::io::write<int>(csg->missions[idx].variables[j].type, cfp);
			cfile::io::writeStringLen(csg->missions[idx].variables[j].text, cfp);
			cfile::io::writeStringLen(csg->missions[idx].variables[j].variable_name, cfp);
		}

		// scoring stats
		cfile::io::write<int>(csg->missions[idx].stats.score, cfp);
		cfile::io::write<int>(csg->missions[idx].stats.rank, cfp);
		cfile::io::write<int>(csg->missions[idx].stats.assists, cfp);
		cfile::io::write<int>(csg->missions[idx].stats.kill_count, cfp);
		cfile::io::write<int>(csg->missions[idx].stats.kill_count_ok, cfp);
		cfile::io::write<int>(csg->missions[idx].stats.bonehead_kills, cfp);

		cfile::io::write<uint>(csg->missions[idx].stats.p_shots_fired, cfp);
		cfile::io::write<uint>(csg->missions[idx].stats.p_shots_hit, cfp);
		cfile::io::write<uint>(csg->missions[idx].stats.p_bonehead_hits, cfp);

		cfile::io::write<uint>(csg->missions[idx].stats.s_shots_fired, cfp);
		cfile::io::write<uint>(csg->missions[idx].stats.s_shots_hit, cfp);
		cfile::io::write<uint>(csg->missions[idx].stats.s_bonehead_hits, cfp);

		// ship kills (scoring)
		count = (int)csg->missions[idx].stats.ship_kills.size();

		for (j = 0; j < count; j++) {
			cfile::io::write<int>(csg->missions[idx].stats.ship_kills[j].val, cfp);
		}

		// medals earned (scoring)
		count = (int)csg->missions[idx].stats.medals_earned.size();

		for (j = 0; j < count; j++) {
			cfile::io::write<int>(csg->missions[idx].stats.medals_earned[j].val, cfp);
		}
	}

	endSection();
}

void pilotfile_convert::csg_export_techroom()
{
	int list_size = 0;
	int idx;
	ubyte visible;

	startSection(Section::Techroom);

	// visible ships
	list_size = (int)csg->ships_techroom.size();

	for (idx = 0; idx < list_size; idx++) {
		visible = csg->ships_techroom[idx] ? 1 : 0;
		cfile::io::write<ubyte>(visible, cfp);
	}

	// visible weapons
	list_size = (int)csg->weapons_techroom.size();

	for (idx = 0; idx < list_size; idx++) {
		visible = csg->weapons_techroom[idx] ? 1 : 0;
		cfile::io::write<ubyte>(visible, cfp);
	}

	// visible intel entries
	list_size = (int)csg->intel_techroom.size();

	for (idx = 0; idx < list_size; idx++) {
		visible = csg->intel_techroom[idx] ? 1 : 0;
		cfile::io::write<ubyte>(visible, cfp);
	}

	endSection();
}

void pilotfile_convert::csg_export_loadout()
{
	int idx, j;
	int list_size = 0;

	startSection(Section::Loadout);

	// base info
	cfile::io::writeStringLen(csg->loadout.filename.c_str(), cfp);
	cfile::io::writeStringLen(csg->loadout.last_modified.c_str(), cfp);

	// ship pool
	list_size = csg->loadout.ship_pool.size();

	for (idx = 0; idx < list_size; idx++) {
		cfile::io::write<int>(csg->loadout.ship_pool[idx], cfp);
	}

	// weapon pool
	list_size = csg->loadout.weapon_pool.size();

	for (idx = 0; idx < list_size; idx++) {
		cfile::io::write<int>(csg->loadout.weapon_pool[idx], cfp);
	}

	// play ship loadout
	cfile::io::write<short>(12, cfp);

	for (idx = 0; idx < 12; idx++) {
		// ship
		cfile::io::write<int>(csg->loadout.slot[idx].ship_index, cfp);

		// primary weapons
		cfile::io::write<int>(3, cfp);

		for (j = 0; j < 3; j++) {
			cfile::io::write<int>(csg->loadout.slot[idx].wep[j], cfp);
			cfile::io::write<int>(csg->loadout.slot[idx].wep_count[j], cfp);
		}

		// secondary weapons
		cfile::io::write<int>(4, cfp);

		for (j = 0; j < 4; j++) {
			cfile::io::write<int>(csg->loadout.slot[idx].wep[j+3], cfp);
			cfile::io::write<int>(csg->loadout.slot[idx].wep_count[j+3], cfp);
		}
	}

	endSection();
}

void pilotfile_convert::csg_export_stats()
{
	int idx;
	int list_size = 0;

	startSection(Section::Scoring);

	// scoring stats
	cfile::io::write<int>(csg->stats.score, cfp);
	cfile::io::write<int>(csg->stats.rank, cfp);
	cfile::io::write<int>(csg->stats.assists, cfp);
	cfile::io::write<int>(csg->stats.kill_count, cfp);
	cfile::io::write<int>(csg->stats.kill_count_ok, cfp);
	cfile::io::write<int>(csg->stats.bonehead_kills, cfp);

	cfile::io::write<uint>(csg->stats.p_shots_fired, cfp);
	cfile::io::write<uint>(csg->stats.p_shots_hit, cfp);
	cfile::io::write<uint>(csg->stats.p_bonehead_hits, cfp);

	cfile::io::write<uint>(csg->stats.s_shots_fired, cfp);
	cfile::io::write<uint>(csg->stats.s_shots_hit, cfp);
	cfile::io::write<uint>(csg->stats.s_bonehead_hits, cfp);

	cfile::io::write<uint>(csg->stats.flight_time, cfp);
	cfile::io::write<uint>(csg->stats.missions_flown, cfp);
	cfile::io::write<int>((int)csg->stats.last_flown, cfp);
	cfile::io::write<int>((int)csg->stats.last_backup, cfp);

	// ship kills (scoring)
	list_size = csg->stats.ship_kills.size();
	for (idx = 0; idx < list_size; idx++) {
		cfile::io::write<int>(csg->stats.ship_kills[idx].val, cfp);
	}

	// medals earned (scoring)
	list_size = csg->stats.medals_earned.size();
	for (idx = 0; idx < list_size; idx++) {
		cfile::io::write<int>(csg->stats.medals_earned[idx].val, cfp);
	}

	endSection();
}

void pilotfile_convert::csg_export_redalert()
{
	int idx, j, list_size = 0;
	int count;
	red_alert_ship_status *ras;

	startSection(Section::RedAlert);

	list_size = (int)csg->wingman_status.size();

	cfile::io::write<int>(list_size, cfp);

	if (list_size) {
		cfile::io::writeStringLen(csg->precursor_mission.c_str(), cfp);

		for (idx = 0; idx < list_size; idx++) {
			ras = &csg->wingman_status[idx];

			cfile::io::writeStringLen(ras->name.c_str(), cfp);

			cfile::io::write<float>(ras->hull, cfp);

			// ship class, should be index into ship_list[] on load
			cfile::io::write<int>(ras->ship_class, cfp);

			// subsystem hits
			count = (int)ras->subsys_current_hits.size();
			cfile::io::write<int>(count, cfp);

			for (j = 0; j < count; j++) {
				cfile::io::write<float>(ras->subsys_current_hits[j], cfp);
			}

			// subsystem aggregate hits
			count = (int)ras->subsys_aggregate_current_hits.size();
			cfile::io::write<int>(count, cfp);

			for (j = 0; j < count; j++) {
				cfile::io::write<float>(ras->subsys_aggregate_current_hits[j], cfp);
			}

			// primary weapon loadout and status
			count = (int)ras->primary_weapons.size();
			cfile::io::write<int>(count, cfp);

			for (j = 0; j < count; j++) {
				cfile::io::write<int>(ras->primary_weapons[j].index, cfp);
				cfile::io::write<int>(ras->primary_weapons[j].count, cfp);
			}

			// secondary weapon loadout and status
			count = (int)ras->secondary_weapons.size();
			cfile::io::write<int>(count, cfp);

			for (j = 0; j < count; j++) {
				cfile::io::write<int>(ras->secondary_weapons[j].index, cfp);
				cfile::io::write<int>(ras->secondary_weapons[j].count, cfp);
			}
		}
	}

	endSection();
}

void pilotfile_convert::csg_export_hud()
{
	int idx;

	startSection(Section::HUD);

	// flags
	cfile::io::write<int>(plr->hud_show_flags, cfp);
	cfile::io::write<int>(plr->hud_show_flags2, cfp);

	cfile::io::write<int>(plr->hud_popup_flags, cfp);
	cfile::io::write<int>(plr->hud_popup_flags2, cfp);

	// settings
	cfile::io::write<ubyte>(plr->hud_num_lines, cfp);

	cfile::io::write<int>(plr->hud_rp_flags, cfp);
	cfile::io::write<int>(plr->hud_rp_dist, cfp);

	// basic colors
	cfile::io::write<int>(0, cfp);	// color
	cfile::io::write<int>(8, cfp);	// alpha

	// gauge-specific colors
	cfile::io::write<int>(39, cfp);

	for (idx = 0; idx < 39; idx++) {
		cfile::io::write<ubyte>(plr->hud_colors[idx][0], cfp);
		cfile::io::write<ubyte>(plr->hud_colors[idx][1], cfp);
		cfile::io::write<ubyte>(plr->hud_colors[idx][2], cfp);
		cfile::io::write<ubyte>(plr->hud_colors[idx][3], cfp);
	}

	endSection();
}

void pilotfile_convert::csg_export_variables()
{
	int list_size = 0;
	int idx;

	startSection(Section::Variables);

	list_size = (int)csg->variables.size();

	cfile::io::write<int>(list_size, cfp);

	for (idx = 0; idx < list_size; idx++) {
		cfile::io::write<int>(csg->variables[idx].type, cfp);
		cfile::io::writeStringLen(csg->variables[idx].text, cfp);
		cfile::io::writeStringLen(csg->variables[idx].variable_name, cfp);
	}

	endSection();
}

void pilotfile_convert::csg_export_cutscenes() {
	SCP_vector<cutscene_info>::iterator cut;

	startSection(Section::Cutscenes);

	// convert the old int bitfield to the new vector
	// the 32 is the size-in-bits of the old int on all platforms
	// supported by FSO prior to 3.7.0
	size_t size = Cutscenes.size();
	size_t viewableScenes = 0;
	for (size_t j=0; j<size && j<32; ++j) {
		if ( csg->cutscenes & (1<<j) ) {
			Cutscenes.at(j).viewable = true;
			viewableScenes++;
		}
	}

	// output cutscene data in new format
	cfile::io::write<uint>(viewableScenes, cfp);

	for(cut = Cutscenes.begin(); cut != Cutscenes.end(); ++cut) {
		if(cut->viewable)
			cfile::io::writeStringLen(cut->filename, cfp);
	}

	endSection();
}

void pilotfile_convert::csg_export()
{
	Assert( cfp != NULL );

	// header and version
	cfile::io::write<int>(CSG_FILE_ID, cfp);
	cfile::io::write<ubyte>(CSG_VERSION, cfp);

	// flags and info sections go first
	csg_export_flags();
	csg_export_info();

	// everything else is next, not order specific
	csg_export_missions();
	csg_export_techroom();
	csg_export_loadout();
	csg_export_stats();
	csg_export_redalert();
	csg_export_hud();
	csg_export_variables();
	csg_export_cutscenes();

	// and... we're done! :)
}

bool pilotfile_convert::csg_convert(const char *fname, bool inferno)
{
	Assert( fname != NULL );
	Assert( plr != NULL);
	Assert( csg == NULL );

	bool rval = true;

	csg = new(std::nothrow) csg_data;

	if (csg == NULL) {
		return false;
	}

	SCP_string filename(fname);
	filename.append(".cs2");

	mprintf(("    CS2 => Converting '%s'...\n", filename.c_str()));

	cfp = cfile::io::open(filename, cfile::MODE_READ, cfile::OPEN_NORMAL, inferno ? cfile::TYPE_SINGLE_PLAYERS_INFERNO : cfile::TYPE_SINGLE_PLAYERS);

	if ( !cfp ) {
		mprintf(("    CS2 => Unable to open '%s' for import!\n", fname));
		delete csg;
		csg = NULL;

		return false;
	}

	try {
		csg_import(inferno);
	} catch (const std::exception& err) {
		mprintf(("    CS2 => Import ERROR: %s\n", err.what()));
		rval = false;
	}

	cfile::io::close(cfp);
	cfp = NULL;

	if ( !rval ) {
		delete csg;
		csg = NULL;

		return false;
	}

	filename.assign(fname);
	filename.append(".csg");

	cfp = cfile::io::open(filename.c_str(), cfile::MODE_WRITE, cfile::OPEN_NORMAL, cfile::TYPE_PLAYERS);

	if ( !cfp ) {
		mprintf(("    CSG => Unable to open '%s' for export!\n", fname));
		return false;
	}

	try {
		csg_export();
	} catch (const char *err) {
		mprintf(("    CSG => Export ERROR: %s\n", err));
		rval = false;
	}

	cfile::io::close(cfp);
	cfp = NULL;

	delete csg;
	csg = NULL;

	if (rval) {
		mprintf(("    CSG => Conversion complete!\n"));
	}

	return rval;
}
