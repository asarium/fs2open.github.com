/*
 * Created for the FreeSpace2 Source Code Project.
 *
 * You may not sell or otherwise commercially exploit the source or things you
 * create based on the source.
 */

#include "wxFredRender.h"
#include "wxGraphicsOperations.h"

#include <globalincs/alphacolors.h>
#include <globalincs/pstypes.h>
#include <globalincs/vmallocator.h>
#include <graphics/2d.h>
#include <graphics/font.h>
#include <lighting/lighting.h>
#include <math/vecmat.h>
#include <osapi/osapi.h>
#include <parse/parselo.h>
#include <physics/physics.h>
#include <render/3d.h>

#include <SDL_loadso.h>

#include <wx/glcanvas.h>
#include <wx/window.h>

using namespace wxfred;

const float FRED_DEFAULT_HTL_FOV = 0.485f;

static bool fred_inited = false;

// Colors used for 2d rendering
color colour_black;
color colour_green;
color colour_white;
color colour_yellow;

/**
 * @brief Renders the asteroid field
 */
void render_asteroid_field();

/**
 * @brief Renders the compass widget
 */
void render_compass();

/**
 * @brief Renders the grid widget
 */
void render_grid(grid* grid_p);

/**
 * @brief Renders all modeled objects within the mission
 */
void render_models();

/**
* @brief Displays/Renders the distances between selected objects
*/
void display_distances();

/**
 * @brief Highlights the currently selected skybox bitmap
 */
void hilight_bitmap();


void render_asteroid_field() {}

void render_compass() {}

void render_grid(grid* grid_p) {}

void render_models() {}

void display_distances() {}

void hilight_bitmap() {
	// Currently disabled for now.
	/*
	int i;
	vertex p[4];

	if (Starfield_bitmaps[Cur_bitmap].bitmap_index == -1)  // can't draw if no bitmap
	return;

	for (i=0; i<4; i++)
	{
	g3_rotate_faraway_vertex(&p[i], &Starfield_bitmaps[Cur_bitmap].points[i]);
	if (p[i].codes & CC_BEHIND)
	return;

	g3_project_vertex(&p[i]);
	if (p[i].flags & PF_OVERFLOW)
	return;
	}

	gr_set_color(255, 255, 255);
	g3_draw_line(&p[0], &p[1]);
	g3_draw_line(&p[1], &p[2]);
	g3_draw_line(&p[2], &p[3]);
	g3_draw_line(&p[3], &p[0]);
	*/
}


void wxfred::render_init(glcViewport* win) {
	if (!fred_inited) {
		// Create the GraphicsOperations helper object with the target window
		std::unique_ptr<wxGraphicsOperations> graphicsOperations(new wxGraphicsOperations(win));

		// Do graphics init
		gr_init(std::move(graphicsOperations), GR_OPENGL, 640, 480, 32);

		font::init();

		gr_set_gamma(3.0f);

		// sprintf(palette_filename, "gamepalette%d-%02d", 1, 1);
		// mprintf(("Loading palette %s\n", palette_filename));
		// palette_load_table(palette_filename);

		// particle::ParticleManager::init();

		alpha_colors_init();
		// glowpoint_init();
		// neb2_init();
		// stars_init();
		// brief_init_colors();
		// stars_post_level_init();
		// nebl_init();

		gr_init_alphacolor(&colour_white, 255, 255, 255, 255);
		gr_init_alphacolor(&colour_green, 0, 200, 0, 255);
		gr_init_alphacolor(&colour_yellow, 200, 255, 0, 255);
		gr_init_alphacolor(&colour_black, 0, 0, 0, 255);

		gr_reset_clip();
		g3_start_frame(0);
		g3_set_view_matrix(&win->vset.c_pos, &win->vset.c_orient, 0.5f);

		fred_inited = true;
	} else {
		// Set render target to window?
	}
}

void wxfred::render_frame(glcViewport *win) {
	if (!fred_inited) {
		// TODO: Maybe fix the calling code so that this check doesn't need to be here
		// This can happen if a dialog is shown before the render init is complete
		return;
	}

	Assertion(fred_inited, "Call to render_frame was made before render_init!\n");

	// Caller viewport must set context as current before entering!!
	// Caller viewport must swap buffers after we've rendered!

	// @note The following is essentially copypasty from fredrender::render_frame()
	g3_end_frame();	 // ** Accounted for

	gr_reset_clip();
	gr_clear();

	// Briefing dialog stuff goes here, in FRED.

	g3_start_frame(1);
	font::set_font(font::FONT1);
	light_reset();

	g3_set_view_matrix(&win->vset.c_pos, &win->vset.c_orient, FRED_DEFAULT_HTL_FOV);

	// fred_enable_htl();
	// Bg_bitmap_dialog?
	// fred_disable_htl();

	if (win->vset.show_horizon) {
		gr_set_color(128, 128, 64);
		g3_draw_horizon_line();
	}

	if (win->vset.show_asteroids) {
		gr_set_color(192, 96, 16);
		render_asteroid_field();
	}

	if (win->vset.show_grid) {
		render_grid(win->_grid);
	}

	//	if (Bg_bitmap_dialog) {
	if (false) {
		hilight_bitmap();
	}

	gr_set_color(0, 0, 64);
	render_models();

	if (win->vset.show_distances) {
		display_distances();
	}

	/*
	display_ship_info();
	display_active_ship_subsystem();
	render_active_rect();
	*/

	// Fred tooltip stuff here

	gr_set_color(0, 160, 0);
	/*
	fred_enable_htl();
	jumpnode_render_all();
	fred_disable_htl();
	*/

	auto c_pos = win->vset.c_pos;
	auto c_orient = win->vset.c_orient;
	SCP_string buf;
	int w, h;	// Used for displaying current position text

	sprintf(buf, "(%.1f,%.1f,%.1f)", c_pos.xyz.x, c_pos.xyz.y, c_pos.xyz.z);
	gr_get_string_size(&w, &h, buf.c_str());
	gr_set_color_fast(&colour_white);
	gr_string(gr_screen.max_w - w - 2, 2, buf.c_str());

	g3_end_frame();	 // ** Accounted for
	render_compass();

	gr_flip();

	gr_reset_clip();

	g3_start_frame(0);	 // ** Accounted for
	g3_set_view_matrix(&c_pos, &c_orient, FRED_DEFAULT_HTL_FOV);
}
