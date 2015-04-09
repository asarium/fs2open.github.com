
#pragma once

#include <globalincs/pstypes.h>
#include <physics/physics.h>
#include <globalincs/alphacolors.h>
#include "fredrender.h"

struct grid;
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

namespace fred
{
    class FredRenderer
    {
        /**
         * A lot of this stuff doesn't belong here
         * @todo: Move camera stuff into own class
         */
        int	last_x = 0;
        int last_y = 0;

        vec3d Last_eye_pos;

        vec3d view_pos;
        vec3d eye_pos;
        vec3d Grid_center;
        vec3d Viewer_pos;
        vec3d Tp1;
        vec3d Tp2;  // test points
        matrix Grid_gmatrix;
        vec3d Last_control_pos = vmd_zero_vector;
        vec3d my_pos = { { 0.0f, 0.0f, -5.0f } };
        matrix view_orient = vmd_identity_matrix;
        matrix eye_orient;
        physics_info view_physics;
        control_info view_controls;

        int	Control_mode = 0;
        int	Flying_controls_mode = 1;
        int	Universal_heading = 0;
        int	Group_rotate = 1;
        int	Lookat_mode = 0;
        int	Last_cursor_over = -1;
        int	Show_stars = 1;
        int	Show_horizon = 0;
        int	Show_grid = 1;
        int	Show_distances = 1;
        int	Show_asteroid_field = 1;

        color colour_white;
        color colour_green;
        color colour_black;
        color colour_yellow;

        matrix my_orient = vmd_identity_matrix;
        matrix trackball_orient = vmd_identity_matrix;
        matrix Last_eye_orient = vmd_identity_matrix;
        matrix Last_control_orient = vmd_identity_matrix;

        grid* The_grid;

        fix lasttime = 0;

        FredRenderer(const FredRenderer& other) = delete;
        FredRenderer& operator=(const FredRenderer& other) = delete;

    public:
        FredRenderer();
        ~FredRenderer();
        void inc_mission_time();
        void move_mouse(int btn, int mdx, int mdy);
        void process_system_keys(int key);
        void process_controls(vec3d* pos, matrix* orient, float frametime, int key, int mode = 0);
        void game_do_frame(const int view_obj, const int viewpoint, const int cur_object_index, const int Cursor_over);
        void render_grid(grid* gridp);
        void hilight_bitmap();
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
    };
}
