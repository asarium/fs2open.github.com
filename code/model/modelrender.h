/*
 * Copyright (C) Freespace Open 2013.  All rights reserved.
 *
 * All source code herein is the property of Freespace Open. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 

#ifndef _MODELRENDER_H
#define _MODELRENDER_H

#include "graphics/material.h"
#include "lighting/lighting.h"
#include "model/draw_list.h"
#include "math/vecmat.h"
#include "model/model.h"

extern bool Rendering_to_shadow_map;

extern matrix Object_matrix;
extern vec3d Object_position;

inline int in_box(vec3d *min, vec3d *max, vec3d *pos, vec3d *view_position)
{
	vec3d point;

	vm_vec_sub(&point, view_position, pos);

	if ( (point.xyz.x >= min->xyz.x) && (point.xyz.x <= max->xyz.x)
		&& (point.xyz.y >= min->xyz.y) && (point.xyz.y <= max->xyz.y)
		&& (point.xyz.z >= min->xyz.z) && (point.xyz.z <= max->xyz.z) )
	{
		return 1;
	}

	return -1;
}

inline int in_sphere(vec3d *pos, float radius, vec3d *view_position)
{
	if ( vm_vec_dist(view_position, pos) <= radius )
		return 1;
	else
		return -1;
}

extern int model_interp_get_texture(texture_info *tinfo, fix base_frametime);

void model_render_immediate(model_render_params *render_info, int model_num, matrix *orient, vec3d * pos, int render = MODEL_RENDER_ALL, bool sort = true);
void model_render_queue(model_render_params *render_info, draw_list* scene, int model_num, matrix *orient, vec3d *pos);
void submodel_render_immediate(model_render_params *render_info, int model_num, int submodel_num, matrix *orient, vec3d * pos);
void submodel_render_queue(model_render_params *render_info, draw_list *scene, int model_num, int submodel_num, matrix *orient, vec3d * pos);
void model_render_buffers(draw_list* scene, model_material *rendering_material, model_render_params* interp, vertex_buffer *buffer, polymodel *pm, int mn, int detail_level, uint tmap_flags);
void model_render_set_thrust(model_render_params *interp, int model_num, mst_info *mst);
void model_render_set_clip_plane(model_render_params *interp, vec3d *pos = NULL, vec3d *normal = NULL);
fix model_render_determine_base_frametime(int objnum, uint flags);
bool model_render_check_detail_box(vec3d *view_pos, polymodel *pm, int submodel_num, uint flags);
void model_render_arc(vec3d *v1, vec3d *v2, color *primary, color *secondary, float arc_width);
void model_render_insignias(insignia_draw_data *insignia);

void model_render_determine_color(color *clr, float alpha, gr_alpha_blend blend_mode, bool no_texturing, bool desaturate);
gr_alpha_blend model_render_determine_blend_mode(int base_bitmap, bool blending);

#endif
