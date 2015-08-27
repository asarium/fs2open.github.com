
/* WARNING:
 *    This is magic-number central, but these numbers are set specifically
 *    to the acceptable defaults or range values that were used when the
 *    pl2/plr files were created.  Standard game defines should not be used in
 *    place of these major numbers for /any/ reason, *ever*!
 */

#include "mission/missionbriefcommon.h"
#include "network/psnet2.h"
#include "pilotfile/pilotfile_convert.h"


// this struct isn't well packed, and is written whole to the pilot file, so
// we can't easily just get the RGBA that we need and instead must retain this
typedef struct conv_color { //-V802
	uint		screen_sig;
	ubyte		red;
	ubyte		green;
	ubyte		blue;
	ubyte		alpha;
	ubyte		ac_type;
	int		is_alphacolor;
	ubyte		raw8;
	int		alphacolor;
	int		magic;
} conv_color;


plr_data::plr_data()
{
	// not carried over, just for reference during conversion process
	version = 0;
	is_multi = 0;
	lcl_get_language_name(language);

	// basic flags and settings
	tips = 0;
	rank = 0;
	skill_level = 1;
	save_flags = 0;
	readyroom_listing_mode = 0;
	voice_enabled = 1;
	auto_advance = 1;
	Use_mouse_to_fly = 0;
	Mouse_sensitivity = 4;
	Joy_sensitivity = 9;
	Dead_zone_size = 10;

	// multiplayer settings/options
	net_protocol = 1;

	multi_squad_set = 2;
	multi_endgame_set = 3;
	multi_flags = 3;
	multi_respawn = 2;
	multi_max_observers = 2;
	multi_skill_level = 2;
	multi_voice_qos = 10;
	multi_voice_token_wait = 2000;
	multi_voice_record_time = 5000;
	multi_time_limit = -65536;
	multi_kill_limit = 9999;

	multi_local_flags = 5;
	multi_local_update_level = 0;

	// pilot info stuff
	memset(image_filename, 0, sizeof(image_filename));
	memset(squad_name, 0, sizeof(squad_name));
	memset(squad_filename, 0, sizeof(squad_filename));
	memset(current_campaign, 0, sizeof(current_campaign));
	memset(last_ship_flown, 0, sizeof(last_ship_flown));

	// HUD config
	hud_show_flags = -1;
	hud_show_flags2 = 31;
	hud_popup_flags = 0;
	hud_popup_flags2 = 0;
	hud_num_lines = 4;
	hud_rp_flags = 7;
	hud_rp_dist = 2;

	for (int idx = 0; idx < 39; idx++) {
		hud_colors[idx][0] = 0;
		hud_colors[idx][1] = 255;
		hud_colors[idx][2] = 0;
		hud_colors[idx][3] = 144;
	}

	// control setup
	joy_axis_map_to[0] = 0;
	joy_axis_map_to[1] = 1;
	joy_axis_map_to[2] = 3;
	joy_invert_axis[3] = -1;
	joy_invert_axis[4] = -1;

	memset(joy_invert_axis, 0, sizeof(joy_invert_axis));

	// audio
	sound_volume = 1.0f;
	music_volume = 0.5f;
	voice_volume = 0.7f;

	// detail settings
	detail_setting = 3;
	detail_nebula = 3;
	detail_distance = 3;
	detail_hardware_textures = 4;
	detail_num_debris = 4;
	detail_num_particles = 3;
	detail_num_stars = 4;
	detail_shield_effects = 4;
	detail_lighting = 4;
	detail_targetview_model = 1;
	detail_planets_suns = 1;
	detail_weapon_extras = 1;
}

plr_data::~plr_data()
{
	controls.clear();
}

void pilotfile_convert::plr_import_controls()
{
	int idx;
	config_item con;

	unsigned char num_controls = cfile::io::read<ubyte>(cfp);

	if ( !num_controls ) {
		return;
	}

	// it may be less than 118, but it shouldn't be more than 118
	if (num_controls > 118) {
		throw "Data check failure in controls!";
	}

	plr->controls.reserve(num_controls);

	for (idx = 0; idx < num_controls; idx++) {
		con.key_id = cfile::io::read<short>(cfp);

		if (con.key_id == 255) {
			con.key_id = -1;
		}

		con.joy_id = cfile::io::read<short>(cfp);

		if (con.joy_id == 255) {
			con.joy_id = -1;
		}

		plr->controls.push_back( con );
	}
}

void pilotfile_convert::plr_import_hud()
{
	int idx;
	conv_color c;

	plr->hud_show_flags = cfile::io::read<int>(cfp);
	plr->hud_show_flags2 = cfile::io::read<int>(cfp);

	plr->hud_popup_flags = cfile::io::read<int>(cfp);
	plr->hud_popup_flags2 = cfile::io::read<int>(cfp);

	plr->hud_num_lines = cfile::io::read<ubyte>(cfp);
	plr->hud_rp_flags = cfile::io::read<int>(cfp);
	plr->hud_rp_dist = cfile::io::read<int>(cfp);

	for (idx = 0; idx < 39; idx++) {
		cfile::io::read(&c, sizeof(conv_color), 1, cfp);

		if ( (c.alphacolor != -1) || (c.is_alphacolor != 1) ) {
			throw "Data check failure in hud!";
		}

		plr->hud_colors[idx][0] = c.red;
		plr->hud_colors[idx][1] = c.green;
		plr->hud_colors[idx][2] = c.blue;
		plr->hud_colors[idx][3] = c.alpha;
	}
}

void pilotfile_convert::plr_import_detail()
{
	bool data_failure = false;

	plr->detail_setting = cfile::io::read<int>(cfp);
	plr->detail_nebula = cfile::io::read<int>(cfp);
	plr->detail_distance = cfile::io::read<int>(cfp);
	plr->detail_hardware_textures = cfile::io::read<int>(cfp);
	plr->detail_num_debris = cfile::io::read<int>(cfp);
	plr->detail_num_particles = cfile::io::read<int>(cfp);
	plr->detail_num_stars = cfile::io::read<int>(cfp);
	plr->detail_shield_effects = cfile::io::read<int>(cfp);
	plr->detail_lighting = cfile::io::read<int>(cfp);
	plr->detail_targetview_model = cfile::io::read<int>(cfp);
	plr->detail_planets_suns = cfile::io::read<int>(cfp);
	plr->detail_weapon_extras = cfile::io::read<int>(cfp);

	if ( (plr->detail_setting < -1) || (plr->detail_setting > 4) ) {
		data_failure = true;
	} else 	if ( (plr->detail_nebula < 0) || (plr->detail_nebula > 4) ) {
		data_failure = true;
	} else 	if ( (plr->detail_distance < 0) || (plr->detail_distance > 4) ) {
		data_failure = true;
	} else 	if ( (plr->detail_hardware_textures < 0) || (plr->detail_hardware_textures > 4) ) {
		data_failure = true;
	} else 	if ( (plr->detail_num_debris < 0) || (plr->detail_num_debris > 4) ) {
		data_failure = true;
	} else 	if ( (plr->detail_num_particles < 0) || (plr->detail_num_particles > 4) ) {
		data_failure = true;
	} else 	if ( (plr->detail_num_stars < 0) || (plr->detail_num_stars > 4) ) {
		data_failure = true;
	} else 	if ( (plr->detail_shield_effects < 0) || (plr->detail_shield_effects > 4) ) {
		data_failure = true;
	} else 	if ( (plr->detail_lighting < 0) || (plr->detail_lighting > 4) ) {
		data_failure = true;
	} else 	if ( (plr->detail_targetview_model < 0) || (plr->detail_targetview_model > 1) ) {
		data_failure = true;
	} else 	if ( (plr->detail_planets_suns < 0) || (plr->detail_planets_suns > 1) ) {
		data_failure = true;
	} else 	if ( (plr->detail_weapon_extras < 0) || (plr->detail_weapon_extras > 1) ) {
		data_failure = true;
	}

	if (data_failure) {
		throw "Data check failure in details!";
	}
}

void pilotfile_convert::plr_import_stats()
{
	int idx;
	char name[35];

	if (fver >= 242) {
		return;
	}

	// read everything, but we don't need any of it ...

	cfile::io::read<int>(cfp);	// score
	cfile::io::read<int>(cfp);	// rank
	cfile::io::read<int>(cfp);	// assists

	// medals
	for (idx = 0; idx < 18; idx++) {
		cfile::io::read<int>(cfp);
	}

	// kills per ship
	int count = cfile::io::read<int>(cfp);

	for (idx = 0; idx < count; idx++) {
		cfile::io::read<ushort>(cfp);
		cfile::io::readStringLen(name, sizeof(name), cfp);
	}

	cfile::io::read<int>(cfp);	// kill_count
	cfile::io::read<int>(cfp);	// kill_count_ok

	cfile::io::read<uint>(cfp);	// p_shots_fired
	cfile::io::read<uint>(cfp);	// s_shots_fired
	cfile::io::read<uint>(cfp);	// p_shots_hit
	cfile::io::read<uint>(cfp);	// s_shots_hit

	cfile::io::read<uint>(cfp);	// p_bonehead_hits
	cfile::io::read<uint>(cfp);	// s_bonehead_hits
	cfile::io::read<uint>(cfp);	// bonehead_kills
}

void pilotfile_convert::plr_import_loadout()
{
	int idx, j;
	int s_count, w_count;
	char name[52];

	if (fver >= 242) {
		return;
	}

	// have to read it, but don't need any of it ...

	cfile::io::readStringLen(name, sizeof(name), cfp);	// filename
	cfile::io::readStringLen(name, sizeof(name), cfp);	// last_modified

	s_count = cfile::io::read<int>(cfp);	// num ships
	w_count = cfile::io::read<int>(cfp);	// num weapons

	// ships
	for (idx = 0; idx < s_count; idx++) {
		cfile::io::read<int>(cfp);	// count
		cfile::io::readStringLen(name, sizeof(name), cfp);	// name
	}

	// weapons
	for (idx = 0; idx < w_count; idx++) {
		cfile::io::read<int>(cfp);	// count
		cfile::io::readStringLen(name, sizeof(name), cfp);	// name
	}

	// loadout info
	for (idx = 0; idx < 12; idx++) {
		cfile::io::read<int>(cfp);	// ship class
		cfile::io::readStringLen(name, sizeof(name), cfp);	// ship name

		for (j = 0; j < 12; j++) {
			cfile::io::read<int>(cfp);	// weapon type
			cfile::io::read<int>(cfp);	// weapon count
			cfile::io::readStringLen(name, sizeof(name), cfp);	// weapon name
		}
	}
}

void pilotfile_convert::plr_import_multiplayer()
{
	plr->multi_squad_set = cfile::io::read<ubyte>(cfp);
	plr->multi_endgame_set = cfile::io::read<ubyte>(cfp);
	plr->multi_flags = cfile::io::read<int>(cfp);
	plr->multi_respawn = cfile::io::read<uint>(cfp);
	plr->multi_max_observers = cfile::io::read<ubyte>(cfp);
	plr->multi_skill_level = cfile::io::read<ubyte>(cfp);
	plr->multi_voice_qos = cfile::io::read<ubyte>(cfp);
	plr->multi_voice_token_wait = cfile::io::read<int>(cfp);
	plr->multi_voice_record_time = cfile::io::read<int>(cfp);
	plr->multi_time_limit = cfile::io::read<int>(cfp);
	plr->multi_kill_limit = cfile::io::read<int>(cfp);

	plr->multi_local_flags = cfile::io::read<int>(cfp);
	plr->multi_local_update_level = cfile::io::read<int>(cfp);
}

void pilotfile_convert::plr_import_red_alert()
{
	int idx, j;
	char name[35];

	if (fver >= 242) {
		return;
	}

	// have to read it, but don't need any of it ...

	int num_slots = cfile::io::read<int>(cfp);

	if ( (num_slots < 0) || (num_slots >= 32) ) {
		throw "Data check failure in red-alert!";
	}

	if ( !num_slots ) {
		return;
	}

	for (idx = 0; idx < num_slots; idx++) {
		cfile::io::readString(name, sizeof(name) - 1, cfp);
		cfile::io::read<float>(cfp);

		cfile::io::readStringLen(name, sizeof(name), cfp);

		// subsystem hits
		for (j = 0; j < 64; j++) {
			cfile::io::read<float>(cfp);
		}

		// aggregate hits
		for (j = 0; j < 12; j++) {
			cfile::io::read<float>(cfp);
		}

		// weapons
		for (j = 0; j < 12; j++) {
			cfile::io::readStringLen(name, sizeof(name), cfp);
			cfile::io::read<int>(cfp);
		}
	}
}

void pilotfile_convert::plr_import_variables()
{
	int idx;
	sexp_variable nvar;

	int num_variables = cfile::io::read<int>(cfp);

	if ( (num_variables < 0) || (num_variables >= 100) ) {
		throw "Data check failure in variables!";
	}

	plr->variables.reserve(num_variables);

	for (idx = 0; idx < num_variables; idx++) {
		nvar.type = cfile::io::read<int>(cfp);
		cfile::io::readStringLen(nvar.text, sizeof(nvar.text), cfp);
		cfile::io::readStringLen(nvar.variable_name, sizeof(nvar.variable_name), cfp);

		plr->variables.push_back( nvar );
	}
}

void pilotfile_convert::plr_import()
{
	char name[35];
	int idx;

	unsigned int plr_id = cfile::io::read<uint>(cfp);

	if (plr_id != 0x46505346) {
		throw "Invalid file signature!";
	}

	fver = cfile::io::read<uint>(cfp);

	if ( (fver != 142) && (fver != 242) ) {
		throw "Unsupported file version!";
	}

	// multi flag
	plr->is_multi = (int)cfile::io::read<ubyte>(cfp);

	// rank
	plr->rank = cfile::io::read<int>(cfp);

	// mainhall, don't need it
	if (fver < 242) {
		cfile::io::read<ubyte>(cfp);
	}

	plr->tips = cfile::io::read<int>(cfp);

	if ( (plr->tips < 0) || (plr->tips > 1) ) {
		throw "Data check failure!";
	}

	cfile::io::readStringLen(plr->image_filename, sizeof(plr->image_filename), cfp);
	cfile::io::readStringLen(plr->squad_name, sizeof(plr->squad_name), cfp);
	cfile::io::readStringLen(plr->squad_filename, sizeof(plr->squad_filename), cfp);
	cfile::io::readStringLen(plr->current_campaign, sizeof(plr->current_campaign), cfp);
	cfile::io::readStringLen(plr->last_ship_flown, sizeof(plr->last_ship_flown), cfp);

	// controls
	plr_import_controls();

	// hud config
	plr_import_hud();

	// cutscenes, don't need it
	if (fver < 242) {
		cfile::io::read<int>(cfp);
	}

	// volume stuff
	plr->sound_volume = cfile::io::read<float>(cfp);
	plr->music_volume = cfile::io::read<float>(cfp);
	plr->voice_volume = cfile::io::read<float>(cfp);

	// detail settings
	plr_import_detail();

	// recent missions, don't need it
	int num_missions = cfile::io::read<int>(cfp);

	for (idx = 0; idx < num_missions; idx++) {
		cfile::io::readStringLen(name, sizeof(name), cfp);
	}

	// stats, will skip if fver < 242
	plr_import_stats();

	plr->skill_level = cfile::io::read<int>(cfp);

	if ( (plr->skill_level < 0) || (plr->skill_level > 4) ) {
		throw "Data check failure!";
	}

	// extra joystick stuff
	for (idx = 0; idx < 5; idx++) {
		plr->joy_axis_map_to[idx] = cfile::io::read<int>(cfp);
		plr->joy_invert_axis[idx] = cfile::io::read<int>(cfp);
	}

	// flags
	plr->save_flags = cfile::io::read<int>(cfp);

	// loadout, will skip if fver < 242
	plr_import_loadout();

	// multiplayer
	plr_import_multiplayer();

	// two briefing related values
	plr->readyroom_listing_mode = cfile::io::read<int>(cfp);
	Briefing_voice_enabled = cfile::io::read<int>(cfp);

	plr->net_protocol = cfile::io::read<int>(cfp);

	// protocol must be set to something
	if (plr->net_protocol == NET_NONE) {
		plr->net_protocol = NET_TCP;
	} else if ( (plr->net_protocol < 0) || (plr->net_protocol > NET_VMT) ) {
		throw "Data check failure!";
	}

	// red alert status, will skip if fver < 242 (and should be empty if multi)
	plr_import_red_alert();

	// briefing auto-advance
	plr->auto_advance = cfile::io::read<int>(cfp);

	if ( (plr->auto_advance < 0) || (plr->auto_advance > 1) ) {
		throw "Data check failure!";
	}

	// some input options
	plr->Use_mouse_to_fly = cfile::io::read<int>(cfp);
	plr->Mouse_sensitivity = cfile::io::read<int>(cfp);
	plr->Joy_sensitivity = cfile::io::read<int>(cfp);
	plr->Dead_zone_size = cfile::io::read<int>(cfp);

	// variables
	plr_import_variables();


	// and... we're done! :)
}

void pilotfile_convert::plr_export_flags()
{
	startSection(Section::Flags);

	// tips
	cfile::io::write<ubyte>((unsigned char)plr->tips, cfp);

	// saved flags
	cfile::io::write<int>(plr->save_flags, cfp);

	// listing mode (single or campaign missions)
	cfile::io::write<int>(plr->readyroom_listing_mode, cfp);

	// briefing auto-play
	cfile::io::write<int>(plr->auto_advance, cfp);

	// special rank setting (to avoid having to read all stats on verify)
	cfile::io::write<int>(plr->rank, cfp);

	// What game mode we were in last on this pilot
	cfile::io::write<int>(plr->is_multi, cfp);

	// which language was this pilot created with
	cfile::io::writeStringLen(plr->language, cfp);

	endSection();
}

void pilotfile_convert::plr_export_info()
{
	startSection(Section::Info);

	// pilot image
	cfile::io::writeStringLen(plr->image_filename, cfp);

	// squad name
	cfile::io::writeStringLen(plr->squad_name, cfp);

	// squad image
	cfile::io::writeStringLen(plr->squad_filename, cfp);

	// active campaign
	cfile::io::writeStringLen(plr->current_campaign, cfp);

	endSection();
}

void pilotfile_convert::plr_export_stats()
{
	int idx, list_size = 0;

	startSection(Section::Scoring);

	// global, all-time stats
	cfile::io::write<int>(all_time_stats.score, cfp);
	cfile::io::write<int>(all_time_stats.rank, cfp);
	cfile::io::write<int>(all_time_stats.assists, cfp);
	cfile::io::write<int>(all_time_stats.kill_count, cfp);
	cfile::io::write<int>(all_time_stats.kill_count_ok, cfp);
	cfile::io::write<int>(all_time_stats.bonehead_kills, cfp);

	cfile::io::write<uint>(all_time_stats.p_shots_fired, cfp);
	cfile::io::write<uint>(all_time_stats.p_shots_hit, cfp);
	cfile::io::write<uint>(all_time_stats.p_bonehead_hits, cfp);

	cfile::io::write<uint>(all_time_stats.s_shots_fired, cfp);
	cfile::io::write<uint>(all_time_stats.s_shots_hit, cfp);
	cfile::io::write<uint>(all_time_stats.s_bonehead_hits, cfp);

	cfile::io::write<uint>(all_time_stats.flight_time, cfp);
	cfile::io::write<uint>(all_time_stats.missions_flown, cfp);
	cfile::io::write<int>((int)all_time_stats.last_flown, cfp);
	cfile::io::write<int>((int)all_time_stats.last_backup, cfp);

	// ship kills (contains ships across all mods, not just current)
	list_size = (int)all_time_stats.ship_kills.size();
	cfile::io::write<int>(list_size, cfp);

	for (idx = 0; idx < list_size; idx++) {
		cfile::io::writeStringLen(all_time_stats.ship_kills[idx].name.c_str(), cfp);
		cfile::io::write<int>(all_time_stats.ship_kills[idx].val, cfp);
	}

	// medals earned (contains medals across all mods, not just current)
	list_size = (int)all_time_stats.medals_earned.size();
	cfile::io::write<int>(list_size, cfp);

	for (idx = 0; idx < list_size; idx++) {
		cfile::io::writeStringLen(all_time_stats.medals_earned[idx].name.c_str(), cfp);
		cfile::io::write<int>(all_time_stats.medals_earned[idx].val, cfp);
	}

	endSection();
}

void pilotfile_convert::plr_export_stats_multi()
{
	int idx, list_size = 0;

	startSection(Section::ScoringMulti);

	// global, all-time stats
	cfile::io::write<int>(multi_stats.score, cfp);
	cfile::io::write<int>(multi_stats.rank, cfp);
	cfile::io::write<int>(multi_stats.assists, cfp);
	cfile::io::write<int>(multi_stats.kill_count, cfp);
	cfile::io::write<int>(multi_stats.kill_count_ok, cfp);
	cfile::io::write<int>(multi_stats.bonehead_kills, cfp);

	cfile::io::write<uint>(multi_stats.p_shots_fired, cfp);
	cfile::io::write<uint>(multi_stats.p_shots_hit, cfp);
	cfile::io::write<uint>(multi_stats.p_bonehead_hits, cfp);

	cfile::io::write<uint>(multi_stats.s_shots_fired, cfp);
	cfile::io::write<uint>(multi_stats.s_shots_hit, cfp);
	cfile::io::write<uint>(multi_stats.s_bonehead_hits, cfp);

	cfile::io::write<uint>(multi_stats.flight_time, cfp);
	cfile::io::write<uint>(multi_stats.missions_flown, cfp);
	cfile::io::write<int>((int)multi_stats.last_flown, cfp);
	cfile::io::write<int>((int)multi_stats.last_backup, cfp);

	// ship kills (contains medals across all mods, not just current)
	list_size = (int)multi_stats.ship_kills.size();
	cfile::io::write<int>(list_size, cfp);

	for (idx = 0; idx < list_size; idx++) {
		cfile::io::writeStringLen(multi_stats.ship_kills[idx].name.c_str(), cfp);
		cfile::io::write<int>(multi_stats.ship_kills[idx].val, cfp);
	}

	// medals earned (contains medals across all mods, not just current)
	list_size = (int)multi_stats.medals_earned.size();
	cfile::io::write<int>(list_size, cfp);

	for (idx = 0; idx < list_size; idx++) {
		cfile::io::writeStringLen(multi_stats.medals_earned[idx].name.c_str(), cfp);
		cfile::io::write<int>(multi_stats.medals_earned[idx].val, cfp);
	}

	endSection();
}

void pilotfile_convert::plr_export_hud()
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

void pilotfile_convert::plr_export_variables()
{
	int list_size = 0;
	int idx;

	startSection(Section::Variables);

	list_size = (int)plr->variables.size();

	cfile::io::write<int>(list_size, cfp);

	for (idx = 0; idx < list_size; idx++) {
		cfile::io::write<int>(plr->variables[idx].type, cfp);
		cfile::io::writeStringLen(plr->variables[idx].text, cfp);
		cfile::io::writeStringLen(plr->variables[idx].variable_name, cfp);
	}

	endSection();
}

void pilotfile_convert::plr_export_multiplayer()
{
	startSection(Section::Multiplayer);

	// netgame options
	cfile::io::write<ubyte>(plr->multi_squad_set, cfp);
	cfile::io::write<ubyte>(plr->multi_endgame_set, cfp);
	cfile::io::write<int>(plr->multi_flags, cfp);
	cfile::io::write<uint>(plr->multi_respawn, cfp);
	cfile::io::write<ubyte>(plr->multi_max_observers, cfp);
	cfile::io::write<ubyte>(plr->multi_skill_level, cfp);
	cfile::io::write<ubyte>(plr->multi_voice_qos, cfp);
	cfile::io::write<int>(plr->multi_voice_token_wait, cfp);
	cfile::io::write<int>(plr->multi_voice_record_time, cfp);
	cfile::io::write<int>(plr->multi_time_limit, cfp);
	cfile::io::write<int>(plr->multi_kill_limit, cfp);

	// local options
	cfile::io::write<int>(plr->multi_local_flags, cfp);
	cfile::io::write<int>(plr->multi_local_update_level, cfp);

	// netgame protocol
	cfile::io::write<int>(plr->net_protocol, cfp);

	endSection();
}

void pilotfile_convert::plr_export_controls()
{
	unsigned int idx;

	startSection(Section::Controls);

	cfile::io::write<short>((unsigned short)plr->controls.size(), cfp);

	for (idx = 0; idx < plr->controls.size(); idx++) {
		cfile::io::write<short>(plr->controls[idx].key_id, cfp);
		cfile::io::write<short>(plr->controls[idx].joy_id, cfp);
		// placeholder? for future mouse_id?
		cfile::io::write<short>(-1, cfp);
	}

	// extra joystick stuff
	cfile::io::write<int>(MAX_JOY_AXES_CONV, cfp);
	for (idx = 0; idx < MAX_JOY_AXES_CONV; idx++) {
		cfile::io::write<int>(plr->joy_axis_map_to[idx], cfp);
		cfile::io::write<int>(plr->joy_invert_axis[idx], cfp);
	}

	endSection();
}

void pilotfile_convert::plr_export_settings()
{
	startSection(Section::Settings);

	// sound/voice/music
	cfile::io::write<float>(plr->sound_volume, cfp);
	cfile::io::write<float>(plr->music_volume, cfp);
	cfile::io::write<float>(plr->voice_volume, cfp);

	cfile::io::write<int>(plr->voice_enabled, cfp);

	// skill level
	cfile::io::write<int>(plr->skill_level, cfp);

	// input options
	cfile::io::write<int>(plr->Use_mouse_to_fly, cfp);
	cfile::io::write<int>(plr->Mouse_sensitivity, cfp);
	cfile::io::write<int>(plr->Joy_sensitivity, cfp);
	cfile::io::write<int>(plr->Dead_zone_size, cfp);

	// detail
	cfile::io::write<int>(plr->detail_setting, cfp);
	cfile::io::write<int>(plr->detail_nebula, cfp);
	cfile::io::write<int>(plr->detail_distance, cfp);
	cfile::io::write<int>(plr->detail_hardware_textures, cfp);
	cfile::io::write<int>(plr->detail_num_debris, cfp);
	cfile::io::write<int>(plr->detail_num_particles, cfp);
	cfile::io::write<int>(plr->detail_num_stars, cfp);
	cfile::io::write<int>(plr->detail_shield_effects, cfp);
	cfile::io::write<int>(plr->detail_lighting, cfp);
	cfile::io::write<int>(plr->detail_targetview_model, cfp);
	cfile::io::write<int>(plr->detail_planets_suns, cfp);
	cfile::io::write<int>(plr->detail_weapon_extras, cfp);

	endSection();
}

void pilotfile_convert::plr_export()
{
	Assert( cfp != NULL );

	// header and version
	cfile::io::write<int>(PLR_FILE_ID, cfp);
	cfile::io::write<ubyte>(PLR_VERSION, cfp);

	// flags and info sections go first
	plr_export_flags();
	plr_export_info();

	// everything else is next, not order specific
	plr_export_stats();
	plr_export_stats_multi();
	plr_export_hud();
	plr_export_variables();
	plr_export_multiplayer();
	plr_export_controls();
	plr_export_settings();


	// and... we're done! :)
}

bool pilotfile_convert::plr_convert(const char *fname, bool inferno)
{
	Assert( fname != NULL );

	bool rval = true;

	if (plr == NULL) {
		plr = new(std::nothrow) plr_data;
	}

	if (plr == NULL) {
		return false;
	}

	SCP_string filename(fname);
	filename.append(".pl2");

	mprintf(("  PL2 => Converting '%s'...\n", filename.c_str()));

	cfp = cfile::io::open(filename, cfile::MODE_READ, cfile::OPEN_NORMAL, inferno ? cfile::TYPE_SINGLE_PLAYERS_INFERNO : cfile::TYPE_SINGLE_PLAYERS);

	if ( !cfp ) {
		mprintf(("  PL2 => Unable to open '%s' for import!\n", fname));
		return false;
	}

	try {
		plr_import();
	} catch (const char *err) {
		mprintf((  "  PL2 => Import ERROR: %s\n", err));
		rval = false;
	}

	cfile::io::close(cfp);
	cfp = NULL;

	if ( !rval ) {
		return false;
	}

	filename.assign(fname);
	filename.append(".plr");

	cfp = cfile::io::open(filename, cfile::MODE_WRITE, cfile::OPEN_NORMAL, cfile::TYPE_PLAYERS);

	if ( !cfp ) {
		mprintf(("  PLR => Unable to open '%s' for export!\n", fname));
		return false;
	}

	try {
		plr_export();
	} catch (const char *err) {
		mprintf(("  PLR => Export ERROR: %s\n", err));
		rval = false;
	}

	cfile::io::close(cfp);
	cfp = NULL;

	if (rval) {
		mprintf(("  PLR => Conversion complete!\n"));
	}

	return rval;
}
