#include "FredRenderer.h"
#include <globalincs/alphacolors.h>
#include <mission/missiongrid.h>
#include <globalincs/systemvars.h>
#include <io/timer.h>
#include <osapi/osapi.h>
#include <include/object.h>
#include <io/key.h>
#include <object/object.h>
#include <globalincs/linklist.h>
#include <render/3d.h>
#include <graphics/font.h>
#include <lighting/lighting.h>
#include <starfield/starfield.h>
#include <ship/ship.h>
#include <jumpnode/jumpnode.h>
#include <asteroid/asteroid.h>

namespace
{
    const float MAX_FRAMETIME = (F1_0 / 4); // Frametime gets saturated at this.
    const float MIN_FRAMETIME = (F1_0 / 120);
    const float LOLLIPOP_SIZE = 2.5f;
    const float CONVERT_DEGREES = 57.29578f; // conversion factor from radians to degrees

    const float FRED_DEFAULT_HTL_FOV = 0.485f;
    const float FRED_BRIEFING_HTL_FOV = 0.325f;
    const float FRED_DEAFULT_HTL_DRAW_DIST = 300000.0f;

    void enable_htl()
    {
        gr_set_proj_matrix((4.0f / 9.0f) * PI * FRED_DEFAULT_HTL_FOV,
                           gr_screen.aspect * static_cast<float>(gr_screen.clip_width) / static_cast<float>(gr_screen.clip_height),
                           1.0f, FRED_DEAFULT_HTL_DRAW_DIST);
        gr_set_view_matrix(&Eye_position, &Eye_matrix);
    }

    void disable_htl()
    {
        gr_end_proj_matrix();
        gr_end_view_matrix();
    }

    int grid_colors_inited = 0;
    color Fred_grid_bright;
    color Fred_grid_dark;
    color Fred_grid_bright_aa;
    color Fred_grid_dark_aa;

    void process_movement_keys(int key, vec3d* mvec, angles* angs)
    {
        int raw_key;

        mvec->xyz.x = 0.0f;
        mvec->xyz.y = 0.0f;
        mvec->xyz.z = 0.0f;
        angs->p = 0.0f;
        angs->b = 0.0f;
        angs->h = 0.0f;

        raw_key = key & 0xff;

        switch (raw_key)
        {
            case KEY_PAD1: mvec->xyz.x += -1.0f;
                break;
            case KEY_PAD3: mvec->xyz.x += +1.0f;
                break;
            case KEY_PADPLUS: mvec->xyz.y += -1.0f;
                break;
            case KEY_PADMINUS: mvec->xyz.y += +1.0f;
                break;
            case KEY_A: mvec->xyz.z += +1.0f;
                break;
            case KEY_Z: mvec->xyz.z += -1.0f;
                break;
            case KEY_PAD4: angs->h += -0.1f;
                break;
            case KEY_PAD6: angs->h += +0.1f;
                break;
            case KEY_PAD8: angs->p += -0.1f;
                break;
            case KEY_PAD2: angs->p += +0.1f;
                break;
            case KEY_PAD7: angs->b += -0.1f;
                break;
            case KEY_PAD9: angs->b += +0.1f;
                break;
        }

        if (key & KEY_SHIFTED)
        {
            vm_vec_scale(mvec, 5.0f);
            angs->p *= 5.0f;
            angs->b *= 5.0f;
            angs->h *= 5.0f;
        }
    }

    void draw_asteroid_field()
    {
        int i, j;
        vec3d p[8], ip[8];
        vertex v[8], iv[8];

        for (i = 0; i < 1 /*MAX_ASTEROID_FIELDS*/; i++)
            if (Asteroid_field.num_initial_asteroids)
            {
                p[0].xyz.x = p[2].xyz.x = p[4].xyz.x = p[6].xyz.x = Asteroid_field.min_bound.xyz.x;
                p[1].xyz.x = p[3].xyz.x = p[5].xyz.x = p[7].xyz.x = Asteroid_field.max_bound.xyz.x;
                p[0].xyz.y = p[1].xyz.y = p[4].xyz.y = p[5].xyz.y = Asteroid_field.min_bound.xyz.y;
                p[2].xyz.y = p[3].xyz.y = p[6].xyz.y = p[7].xyz.y = Asteroid_field.max_bound.xyz.y;
                p[0].xyz.z = p[1].xyz.z = p[2].xyz.z = p[3].xyz.z = Asteroid_field.min_bound.xyz.z;
                p[4].xyz.z = p[5].xyz.z = p[6].xyz.z = p[7].xyz.z = Asteroid_field.max_bound.xyz.z;

                for (j = 0; j < 8; j++)
                    g3_rotate_vertex(&v[j], &p[j]);

                g3_draw_line(&v[0], &v[1]);
                g3_draw_line(&v[2], &v[3]);
                g3_draw_line(&v[4], &v[5]);
                g3_draw_line(&v[6], &v[7]);
                g3_draw_line(&v[0], &v[2]);
                g3_draw_line(&v[1], &v[3]);
                g3_draw_line(&v[4], &v[6]);
                g3_draw_line(&v[5], &v[7]);
                g3_draw_line(&v[0], &v[4]);
                g3_draw_line(&v[1], &v[5]);
                g3_draw_line(&v[2], &v[6]);
                g3_draw_line(&v[3], &v[7]);


                // maybe draw inner box
                if (Asteroid_field.has_inner_bound)
                {
                    gr_set_color(16, 192, 92);

                    ip[0].xyz.x = ip[2].xyz.x = ip[4].xyz.x = ip[6].xyz.x = Asteroid_field.inner_min_bound.xyz.x;
                    ip[1].xyz.x = ip[3].xyz.x = ip[5].xyz.x = ip[7].xyz.x = Asteroid_field.inner_max_bound.xyz.x;
                    ip[0].xyz.y = ip[1].xyz.y = ip[4].xyz.y = ip[5].xyz.y = Asteroid_field.inner_min_bound.xyz.y;
                    ip[2].xyz.y = ip[3].xyz.y = ip[6].xyz.y = ip[7].xyz.y = Asteroid_field.inner_max_bound.xyz.y;
                    ip[0].xyz.z = ip[1].xyz.z = ip[2].xyz.z = ip[3].xyz.z = Asteroid_field.inner_min_bound.xyz.z;
                    ip[4].xyz.z = ip[5].xyz.z = ip[6].xyz.z = ip[7].xyz.z = Asteroid_field.inner_max_bound.xyz.z;

                    for (j = 0; j < 8; j++)
                        g3_rotate_vertex(&iv[j], &ip[j]);

                    g3_draw_line(&iv[0], &iv[1]);
                    g3_draw_line(&iv[2], &iv[3]);
                    g3_draw_line(&iv[4], &iv[5]);
                    g3_draw_line(&iv[6], &iv[7]);
                    g3_draw_line(&iv[0], &iv[2]);
                    g3_draw_line(&iv[1], &iv[3]);
                    g3_draw_line(&iv[4], &iv[6]);
                    g3_draw_line(&iv[5], &iv[7]);
                    g3_draw_line(&iv[0], &iv[4]);
                    g3_draw_line(&iv[1], &iv[5]);
                    g3_draw_line(&iv[2], &iv[6]);
                    g3_draw_line(&iv[3], &iv[7]);
                }
            }
    }
}

namespace fred
{
    FredRenderer::FredRenderer()
    {
        vec3d f, u, r;

        physics_init(&view_physics);
        view_physics.max_vel.xyz.z = 5.0f; //forward/backward
        view_physics.max_rotvel.xyz.x = 1.5f; //pitch
        memset(&view_controls, 0, sizeof(control_info));

        vm_vec_make(&view_pos, 0.0f, 150.0f, -200.0f);
        vm_vec_make(&f, 0.0f, -0.5f, 0.866025404f); // 30 degree angle
        vm_vec_make(&u, 0.0f, 0.866025404f, 0.5f);
        vm_vec_make(&r, 1.0f, 0.0f, 0.0f);
        vm_vector_2_matrix(&view_orient, &f, &u, &r);

        The_grid = create_default_grid();
        maybe_create_new_grid(The_grid, &view_pos, &view_orient, 1);
        //	vm_set_identity(&view_orient);

        gr_init_alphacolor(&colour_white, 255, 255, 255, 255);
        gr_init_alphacolor(&colour_green, 0, 200, 0, 255);
        gr_init_alphacolor(&colour_yellow, 200, 255, 0, 255);
        gr_init_alphacolor(&colour_black, 0, 0, 0, 255);
    }

    FredRenderer::~FredRenderer()
    {
    }

    void FredRenderer::inc_mission_time()
    {
        fix thistime;

        thistime = timer_get_fixed_seconds();
        if (!lasttime)
        {
            Frametime = F1_0 / 30;
        }
        else
        {
            Frametime = thistime - lasttime;
        }

        if (Frametime > MAX_FRAMETIME)
        {
            Frametime = MAX_FRAMETIME;
        }
        else if (Frametime < MIN_FRAMETIME)
        {
            if (!Cmdline_NoFPSCap)
            {
                thistime = MIN_FRAMETIME - Frametime;
                os_sleep(f2i(thistime) * 1000);
                thistime = timer_get_fixed_seconds();
            }

            Frametime = MIN_FRAMETIME;
        }

        Missiontime += Frametime;
        lasttime = thistime;
    }

    void FredRenderer::move_mouse(int btn, int mdx, int mdy)
    {
        int dx, dy;

        dx = mdx - last_x;
        dy = mdy - last_y;
        last_x = mdx;
        last_y = mdy;

        if (btn & 1)
        {
            matrix tempm, mousem;

            if (dx || dy)
            {
                vm_trackball(dx, dy, &mousem);
                vm_matrix_x_matrix(&tempm, &trackball_orient, &mousem);
                trackball_orient = tempm;
                view_orient = trackball_orient;
            }
        }

        if (btn & 2)
        {
            my_pos.xyz.z += (float)dy;
        }
    }

    ///////////////////////////////////////////////////
    void FredRenderer::process_system_keys(int key)
    {
        //	mprintf(("Key = %d\n", key));
        switch (key)
        {
            case KEY_LAPOSTRO:
                ///! \todo cycle through axis-constraints for rotations.
                //CFREDView::GetView()->cycle_constraint();
                break;

            case KEY_R: // for some stupid reason, an accelerator for 'R' doesn't work.
                ///! \todo Change editing mode to 'move and rotate'.
                //Editing_mode = 2;
                break;

            case KEY_SPACEBAR:
                ///! \todo Toggle selection lock.
                //Selection_lock = !Selection_lock;
                break;

            case KEY_ESC:
                ///! \todo Cancel drag.
                //if (button_down)
                //	cancel_drag();

                break;
        }
    }

    void FredRenderer::process_controls(vec3d* pos, matrix* orient, float frametime, int key, int mode)
    {
        if (Flying_controls_mode)
        {
            grid_read_camera_controls(&view_controls, frametime);

            if (key_get_shift_status())
                memset(&view_controls, 0, sizeof(control_info));

            ///! \todo Notify update window.
            if ((fabs(view_controls.pitch) > (frametime / 100)) &&
                (fabs(view_controls.vertical) > (frametime / 100)) &&
                (fabs(view_controls.heading) > (frametime / 100)) &&
                (fabs(view_controls.sideways) > (frametime / 100)) &&
                (fabs(view_controls.bank) > (frametime / 100)) &&
                (fabs(view_controls.forward) > (frametime / 100)));

            //view_physics.flags |= (PF_ACCELERATES | PF_SLIDE_ENABLED);
            physics_read_flying_controls(orient, &view_physics, &view_controls, frametime);
            if (mode)
                physics_sim_editor(pos, orient, &view_physics, frametime);
            else
                physics_sim(pos, orient, &view_physics, frametime);
        }
        else
        {
            vec3d movement_vec, rel_movement_vec;
            angles rotangs;
            matrix newmat, rotmat;

            process_movement_keys(key, &movement_vec, &rotangs);
            vm_vec_rotate(&rel_movement_vec, &movement_vec, &The_grid->gmatrix);
            vm_vec_add2(pos, &rel_movement_vec);

            vm_angles_2_matrix(&rotmat, &rotangs);
            if (rotangs.h && Universal_heading)
                vm_transpose_matrix(orient);
            vm_matrix_x_matrix(&newmat, orient, &rotmat);
            *orient = newmat;
            if (rotangs.h && Universal_heading)
                vm_transpose_matrix(orient);
        }
    }
    
    void FredRenderer::game_do_frame(const int view_obj, const int viewpoint, const int cur_object_index, const int Cursor_over)
    {
        int key, cmode;
        vec3d viewer_position, control_pos;
        object* objp;
        matrix control_orient;

        inc_mission_time();

        viewer_position = my_orient.vec.fvec;
        vm_vec_scale(&viewer_position, my_pos.xyz.z);

        ///! \bug Reset viewpoint.
        if ((viewpoint == 1) && !query_valid_object(view_obj))
        /*viewpoint = 0*/;

        key = key_inkey();
        process_system_keys(key);
        cmode = Control_mode;
        if ((viewpoint == 1) && !cmode)
            cmode = 2;

        control_pos = Last_control_pos;
        control_orient = Last_control_orient;

        //	if ((key & KEY_MASK) == key)  // unmodified
        switch (cmode)
        {
            case 0: //	Control the viewer's location and orientation
                process_controls(&view_pos, &view_orient, f2fl(Frametime), key, 1);
                control_pos = view_pos;
                control_orient = view_orient;
                break;

            case 2: // Control viewpoint object
                process_controls(&Objects[view_obj].pos, &Objects[view_obj].orient, f2fl(Frametime), key);
                object_moved(&Objects[view_obj]);
                control_pos = Objects[view_obj].pos;
                control_orient = Objects[view_obj].orient;
                break;

            case 1: //	Control the current object's location and orientation
                if (query_valid_object(cur_object_index))
                {
                    vec3d delta_pos, leader_old_pos;
                    matrix leader_orient, leader_transpose, tmp;
                    object* leader;

                    leader = &Objects[cur_object_index];
                    leader_old_pos = leader->pos; // save original position
                    leader_orient = leader->orient; // save original orientation
                    vm_copy_transpose_matrix(&leader_transpose, &leader_orient);

                    process_controls(&leader->pos, &leader->orient, f2fl(Frametime), key);
                    vm_vec_sub(&delta_pos, &leader->pos, &leader_old_pos); // get position change
                    control_pos = leader->pos;
                    control_orient = leader->orient;

                    objp = GET_FIRST(&obj_used_list);
                    while (objp != END_OF_LIST(&obj_used_list))
                    {
                        Assert(objp->type != OBJ_NONE);
                        if ((objp->flags & OF_MARKED) && (cur_object_index != OBJ_INDEX(objp)))
                        {
                            if (Group_rotate)
                            {
                                matrix rot_trans;
                                vec3d tmpv1, tmpv2;

                                // change rotation matrix to rotate in opposite direction.  This rotation
                                // matrix is what the leader ship has rotated by.
                                vm_copy_transpose_matrix(&rot_trans, &view_physics.last_rotmat);

                                // get point relative to our point of rotation (make POR the origin).  Since
                                // only the leader has been moved yet, and not the objects, we have to use
                                // the old leader's position.
                                vm_vec_sub(&tmpv1, &objp->pos, &leader_old_pos);

                                // convert point from real-world coordinates to leader's relative coordinate
                                // system (z=forward vec, y=up vec, x=right vec
                                vm_vec_rotate(&tmpv2, &tmpv1, &leader_orient);

                                // now rotate the point by the transpose from above.
                                vm_vec_rotate(&tmpv1, &tmpv2, &rot_trans);

                                // convert point back into real-world coordinates
                                vm_vec_rotate(&tmpv2, &tmpv1, &leader_transpose);

                                // and move origin back to real-world origin.  Object is now at its correct
                                // position.  Note we used the leader's new position, instead of old position.
                                vm_vec_add(&objp->pos, &leader->pos, &tmpv2);

                                // Now fix the object's orientation to what it should be.
                                vm_matrix_x_matrix(&tmp, &objp->orient, &view_physics.last_rotmat);
                                vm_orthogonalize_matrix(&tmp); // safety check
                                objp->orient = tmp;
                            }
                            else
                            {
                                vm_vec_add2(&objp->pos, &delta_pos);
                                vm_matrix_x_matrix(&tmp, &objp->orient, &view_physics.last_rotmat);
                                objp->orient = tmp;
                            }
                        }

                        objp = GET_NEXT(objp);
                    }

                    objp = GET_FIRST(&obj_used_list);
                    while (objp != END_OF_LIST(&obj_used_list))
                    {
                        if (objp->flags & OF_MARKED)
                            object_moved(objp);

                        objp = GET_NEXT(objp);
                    }

                    ///! \todo Notify.
                    //set_modified();
                }

                break;

            default:
                Assert(0);
        }

        if (Lookat_mode && query_valid_object(cur_object_index))
        {
            float dist;

            dist = vm_vec_dist(&view_pos, &Objects[cur_object_index].pos);
            vm_vec_scale_add(&view_pos, &Objects[cur_object_index].pos, &view_orient.vec.fvec, -dist);
        }

        switch (viewpoint)
        {
            case 0:
                eye_pos = view_pos;
                eye_orient = view_orient;
                break;

            case 1:
                eye_pos = Objects[view_obj].pos;
                eye_orient = Objects[view_obj].orient;
                break;

            default:
                Assert(0);
        }

        maybe_create_new_grid(The_grid, &eye_pos, &eye_orient);

        if (Cursor_over != Last_cursor_over)
        {
            Last_cursor_over = Cursor_over;
            ///! \todo Notify update_window.
            //Update_window = 1;
        }

        // redraw screen if controlled object moved or rotated
        if (vm_vec_cmp(&control_pos, &Last_control_pos) || vm_matrix_cmp(&control_orient, &Last_control_orient))
        {
            ///! \todo Notify update window.
            //Update_window = 1;
            Last_control_pos = control_pos;
            Last_control_orient = control_orient;
        }

        // redraw screen if current viewpoint moved or rotated
        if (vm_vec_cmp(&eye_pos, &Last_eye_pos) || vm_matrix_cmp(&eye_orient, &Last_eye_orient))
        {
            ///! \todo Notify update window.
            //Update_window = 1;
            Last_eye_pos = eye_pos;
            Last_eye_orient = eye_orient;
        }
    }

    void FredRenderer::render_grid(grid* gridp)
    {
        int i, ncols, nrows;

        if (!Cmdline_nohtl)
        {
            enable_htl();
            gr_zbuffer_set(0);
        }

        if (!grid_colors_inited)
        {
            grid_colors_inited = 1;

            gr_init_alphacolor(&Fred_grid_dark_aa, 64, 64, 64, 255);
            gr_init_alphacolor(&Fred_grid_bright_aa, 128, 128, 128, 255);
            gr_init_color(&Fred_grid_dark, 64, 64, 64);
            gr_init_color(&Fred_grid_bright, 128, 128, 128);
        }

        ncols = gridp->ncols;
        nrows = gridp->nrows;
        if (double_fine_gridlines)
        {
            ncols *= 2;
            nrows *= 2;
        }

        if (Aa_gridlines)
            gr_set_color_fast(&Fred_grid_dark_aa);
        else
            gr_set_color_fast(&Fred_grid_dark);

        //	Draw the column lines.
        for (i = 0; i <= ncols; i++)
        {
            if (Cmdline_nohtl)
                rpd_line(&gridp->gpoints1[i], &gridp->gpoints2[i]);
            else
                g3_draw_htl_line(&gridp->gpoints1[i], &gridp->gpoints2[i]);
        }
        //	Draw the row lines.
        for (i = 0; i <= nrows; i++)
        {
            if (Cmdline_nohtl)
                rpd_line(&gridp->gpoints3[i], &gridp->gpoints4[i]);
            else
                g3_draw_htl_line(&gridp->gpoints3[i], &gridp->gpoints4[i]);
        }

        ncols = gridp->ncols / 2;
        nrows = gridp->nrows / 2;

        // now draw the larger, brighter gridlines that is x10 the scale of smaller one.
        if (Aa_gridlines)
            gr_set_color_fast(&Fred_grid_bright_aa);
        else
            gr_set_color_fast(&Fred_grid_bright);

        for (i = 0; i <= ncols; i++)
        {
            if (Cmdline_nohtl)
                rpd_line(&gridp->gpoints5[i], &gridp->gpoints6[i]);
            else
                g3_draw_htl_line(&gridp->gpoints5[i], &gridp->gpoints6[i]);
        }

        for (i = 0; i <= nrows; i++)
        {
            if (Cmdline_nohtl)
                rpd_line(&gridp->gpoints7[i], &gridp->gpoints8[i]);
            else
                g3_draw_htl_line(&gridp->gpoints7[i], &gridp->gpoints8[i]);
        }

        if (!Cmdline_nohtl)
        {
            disable_htl();
            gr_zbuffer_set(1);
        }
    }
    
    void FredRenderer::hilight_bitmap()
    {
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

    void FredRenderer::render_frame(int cur_object_index, subsys_to_render& Render_subsys, bool box_marking, const Marking_box& marking_box, int Cursor_over, bool Show_starts, bool Show_ships, bool Show_iff[], bool Show_ship_info, bool Show_ship_models, bool Show_dock_points, bool Show_paths_fred, bool Bg_bitmap_dialog, bool Render_compass, bool Lighting_on, bool FullDetail)
    {
        char buf[256];
        int x, y, w, h, inst;
        vec3d pos;
        vertex v;
        angles a, a_deg; //a is in rads, a_deg is in degrees

        if (g3_in_frame())
        g3_end_frame(); // ** Accounted for

        gr_reset_clip();
        gr_clear();
        ///! \fixme Briefing related!
#if 0
        if (Briefing_dialog) {
            CRect rect;

            Fred_main_wnd->GetClientRect(rect);
            True_rw = rect.Width();
            True_rh = rect.Height();
            if (Fixed_briefing_size) {
                True_rw = BRIEF_GRID_W;
                True_rh = BRIEF_GRID_H;

            }
            else {
                if ((float)True_rh / (float)True_rw > (float)BRIEF_GRID_H / (float)BRIEF_GRID_W) {
                    True_rh = (int)((float)BRIEF_GRID_H * (float)True_rw / (float)BRIEF_GRID_W);

                }
                else {  // Fred is wider than briefing window
                    True_rw = (int)((float)BRIEF_GRID_W * (float)True_rh / (float)BRIEF_GRID_H);
                }
            }

            g3_start_frame(0); // ** Accounted for
            gr_set_color(255, 255, 255);
            gr_line(0, True_rh, True_rw, True_rh);
            gr_line(True_rw, 0, True_rw, True_rh);
            g3_end_frame();	 // ** Accounted for
            gr_set_clip(0, 0, True_rw, True_rh);
        }
#endif

        g3_start_frame(1); // ** Accounted for
        // 1 means use zbuffering

        gr_set_font(FONT1);
        light_reset();

        g3_set_view_matrix(&eye_pos, &eye_orient, 0.5f);
        Viewer_pos = eye_pos; // for starfield code

        enable_htl();
        if (Bg_bitmap_dialog)
        {
            stars_draw(Show_stars, 1, Show_stars, 0, 0);
        }
        else
        {
            stars_draw(Show_stars, Show_stars, Show_stars, 0, 0);
        }
        disable_htl();

        if (Show_horizon)
        {
            gr_set_color(128, 128, 64);
            g3_draw_horizon_line();
        }

        if (Show_asteroid_field)
        {
            gr_set_color(192, 96, 16);
            draw_asteroid_field();
        }

        if (Show_grid)
            render_grid(The_grid);
        if (Bg_bitmap_dialog)
            hilight_bitmap();

        gr_set_color(0, 0, 64);
        render_models(
            cur_object_index,
            Show_starts, Show_ships, Show_iff,
            Bg_bitmap_dialog,
            Show_ship_models, Show_dock_points, Show_paths_fred,
            Lighting_on, FullDetail);

        if (Show_distances)
        {
            display_distances();
        }

        display_ship_info(cur_object_index, Show_starts, Show_ships, Show_iff, Show_ship_info);
        display_active_ship_subsystem(Render_subsys, cur_object_index);
        render_active_rect(box_marking, marking_box);

        if (query_valid_object(Cursor_over))
        { // display a tool-tip like infobox
            pos = Objects[Cursor_over].pos;
            inst = Objects[Cursor_over].instance;
            if ((Objects[Cursor_over].type == OBJ_SHIP) || (Objects[Cursor_over].type == OBJ_START))
            {
                vm_extract_angles_matrix(&a, &Objects[Cursor_over].orient);

                a_deg.h = a.h * CONVERT_DEGREES; // convert angles to more readable degrees
                a_deg.p = a.p * CONVERT_DEGREES;
                a_deg.b = a.b * CONVERT_DEGREES;

                sprintf(buf, "%s\n%s\n( %.1f , %.1f , %.1f ) \nHeading: %.2f\nPitch: %.2f\nBank: %.2f",
                        Ships[inst].ship_name, Ship_info[Ships[inst].ship_info_index].short_name,
                        pos.xyz.x, pos.xyz.y, pos.xyz.z, a_deg.h, a_deg.p, a_deg.b);
            }
            else if (Objects[Cursor_over].type == OBJ_WAYPOINT)
            {
                int idx;
                waypoint_list* wp_list = find_waypoint_list_with_instance(inst, &idx);
                Assert(wp_list != NULL);
                sprintf(buf, "%s\nWaypoint %d\n( %.1f , %.1f , %.1f ) ", wp_list->get_name(), idx + 1, pos.xyz.x, pos.xyz.y, pos.xyz.z);
            }
            else if (Objects[Cursor_over].type == OBJ_POINT)
            {
                sprintf(buf, "Briefing icon\n( %.1f , %.1f , %.1f ) ", pos.xyz.x, pos.xyz.y, pos.xyz.z);
            }
            else
                sprintf(buf, "( %.1f , %.1f , %.1f ) ", pos.xyz.x, pos.xyz.y, pos.xyz.z);

            g3_rotate_vertex(&v, &pos);
            if (!(v.codes & CC_BEHIND))
                if (!(g3_project_vertex(&v) & PF_OVERFLOW))
                {
                    gr_get_string_size(&w, &h, buf);

                    x = (int)v.screen.xyw.x;
                    y = (int)v.screen.xyw.y + 20;

                    gr_set_color_fast(&colour_white);
                    gr_rect(x - 7, y - 6, w + 8, h + 7);

                    gr_set_color_fast(&colour_black);
                    gr_rect(x - 5, y - 5, w + 5, h + 5);

                    gr_set_color_fast(&colour_white);
                    gr_string(x, y, buf);
                }
        }

        gr_set_color(0, 160, 0);

        enable_htl();
        jumpnode_render_all();
        disable_htl();

        sprintf(buf, "(%.1f,%.1f,%.1f)", eye_pos.xyz.x, eye_pos.xyz.y, eye_pos.xyz.z);
        gr_get_string_size(&w, &h, buf);
        gr_set_color_fast(&colour_white);
        gr_string(gr_screen.max_w - w - 2, 2, buf);

        g3_end_frame(); // ** Accounted for
        render_compass(Render_compass);

        gr_flip();

        gr_reset_clip();
        ///! \fixme Briefing related!
#if 0
        if (Briefing_dialog)
            gr_set_clip(0, 0, True_rw, True_rh);
#endif

        g3_start_frame(0); // ** Accounted for
        g3_set_view_matrix(&eye_pos, &eye_orient, 0.5f);
    }

    int FredRenderer::select_object(int cx, int cy, bool Selection_lock, bool Show_starts, bool Show_ships, bool Show_iff[], bool Show_ship_models)
    {
    }

    void FredRenderer::level_controlled(const int viewpoint, const int cur_obj)
    {
    }

    void FredRenderer::verticalize_controlled(const int viewpoint, const int cur_obj)
    {
    }
}
