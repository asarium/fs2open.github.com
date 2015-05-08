
#include "globalincs/pstypes.h"
#include "pilotfile/pilotfile.h"
#include "playerman/player.h"
#include "ship/ship.h"
#include "menuui/techmenu.h"
#include "weapon/weapon.h"
#include "hud/hudconfig.h"
#include "stats/medals.h"
#include "hud/hudsquadmsg.h"
#include "gamesnd/eventmusic.h"
#include "osapi/osregistry.h"
#include "sound/audiostr.h"
#include "io/joy.h"
#include "io/mouse.h"
#include "network/multi.h"
#include "freespace.h"
#include "playerman/managepilot.h"
#include "localization/localize.h"


void pilotfile::plr_read_flags()
{
	// tips?
	p->tips = (int)cfile::io::read<ubyte>(cfp);

	// saved flags
	p->save_flags = cfile::io::read<int>(cfp);

	// listing mode (single or campaign missions
	p->readyroom_listing_mode = cfile::io::read<int>(cfp);

	// briefing auto-play
	p->auto_advance = cfile::io::read<int>(cfp);

	// special rank setting (to avoid having to read all stats on verify)
	// will be the multi rank
	// if there's a valid CSG, this will be overwritten
	p->stats.rank = cfile::io::read<int>(cfp);

	if (version > 0) 
	{
		p->player_was_multi = cfile::io::read<int>(cfp);
	} else 
	{
		p->player_was_multi = 0; // Default to single player
	}

	// which language was this pilot created with
	if (version > 1) {
		cfile::io::readStringLen(p->language, sizeof(p->language), cfp);
	} else {
		// if we don't know, default to the current language setting
		lcl_get_language_name(p->language);
	}
}

void pilotfile::plr_write_flags()
{
	startSection(Section::Flags);

	// tips
	cfile::io::write<ubyte>((unsigned char)p->tips, cfp);

	// saved flags
	cfile::io::write<int>(p->save_flags, cfp);

	// listing mode (single or campaign missions)
	cfile::io::write<int>(p->readyroom_listing_mode, cfp);

	// briefing auto-play
	cfile::io::write<int>(p->auto_advance, cfp);

	// special rank setting (to avoid having to read all stats on verify)
	// should be multi only from now on
	cfile::io::write<int>(multi_stats.rank, cfp);

	// What game mode we were in last on this pilot
	cfile::io::write<int>(p->player_was_multi, cfp);

	// which language was this pilot created with
	cfile::io::writeStringLen(p->language, cfp);

	endSection();
}

void pilotfile::plr_read_info()
{
	if ( !m_have_flags ) {
		throw "Info before Flags!";
	}

	// pilot image
	cfile::io::readStringLen(p->image_filename, MAX_FILENAME_LEN, cfp);

	// multi squad name
	cfile::io::readStringLen(p->m_squad_name, NAME_LENGTH, cfp);

	// squad image
	cfile::io::readStringLen(p->m_squad_filename, MAX_FILENAME_LEN, cfp);

	// active campaign
	cfile::io::readStringLen(p->current_campaign, MAX_FILENAME_LEN, cfp);
}

void pilotfile::plr_write_info()
{
	startSection(Section::Info);

	// pilot image
	cfile::io::writeStringLen(p->image_filename, cfp);

	// multi squad name
	cfile::io::writeStringLen(p->m_squad_name, cfp);

	// squad image
	cfile::io::writeStringLen(p->m_squad_filename, cfp);

	// active campaign
	cfile::io::writeStringLen(p->current_campaign, cfp);

	endSection();
}

void pilotfile::plr_read_hud()
{
	int idx;

	// flags
	HUD_config.show_flags = cfile::io::read<int>(cfp);
	HUD_config.show_flags2 = cfile::io::read<int>(cfp);

	HUD_config.popup_flags = cfile::io::read<int>(cfp);
	HUD_config.popup_flags2 = cfile::io::read<int>(cfp);

	// settings
	HUD_config.num_msg_window_lines = cfile::io::read<ubyte>(cfp);

	HUD_config.rp_flags = cfile::io::read<int>(cfp);
	HUD_config.rp_dist = cfile::io::read<int>(cfp);

	// basic colors
	HUD_config.main_color = cfile::io::read<int>(cfp);
	HUD_color_alpha = cfile::io::read<int>(cfp);

	if (HUD_color_alpha < HUD_COLOR_ALPHA_USER_MIN) {
		HUD_color_alpha = HUD_COLOR_ALPHA_DEFAULT;
	}

	hud_config_set_color(HUD_config.main_color);

	// gauge-specific colors
	int num_gauges = cfile::io::read<int>(cfp);

	for (idx = 0; idx < num_gauges; idx++) {
		ubyte red = cfile::io::read<ubyte>(cfp);
		ubyte green = cfile::io::read<ubyte>(cfp);
		ubyte blue = cfile::io::read<ubyte>(cfp);
		ubyte alpha = cfile::io::read<ubyte>(cfp);

		if (idx >= NUM_HUD_GAUGES) {
			continue;
		}

		HUD_config.clr[idx].red = red;
		HUD_config.clr[idx].green = green;
		HUD_config.clr[idx].blue = blue;
		HUD_config.clr[idx].alpha = alpha;
	}
}

void pilotfile::plr_write_hud()
{
	int idx;

	startSection(Section::HUD);

	// flags
	cfile::io::write<int>(HUD_config.show_flags, cfp);
	cfile::io::write<int>(HUD_config.show_flags2, cfp);

	cfile::io::write<int>(HUD_config.popup_flags, cfp);
	cfile::io::write<int>(HUD_config.popup_flags2, cfp);

	// settings
	cfile::io::write<ubyte>(HUD_config.num_msg_window_lines, cfp);

	cfile::io::write<int>(HUD_config.rp_flags, cfp);
	cfile::io::write<int>(HUD_config.rp_dist, cfp);

	// basic colors
	cfile::io::write<int>(HUD_config.main_color, cfp);
	cfile::io::write<int>(HUD_color_alpha, cfp);

	// gauge-specific colors
	cfile::io::write<int>(NUM_HUD_GAUGES, cfp);

	for (idx = 0; idx < NUM_HUD_GAUGES; idx++) {
		cfile::io::write<ubyte>(HUD_config.clr[idx].red, cfp);
		cfile::io::write<ubyte>(HUD_config.clr[idx].green, cfp);
		cfile::io::write<ubyte>(HUD_config.clr[idx].blue, cfp);
		cfile::io::write<ubyte>(HUD_config.clr[idx].alpha, cfp);
	}

	endSection();
}

void pilotfile::plr_read_variables()
{
	int list_size = 0;
	int idx;
	sexp_variable n_var;

	list_size = cfile::io::read<int>(cfp);

	if (list_size <= 0) {
		return;
	}

	p->variables.reserve(list_size);

	for (idx = 0; idx < list_size; idx++) {
		n_var.type = cfile::io::read<int>(cfp);
		cfile::io::readStringLen(n_var.text, TOKEN_LENGTH, cfp);
		cfile::io::readStringLen(n_var.variable_name, TOKEN_LENGTH, cfp);

		p->variables.push_back( n_var );
	}
}

void pilotfile::plr_write_variables()
{
	int list_size = 0;
	int idx;

	startSection(Section::Variables);

	list_size = (int)p->variables.size();

	cfile::io::write<int>(list_size, cfp);

	for (idx = 0; idx < list_size; idx++) {
		cfile::io::write<int>(p->variables[idx].type, cfp);
		cfile::io::writeStringLen(p->variables[idx].text, cfp);
		cfile::io::writeStringLen(p->variables[idx].variable_name, cfp);
	}

	endSection();
}

void pilotfile::plr_read_multiplayer()
{
	// netgame options
	p->m_server_options.squad_set = cfile::io::read<ubyte>(cfp);
	p->m_server_options.endgame_set = cfile::io::read<ubyte>(cfp);
	p->m_server_options.flags = cfile::io::read<int>(cfp);
	p->m_server_options.respawn = cfile::io::read<uint>(cfp);
	p->m_server_options.max_observers = cfile::io::read<ubyte>(cfp);
	p->m_server_options.skill_level = cfile::io::read<ubyte>(cfp);
	p->m_server_options.voice_qos = cfile::io::read<ubyte>(cfp);
	p->m_server_options.voice_token_wait = cfile::io::read<int>(cfp);
	p->m_server_options.voice_record_time = cfile::io::read<int>(cfp);
	p->m_server_options.mission_time_limit = (fix)cfile::io::read<int>(cfp);
	p->m_server_options.kill_limit = cfile::io::read<int>(cfp);

	// local options
	p->m_local_options.flags = cfile::io::read<int>(cfp);
	p->m_local_options.obj_update_level = cfile::io::read<int>(cfp);

	// netgame protocol
	Multi_options_g.protocol = cfile::io::read<int>(cfp);

	if (Multi_options_g.protocol == NET_VMT) {
		Multi_options_g.protocol = NET_TCP;
	}

	Assert( (Multi_options_g.protocol == NET_IPX) || (Multi_options_g.protocol == NET_TCP) );
}

void pilotfile::plr_write_multiplayer()
{
	startSection(Section::Multiplayer);

	// netgame options
	cfile::io::write<ubyte>(p->m_server_options.squad_set, cfp);
	cfile::io::write<ubyte>(p->m_server_options.endgame_set, cfp);
	cfile::io::write<int>(p->m_server_options.flags, cfp);
	cfile::io::write<uint>(p->m_server_options.respawn, cfp);
	cfile::io::write<ubyte>(p->m_server_options.max_observers, cfp);
	cfile::io::write<ubyte>(p->m_server_options.skill_level, cfp);
	cfile::io::write<ubyte>(p->m_server_options.voice_qos, cfp);
	cfile::io::write<int>(p->m_server_options.voice_token_wait, cfp);
	cfile::io::write<int>(p->m_server_options.voice_record_time, cfp);
	cfile::io::write<int>((int)p->m_server_options.mission_time_limit, cfp);
	cfile::io::write<int>(p->m_server_options.kill_limit, cfp);

	// local options
	cfile::io::write<int>(p->m_local_options.flags, cfp);
	cfile::io::write<int>(p->m_local_options.obj_update_level, cfp);

	// netgame protocol
	cfile::io::write<int>(Multi_options_g.protocol, cfp);

	endSection();
}

void pilotfile::plr_read_stats()
{
	int idx, j, list_size = 0;
	index_list_t ilist;
	char t_string[NAME_LENGTH+1];

	// global, all-time stats (used only until campaign stats are loaded)
	all_time_stats.score = cfile::io::read<int>(cfp);
	all_time_stats.rank = cfile::io::read<int>(cfp);
	all_time_stats.assists = cfile::io::read<int>(cfp);
	all_time_stats.kill_count = cfile::io::read<int>(cfp);
	all_time_stats.kill_count_ok = cfile::io::read<int>(cfp);
	all_time_stats.bonehead_kills = cfile::io::read<int>(cfp);

	all_time_stats.p_shots_fired = cfile::io::read<uint>(cfp);
	all_time_stats.p_shots_hit = cfile::io::read<uint>(cfp);
	all_time_stats.p_bonehead_hits = cfile::io::read<uint>(cfp);

	all_time_stats.s_shots_fired = cfile::io::read<uint>(cfp);
	all_time_stats.s_shots_hit = cfile::io::read<uint>(cfp);
	all_time_stats.s_bonehead_hits = cfile::io::read<uint>(cfp);

	all_time_stats.flight_time = cfile::io::read<uint>(cfp);
	all_time_stats.missions_flown = cfile::io::read<uint>(cfp);
	all_time_stats.last_flown = (_fs_time_t)cfile::io::read<int>(cfp);
	all_time_stats.last_backup = (_fs_time_t)cfile::io::read<int>(cfp);

	// ship kills (contains ships across all mods, not just current)
	list_size = cfile::io::read<int>(cfp);
	all_time_stats.ship_kills.reserve(list_size);

	for (idx = 0; idx < list_size; idx++) {
		cfile::io::readStringLen(t_string, NAME_LENGTH, cfp);

		ilist.name = t_string;
		ilist.index = ship_info_lookup(t_string);
		ilist.val = cfile::io::read<int>(cfp);

		all_time_stats.ship_kills.push_back(ilist);
	}

	// medals earned (contains medals across all mods, not just current)
	list_size = cfile::io::read<int>(cfp);
	all_time_stats.medals_earned.reserve(list_size);

	for (idx = 0; idx < list_size; idx++) {
		cfile::io::readStringLen(t_string, NAME_LENGTH,cfp);

		ilist.name = t_string;
		ilist.index = medals_info_lookup(t_string);
		ilist.val = cfile::io::read<int>(cfp);

		all_time_stats.medals_earned.push_back(ilist);
	}

	// if not in multiplayer mode then set these stats as the player stats
	if ( !(Game_mode & GM_MULTIPLAYER) ) {
		p->stats.score = all_time_stats.score;
		p->stats.rank = all_time_stats.rank;
		p->stats.assists = all_time_stats.assists;
		p->stats.kill_count = all_time_stats.kill_count;
		p->stats.kill_count_ok = all_time_stats.kill_count_ok;
		p->stats.bonehead_kills = all_time_stats.bonehead_kills;

		p->stats.p_shots_fired = all_time_stats.p_shots_fired;
		p->stats.p_shots_hit = all_time_stats.p_shots_hit;
		p->stats.p_bonehead_hits = all_time_stats.p_bonehead_hits;

		p->stats.s_shots_fired = all_time_stats.s_shots_fired;
		p->stats.s_shots_hit = all_time_stats.s_shots_hit;
		p->stats.s_bonehead_hits = all_time_stats.s_bonehead_hits;

		p->stats.flight_time = all_time_stats.flight_time;
		p->stats.missions_flown = all_time_stats.missions_flown;
		p->stats.last_flown = all_time_stats.last_flown;
		p->stats.last_backup = all_time_stats.last_backup;

		// ship kills (have to find ones that match content)
		list_size = (int)all_time_stats.ship_kills.size();
		for (idx = 0; idx < list_size; idx++) {
			j = all_time_stats.ship_kills[idx].index;

			if (j >= 0) {
				p->stats.kills[j] = all_time_stats.ship_kills[idx].val;
			}
		}

		// medals earned (have to find ones that match content)
		list_size = (int)all_time_stats.medals_earned.size();
		for (idx = 0; idx < list_size; idx++) {
			j = all_time_stats.medals_earned[idx].index;

			if (j >= 0) {
				p->stats.medal_counts[j] = all_time_stats.medals_earned[idx].val;
			}
		}
	}
}

void pilotfile::plr_write_stats()
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

void pilotfile::plr_read_stats_multi()
{
	int idx, j, list_size = 0;
	index_list_t ilist;
	char t_string[NAME_LENGTH+1];

	// global, all-time stats (used only until campaign stats are loaded)
	multi_stats.score = cfile::io::read<int>(cfp);
	multi_stats.rank = cfile::io::read<int>(cfp);
	multi_stats.assists = cfile::io::read<int>(cfp);
	multi_stats.kill_count = cfile::io::read<int>(cfp);
	multi_stats.kill_count_ok = cfile::io::read<int>(cfp);
	multi_stats.bonehead_kills = cfile::io::read<int>(cfp);

	multi_stats.p_shots_fired = cfile::io::read<uint>(cfp);
	multi_stats.p_shots_hit = cfile::io::read<uint>(cfp);
	multi_stats.p_bonehead_hits = cfile::io::read<uint>(cfp);

	multi_stats.s_shots_fired = cfile::io::read<uint>(cfp);
	multi_stats.s_shots_hit = cfile::io::read<uint>(cfp);
	multi_stats.s_bonehead_hits = cfile::io::read<uint>(cfp);

	multi_stats.flight_time = cfile::io::read<uint>(cfp);
	multi_stats.missions_flown = cfile::io::read<uint>(cfp);
	multi_stats.last_flown = (_fs_time_t)cfile::io::read<int>(cfp);
	multi_stats.last_backup = (_fs_time_t)cfile::io::read<int>(cfp);

	// ship kills (contains ships across all mods, not just current)
	list_size = cfile::io::read<int>(cfp);
	multi_stats.ship_kills.reserve(list_size);

	for (idx = 0; idx < list_size; idx++) {
		cfile::io::readStringLen(t_string, NAME_LENGTH, cfp);

		ilist.name = t_string;
		ilist.index = ship_info_lookup(t_string);
		ilist.val = cfile::io::read<int>(cfp);

		multi_stats.ship_kills.push_back(ilist);
	}

	// medals earned (contains medals across all mods, not just current)
	list_size = cfile::io::read<int>(cfp);
	multi_stats.medals_earned.reserve(list_size);

	for (idx = 0; idx < list_size; idx++) {
		cfile::io::readStringLen(t_string, NAME_LENGTH,cfp);

		ilist.name = t_string;
		ilist.index = medals_info_lookup(t_string);
		ilist.val = cfile::io::read<int>(cfp);

		multi_stats.medals_earned.push_back(ilist);
	}

	// if in multiplayer mode then set these stats as the player stats
	if (Game_mode & GM_MULTIPLAYER) {
		p->stats.score = multi_stats.score;
		p->stats.rank = multi_stats.rank;
		p->stats.assists = multi_stats.assists;
		p->stats.kill_count = multi_stats.kill_count;
		p->stats.kill_count_ok = multi_stats.kill_count_ok;
		p->stats.bonehead_kills = multi_stats.bonehead_kills;

		p->stats.p_shots_fired = multi_stats.p_shots_fired;
		p->stats.p_shots_hit = multi_stats.p_shots_hit;
		p->stats.p_bonehead_hits = multi_stats.p_bonehead_hits;

		p->stats.s_shots_fired = multi_stats.s_shots_fired;
		p->stats.s_shots_hit = multi_stats.s_shots_hit;
		p->stats.s_bonehead_hits = multi_stats.s_bonehead_hits;

		p->stats.flight_time = multi_stats.flight_time;
		p->stats.missions_flown = multi_stats.missions_flown;
		p->stats.last_flown = multi_stats.last_flown;
		p->stats.last_backup = multi_stats.last_backup;

		// ship kills (have to find ones that match content)
		list_size = (int)multi_stats.ship_kills.size();
		for (idx = 0; idx < list_size; idx++) {
			j = multi_stats.ship_kills[idx].index;

			if (j >= 0) {
				p->stats.kills[j] = multi_stats.ship_kills[idx].val;
			}
		}

		// medals earned (have to find ones that match content)
		list_size = (int)multi_stats.medals_earned.size();
		for (idx = 0; idx < list_size; idx++) {
			j = multi_stats.medals_earned[idx].index;

			if (j >= 0) {
				p->stats.medal_counts[j] = multi_stats.medals_earned[idx].val;
			}
		}
	}
}

void pilotfile::plr_write_stats_multi()
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

void pilotfile::plr_read_controls()
{
	int idx, list_size, list_axis;
	short id1, id2, id3 __attribute__((__unused__));
	int axi, inv;

	list_size = (int)cfile::io::read<ushort>(cfp);
	for (idx = 0; idx < list_size; idx++) {
		id1 = cfile::io::read<short>(cfp);
		id2 = cfile::io::read<short>(cfp);
		id3 = cfile::io::read<short>(cfp);	// unused, at the moment

		if (idx < CCFG_MAX) {
			Control_config[idx].key_id = id1;
			Control_config[idx].joy_id = id2;
		}
	}

	list_axis = cfile::io::read<int>(cfp);
	for (idx = 0; idx < list_axis; idx++) {
		axi = cfile::io::read<int>(cfp);
		inv = cfile::io::read<int>(cfp);

		if (idx < NUM_JOY_AXIS_ACTIONS) {
			Axis_map_to[idx] = axi;
			Invert_axis[idx] = inv;
		}
	}
}

void pilotfile::plr_write_controls()
{
	int idx;

	startSection(Section::Controls);

	cfile::io::write<short>(CCFG_MAX, cfp);

	for (idx = 0; idx < CCFG_MAX; idx++) {
		cfile::io::write<short>(Control_config[idx].key_id, cfp);
		cfile::io::write<short>(Control_config[idx].joy_id, cfp);
		// placeholder? for future mouse_id?
		cfile::io::write<short>(-1, cfp);
	}

	cfile::io::write<int>(NUM_JOY_AXIS_ACTIONS, cfp);

	for (idx = 0; idx < NUM_JOY_AXIS_ACTIONS; idx++) {
		cfile::io::write<int>(Axis_map_to[idx], cfp);
		cfile::io::write<int>(Invert_axis[idx], cfp);
	}

	endSection();
}

void pilotfile::plr_read_settings()
{
	// sound/voice/music
	Master_sound_volume = cfile::io::read<float>(cfp);
	Master_event_music_volume = cfile::io::read<float>(cfp);
	Master_voice_volume = cfile::io::read<float>(cfp);

	audiostream_set_volume_all(Master_voice_volume, ASF_VOICE);
	audiostream_set_volume_all(Master_event_music_volume, ASF_EVENTMUSIC);

	if (Master_event_music_volume > 0.0f) {
		Event_music_enabled = 1;
	} else {
		Event_music_enabled = 0;
	}

	Briefing_voice_enabled = cfile::io::read<int>(cfp);

	// skill level
	Game_skill_level = cfile::io::read<int>(cfp);

	// input options
	Use_mouse_to_fly = cfile::io::read<int>(cfp);
	Mouse_sensitivity = cfile::io::read<int>(cfp);
	Joy_sensitivity = cfile::io::read<int>(cfp);
	Dead_zone_size = cfile::io::read<int>(cfp);

	// detail
	Detail.setting = cfile::io::read<int>(cfp);
	Detail.nebula_detail = cfile::io::read<int>(cfp);
	Detail.detail_distance = cfile::io::read<int>(cfp);
	Detail.hardware_textures = cfile::io::read<int>(cfp);
	Detail.num_small_debris = cfile::io::read<int>(cfp);
	Detail.num_particles = cfile::io::read<int>(cfp);
	Detail.num_stars = cfile::io::read<int>(cfp);
	Detail.shield_effects = cfile::io::read<int>(cfp);
	Detail.lighting = cfile::io::read<int>(cfp);
	Detail.targetview_model = cfile::io::read<int>(cfp);
	Detail.planets_suns = cfile::io::read<int>(cfp);
	Detail.weapon_extras = cfile::io::read<int>(cfp);
}

void pilotfile::plr_write_settings()
{
	startSection(Section::Settings);

	// sound/voice/music
	cfile::io::write<float>(Master_sound_volume, cfp);
	cfile::io::write<float>(Master_event_music_volume, cfp);
	cfile::io::write<float>(Master_voice_volume, cfp);

	cfile::io::write<int>(Briefing_voice_enabled, cfp);

	// skill level
	cfile::io::write<int>(Game_skill_level, cfp);

	// input options
	cfile::io::write<int>(Use_mouse_to_fly, cfp);
	cfile::io::write<int>(Mouse_sensitivity, cfp);
	cfile::io::write<int>(Joy_sensitivity, cfp);
	cfile::io::write<int>(Dead_zone_size, cfp);

	// detail
	cfile::io::write<int>(Detail.setting, cfp);
	cfile::io::write<int>(Detail.nebula_detail, cfp);
	cfile::io::write<int>(Detail.detail_distance, cfp);
	cfile::io::write<int>(Detail.hardware_textures, cfp);
	cfile::io::write<int>(Detail.num_small_debris, cfp);
	cfile::io::write<int>(Detail.num_particles, cfp);
	cfile::io::write<int>(Detail.num_stars, cfp);
	cfile::io::write<int>(Detail.shield_effects, cfp);
	cfile::io::write<int>(Detail.lighting, cfp);
	cfile::io::write<int>(Detail.targetview_model, cfp);
	cfile::io::write<int>(Detail.planets_suns, cfp);
	cfile::io::write<int>(Detail.weapon_extras, cfp);

	endSection();
}

void pilotfile::plr_reset_data()
{
	// internals
	m_have_flags = false;
	m_have_info = false;

	m_data_invalid = false;

	// set all the entries in the control config arrays to -1 (undefined)
	control_config_clear();

	// init stats
	p->stats.init();

	// reset scoring lists
	all_time_stats.ship_kills.clear();
	all_time_stats.medals_earned.clear();

	multi_stats.ship_kills.clear();
	multi_stats.medals_earned.clear();

	// clear variables
	p->variables.clear();

	// reset techroom to defaults (CSG will override this, multi will use defaults)
	tech_reset_to_default();
}

void pilotfile::plr_close()
{
	if (cfp) {
		cfile::io::close(cfp);
		cfp = NULL;
	}

	p = NULL;
	filename = "";

	ship_list.clear();
	weapon_list.clear();
	intel_list.clear();
	medals_list.clear();

	m_have_flags = false;
	m_have_info = false;
}

bool pilotfile::load_player(const char *callsign, player *_p)
{
	// if we're a standalone server in multiplayer, just fill in some bogus values
	// since we don't have a pilot file
	if ( (Game_mode & GM_MULTIPLAYER) && (Game_mode & GM_STANDALONE_SERVER) ) {
		Player->insignia_texture = -1;
		strcpy_s(Player->callsign, NOX("Standalone"));
		strcpy_s(Player->short_callsign, NOX("Standalone"));

		return true;
	}

	// set player ptr first thing
	p = _p;

	if ( !p ) {
		Assert( (Player_num >= 0) && (Player_num < MAX_PLAYERS) );
		p = &Players[Player_num];
	}

	filename = callsign;
	filename += ".plr";

	if ( filename.size() == 4 ) {
		mprintf(("PLR => Invalid filename '%s'!\n", filename.c_str()));
		return false;
	}

	cfp = cfile::io::open(filename, cfile::MODE_READ, cfile::OPEN_NORMAL, cfile::TYPE_PLAYERS);

	if ( !cfp ) {
		mprintf(("PLR => Unable to open '%s' for reading!\n", filename.c_str()));
		return false;
	}

	unsigned int plr_id = cfile::io::read<uint>(cfp);

	if (plr_id != PLR_FILE_ID) {
		mprintf(("PLR => Invalid header id for '%s'!\n", filename.c_str()));
		plr_close();
		return false;
	}

	// version, now used
	version = cfile::io::read<ubyte>(cfp);

	mprintf(("PLR => Loading '%s' with version %d...\n", filename.c_str(), version));

	plr_reset_data();

	// the point of all this: read in the PLR contents
	while ( !cfile::io::eof(cfp) ) {
		ushort section_id = cfile::io::read<ushort>(cfp);
		uint section_size = cfile::io::read<uint>(cfp);

		size_t start_pos = cfile::io::tell(cfp);

		// safety, to help protect against long reads
		cfile::io::setMaxReadLength(cfp, section_size);

		try {
			switch (section_id) {
				case Section::Flags:
					mprintf(("PLR => Parsing:  Flags...\n"));
					m_have_flags = true;
					plr_read_flags();
					break;

				case Section::Info:
					mprintf(("PLR => Parsing:  Info...\n"));
					m_have_info = true;
					plr_read_info();
					break;

				case Section::Variables:
					mprintf(("PLR => Parsing:  Variables...\n"));
					plr_read_variables();
					break;

				case Section::HUD:
					mprintf(("PLR => Parsing:  HUD...\n"));
					plr_read_hud();
					break;

				case Section::Scoring:
					mprintf(("PLR => Parsing:  Scoring...\n"));
					plr_read_stats();
					break;

				case Section::ScoringMulti:
					mprintf(("PLR => Parsing:  ScoringMulti...\n"));
					plr_read_stats_multi();
					break;

				case Section::Multiplayer:
					mprintf(("PLR => Parsing:  Multiplayer...\n"));
					plr_read_multiplayer();
					break;

				case Section::Controls:
					mprintf(("PLR => Parsing:  Controls...\n"));
					plr_read_controls();
					break;

				case Section::Settings:
					mprintf(("PLR => Parsing:  Settings...\n"));
					plr_read_settings();
					break;

				default:
					mprintf(("PLR => Skipping unknown section 0x%04x!\n", section_id));
					break;
			}
		} catch (cfile::MaxReadLengthException &msg) {
			// read to max section size, move to next section, discarding
			// extra/unknown data
			mprintf(("PLR => (0x%04x) %s\n", section_id, msg.what()));
		} catch (const char *err) {
			mprintf(("PLR => ERROR: %s\n", err));
			plr_close();
			return false;
		}

		// reset safety catch
		cfile::io::setMaxReadLength(cfp, 0);

		// skip to next section (if not already there)
		size_t offset_pos = (start_pos + section_size) - cfile::io::tell(cfp);

		if (offset_pos) {
			cfile::io::seek(cfp, offset_pos, cfile::SEEK_MODE_CUR);
			mprintf(("PLR => WARNING: Advancing to the next section. %i bytes were skipped!\n", offset_pos));
		}
	}

	// restore the callsign into the Player structure
	strcpy_s(p->callsign, callsign);

	// restore the truncated callsign into Player structure
	pilot_set_short_callsign(p, SHORT_CALLSIGN_PIXEL_W);

	player_set_squad_bitmap(p, p->m_squad_filename, true);

	hud_squadmsg_save_keys();

	// set last pilot
	os_config_write_string(NULL, "LastPlayer", (char*)callsign);

	mprintf(("PLR => Loading complete!\n"));

	// cleanup and return
	plr_close();

	return true;
}

bool pilotfile::save_player(player *_p)
{
	// never save a pilot file for the standalone server in multiplayer
	if ( (Game_mode & GM_MULTIPLAYER) && (Game_mode & GM_STANDALONE_SERVER) ) {
		return false;
	}

	// set player ptr first thing
	p = _p;

	if ( !p ) {
		Assert( (Player_num >= 0) && (Player_num < MAX_PLAYERS) );
		p = &Players[Player_num];
	}

	if ( !strlen(p->callsign) ) {
		return false;
	}

	filename = p->callsign;
	filename += ".plr";

	if ( filename.size() == 4 ) {
		mprintf(("PLR => Invalid filename '%s'!\n", filename.c_str()));
		return false;
	}

	// open it, hopefully...
	cfp = cfile::io::open(filename, cfile::MODE_WRITE, cfile::OPEN_NORMAL, cfile::TYPE_PLAYERS);

	if ( !cfp ) {
		mprintf(("PLR => Unable to open '%s' for saving!\n", filename.c_str()));
		return false;
	}

	// header and version
	cfile::io::write<int>(PLR_FILE_ID, cfp);
	cfile::io::write<ubyte>(PLR_VERSION, cfp);

	mprintf(("PLR => Saving '%s' with version %d...\n", filename.c_str(), (int)PLR_VERSION));

	// flags and info sections go first
	mprintf(("PLR => Saving:  Flags...\n"));
	plr_write_flags();
	mprintf(("PLR => Saving:  Info...\n"));
	plr_write_info();

	// everything else is next, not order specific
	mprintf(("PLR => Saving:  Scoring...\n"));
	plr_write_stats();
	mprintf(("PLR => Saving:  ScoringMulti...\n"));
	plr_write_stats_multi();
	mprintf(("PLR => Saving:  HUD...\n"));
	plr_write_hud();
	mprintf(("PLR => Saving:  Variables...\n"));
	plr_write_variables();
	mprintf(("PLR => Saving:  Multiplayer...\n"));
	plr_write_multiplayer();
	mprintf(("PLR => Saving:  Controls...\n"));
	plr_write_controls();
	mprintf(("PLR => Saving:  Settings...\n"));
	plr_write_settings();

	// Done!
	mprintf(("PLR => Saving complete!\n"));

	plr_close();

	return true;
}

bool pilotfile::verify(const char *fname, int *rank, char *valid_language)
{
	player t_plr;

	// set player ptr first thing
	p = &t_plr;

	filename = fname;

	if ( filename.size() == 4 ) {
		mprintf(("PLR => Invalid filename '%s'!\n", filename.c_str()));
		return false;
	}

	cfp = cfile::io::open((char*)filename.c_str(), cfile::MODE_READ, cfile::OPEN_NORMAL, cfile::TYPE_PLAYERS);

	if ( !cfp ) {
		mprintf(("PLR => Unable to open '%s'!\n", filename.c_str()));
		return false;
	}

	unsigned int plr_id = cfile::io::read<uint>(cfp);

	if (plr_id != PLR_FILE_ID) {
		mprintf(("PLR => Invalid header id for '%s'!\n", filename.c_str()));
		plr_close();
		return false;
	}

	// version, now used
	version = cfile::io::read<ubyte>(cfp);

	mprintf(("PLR => Verifying '%s' with version %d...\n", filename.c_str(), (int)version));

	// the point of all this: read in the PLR contents
	while ( !(m_have_flags && m_have_info) && !cfile::io::eof(cfp) ) {
		ushort section_id = cfile::io::read<ushort>(cfp);
		uint section_size = cfile::io::read<uint>(cfp);

		size_t start_pos = cfile::io::tell(cfp);

		// safety, to help protect against long reads
		cfile::io::setMaxReadLength(cfp, section_size);

		try {
			switch (section_id) {
				case Section::Flags:
					mprintf(("PLR => Parsing:  Flags...\n"));
					m_have_flags = true;
					plr_read_flags();
					break;

				// now reading the Info section to get the campaign
				// and be able to lookup the campaign rank
				case Section::Info:
					mprintf(("PLR => Parsing:  Info...\n"));
					m_have_info = true;
					plr_read_info();
					break;

				default:
					break;
			}
		} catch (cfile::MaxReadLengthException &msg) {
			// read to max section size, move to next section, discarding
			// extra/unknown data
			mprintf(("PLR => (0x%04x) %s\n", section_id, msg.what()));
		} catch (const char *err) {
			mprintf(("PLR => ERROR: %s\n", err));
			plr_close();
			return false;
		}

		// reset safety catch
		cfile::io::setMaxReadLength(cfp, 0);

		// skip to next section (if not already there)
		size_t offset_pos = (start_pos + section_size) - cfile::io::tell(cfp);

		if (offset_pos) {
			mprintf(("PLR => Warning: (0x%04x) Short read, information may have been lost!\n", section_id));
			cfile::io::seek(cfp, offset_pos, cfile::SEEK_MODE_CUR);
		}
	}

	if (valid_language) {
		strncpy(valid_language, p->language, sizeof(p->language));
	}

	// need to cleanup early to ensure everything is OK for use in the CSG next
	// also means we can't use *p from now on, use t_plr instead for a few vars
	plr_close();

	if (rank) {
		// maybe get the rank from the CSG
		if ( !(Game_mode & GM_MULTIPLAYER) ) {
			// build the csg filename
			// since filename/fname was validated above, perform less safety checks here
			filename = fname;
			filename = filename.replace(filename.find_last_of('.')+1,filename.npos, t_plr.current_campaign);
			filename.append(".csg");

			if (!this->get_csg_rank(rank)) {
				// if we failed to get the csg rank, default to multi rank
				*rank = t_plr.stats.rank;
			}
		} else {
			// if the CSG isn't valid, or for multi, use this rank
			*rank = t_plr.stats.rank;
		}
	}

	mprintf(("PLR => Verifying complete!\n"));

	return true;
}

