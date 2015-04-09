#pragma once
/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell
 * or otherwise commercially exploit the source or things you created based on the
 * source.
 *
*/



#include "mission/missiongrid.h"

#define BRIEFING_LOOKAT_POINT_ID	99999

extern matrix	Grid_gmatrix;
extern vec3d	Grid_center;
extern int	Aa_gridlines;
extern int	player_start1;
extern int	Editing_mode;
extern int	Control_mode;
extern int	Show_grid;
extern int	Show_grid_positions;
extern int	Show_coordinates;
extern int	Show_outlines;
extern int	Single_axis_constraint;
extern int	Show_distances;
extern int	Universal_heading;
extern int	Flying_controls_mode;
extern int	Group_rotate;
extern int	Show_horizon;
extern int	Lookat_mode;
extern int	True_rw, True_rh;
extern int	Fixed_briefing_size;
extern vec3d	Tp1, Tp2;  // test points
extern physics_info view_physics;
extern vec3d view_pos, eye_pos;
extern matrix view_orient, eye_orient;
class object;
class ship_subsys;
///! \fixme This does NOT belong here. Used for porting and testing purposes ONLY!
struct subsys_to_render {
    bool		do_render;
    object  	*ship_obj;
    ship_subsys *cur_subsys;
};

///! \fixme does NOT belong here.
struct Marking_box {
        int x1, y1, x2, y2;
};

void fred_render_init();
void move_mouse(int btn, int mdx, int mdy);
void game_do_frame(const int view_obj, const int viewpoint, const int cur_object_index, const int Cursor_over);
void render_frame(
    int cur_object_index, subsys_to_render &Render_subsys,
    bool box_marking, const Marking_box &marking_box,
    int Cursor_over,
    bool Show_starts, bool Show_ships, bool Show_iff[],
    bool Show_ship_info, bool Show_ship_models, bool Show_dock_points, bool Show_paths_fred,
    bool Bg_bitmap_dialog, bool Render_compass,
    bool Lighting_on, bool FullDetail
);
int select_object(
    int cx, int cy,
    bool Selection_lock,
    bool Show_starts, bool Show_ships, bool Show_iff[],
    bool Show_ship_models);
// viewpoint -> attach camera to current ship.
// cur_obj -> ship viewed.
void level_controlled(const int viewpoint, const int cur_obj);
void verticalize_controlled(const int viewpoint, const int cur_obj);

