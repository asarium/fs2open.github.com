
#include "model/draw_list.h"
#include "globalincs/systemvars.h"
#include "graphics/opengl/gropengldraw.h"
#include "model/modelrender.h"
#include "render/3d.h"

extern light Lights[MAX_LIGHTS];
extern int Num_lights;

extern int Model_texturing;
extern int Model_polys;

draw_list *draw_list::Target = NULL;

model_batch_buffer TransformBufferHandler;

model_render_params::model_render_params():
	Model_flags(MR_NORMAL),
	Debug_flags(0),
	Objnum(-1),
	Detail_level_locked(-1),
	Depth_scale(1500.0f),
	Warp_bitmap(-1),
	Warp_alpha(-1.0f),
	Xparent_alpha(1.0f),
	Forced_bitmap(-1),
	Insignia_bitmap(-1),
	Replacement_textures(NULL),
	Team_color_set(false),
	Clip_plane_set(false),
	Animated_effect(-1),
	Animated_timer(0.0f),
	Thruster_info(),
	Normal_alpha(false),
	Normal_extrude(false)
{
	Warp_scale.xyz.x = 1.0f;
	Warp_scale.xyz.y = 1.0f;
	Warp_scale.xyz.z = 1.0f;

	Clip_normal = vmd_zero_vector;
	Clip_pos = vmd_zero_vector;

	if ( !Model_texturing )
		Model_flags |= MR_NO_TEXTURING;

	if ( !Model_polys )	{
		Model_flags |= MR_NO_POLYS;
	}

	gr_init_color(&Color, 0, 0, 0);
}

uint model_render_params::get_model_flags()
{
	return Model_flags;
}

uint model_render_params::get_debug_flags()
{
	return Debug_flags;
}

int model_render_params::get_object_number()
{
	return Objnum;
}

int model_render_params::get_detail_level_lock()
{
	return Detail_level_locked;
}

float model_render_params::get_depth_scale()
{
	return Depth_scale;
}

int model_render_params::get_warp_bitmap()
{
	return Warp_bitmap;
}

float model_render_params::get_warp_alpha()
{
	return Warp_alpha;
}

const vec3d& model_render_params::get_warp_scale()
{
	return Warp_scale;
}

const color& model_render_params::get_color()
{
	return Color;
}
float model_render_params::get_alpha()
{
	return Xparent_alpha;
}

int model_render_params::get_forced_bitmap()
{
	return Forced_bitmap;
}

int model_render_params::get_insignia_bitmap()
{
	return Insignia_bitmap;
}

const int* model_render_params::get_replacement_textures()
{
	return Replacement_textures;
}

const team_color& model_render_params::get_team_color()
{
	return Current_team_color;
}

const vec3d& model_render_params::get_clip_plane_pos()
{
	return Clip_pos;
}

const vec3d& model_render_params::get_clip_plane_normal()
{
	return Clip_normal;
}

int model_render_params::get_animated_effect_num()
{
	return Animated_effect;
}

float model_render_params::get_animated_effect_timer()
{
	return Animated_timer;
}

void model_render_params::set_animated_effect(int effect_num, float timer)
{
	Animated_effect = effect_num;
	Animated_timer = timer;
}

void model_render_params::set_clip_plane(vec3d &pos, vec3d &normal)
{
	Clip_plane_set = true;

	Clip_normal = normal;
	Clip_pos = pos;
}

bool model_render_params::is_clip_plane_set()
{
	return Clip_plane_set;
}

void model_render_params::set_team_color(team_color &clr)
{
	Team_color_set = true;

	Current_team_color = clr;
}

void model_render_params::set_team_color(const SCP_string &team, const SCP_string &secondaryteam, fix timestamp, int fadetime)
{
	Team_color_set = model_get_team_color(&Current_team_color, team, secondaryteam, timestamp, fadetime);
}

bool model_render_params::is_team_color_set()
{
	return Team_color_set;
}

void model_render_params::set_replacement_textures(int *textures)
{
	Replacement_textures = textures;
}

void model_render_params::set_insignia_bitmap(int bitmap)
{
	Insignia_bitmap = bitmap;
}

void model_render_params::set_forced_bitmap(int bitmap)
{
	Forced_bitmap = bitmap;
}

void model_render_params::set_alpha(float alpha)
{
	Xparent_alpha = alpha;
}

void model_render_params::set_color(color &clr)
{
	Color = clr;
}

void model_render_params::set_color(int r, int g, int b)
{
	gr_init_color( &Color, r, g, b );
}

void model_render_params::set_warp_params(int bitmap, float alpha, vec3d &scale)
{
	Warp_bitmap = bitmap;
	Warp_alpha = alpha;
	Warp_scale = scale;
}

void model_render_params::set_depth_scale(float scale)
{
	Depth_scale = scale;
}

void model_render_params::set_debug_flags(uint flags)
{
	Debug_flags = flags;
}

void model_render_params::set_object_number(int num)
{
	Objnum = num;
}

void model_render_params::set_flags(uint flags)
{
	Model_flags = flags;
}

void model_render_params::set_detail_level_lock(int detail_level_lock)
{
	Detail_level_locked = detail_level_lock;
}

void model_render_params::set_thruster_info(mst_info &info)
{
	Thruster_info = info;

	CLAMP(Thruster_info.length.xyz.z, 0.1f, 1.0f);
}

const mst_info& model_render_params::get_thruster_info()
{
	return Thruster_info;
}

void model_render_params::set_normal_alpha(float min, float max)
{
	Normal_alpha = true;
	Normal_alpha_min = min;
	Normal_alpha_max = max;
}

bool model_render_params::is_normal_alpha_set()
{
	return Normal_alpha;
}

float model_render_params::get_normal_alpha_min()
{
	return Normal_alpha_min;
}

float model_render_params::get_normal_alpha_max()
{
	return Normal_alpha_max;
}

void model_render_params::set_normal_extrude_width(float width)
{
	Normal_extrude = true;
	Normal_extrude_width = width;
}

bool model_render_params::is_normal_extrude_set()
{
	return Normal_extrude;
}

float model_render_params::get_normal_extrude_width()
{
	return Normal_extrude_width;
}

void model_batch_buffer::reset()
{
	Submodel_matrices.clear();

	Current_offset = 0;
}

void model_batch_buffer::set_num_models(int n_models)
{
	matrix4 init_mat;

	vm_matrix4_set_identity(&init_mat);

	Current_offset = Submodel_matrices.size();

	for ( int i = 0; i < n_models; ++i ) {
		Submodel_matrices.push_back(init_mat);
	}
}

void model_batch_buffer::set_model_transform(matrix4 &transform, int model_id)
{
	Submodel_matrices[Current_offset + model_id] = transform;
}

void model_batch_buffer::add_matrix(matrix4 &mat)
{
	Submodel_matrices.push_back(mat);
}

size_t model_batch_buffer::get_buffer_offset()
{
	return Current_offset;
}

void model_batch_buffer::allocate_memory()
{
	auto size = Submodel_matrices.size() * sizeof(matrix4);

	if ( Mem_alloc == NULL || Mem_alloc_size < size ) {
		if ( Mem_alloc != NULL ) {
			vm_free(Mem_alloc);
		}

		Mem_alloc = vm_malloc(size);
	}

	Mem_alloc_size = size;
	memcpy(Mem_alloc, &Submodel_matrices[0], size);
}

void model_batch_buffer::submit_buffer_data()
{
	if ( Submodel_matrices.size() == 0 ) {
		return;
	}

	allocate_memory();

	gr_update_transform_buffer(Mem_alloc, Mem_alloc_size);
}

draw_list::draw_list()
{
	reset();
}

void draw_list::reset()
{
	Render_elements.clear();
	Render_keys.clear();

	clear_transforms();

	Current_scale.xyz.x = 1.0f;
	Current_scale.xyz.y = 1.0f;
	Current_scale.xyz.z = 1.0f;
}

void draw_list::sort_draws()
{
	Target = this;
	std::sort(Target->Render_keys.begin(), Target->Render_keys.end(), draw_list::sort_draw_pair);
}

void draw_list::start_model_batch(int n_models)
{
	TransformBufferHandler.set_num_models(n_models);
}

void draw_list::add_submodel_to_batch(int model_num)
{
	matrix4 transform;

	vm_matrix4_set_identity(&transform);

	// set basis
	transform.a1d[0] = Current_transform.basis.a1d[0] * Current_scale.xyz.x;
	transform.a1d[1] = Current_transform.basis.a1d[1];
	transform.a1d[2] = Current_transform.basis.a1d[2];

	transform.a1d[4] = Current_transform.basis.a1d[3];
	transform.a1d[5] = Current_transform.basis.a1d[4] * Current_scale.xyz.y;
	transform.a1d[6] = Current_transform.basis.a1d[5];

	transform.a1d[8] = Current_transform.basis.a1d[6];
	transform.a1d[9] = Current_transform.basis.a1d[7];
	transform.a1d[10] = Current_transform.basis.a1d[8] * Current_scale.xyz.z;

	// set position
	transform.a1d[12] = Current_transform.origin.a1d[0];
	transform.a1d[13] = Current_transform.origin.a1d[1];
	transform.a1d[14] = Current_transform.origin.a1d[2];

	// set visibility
	transform.a1d[15] = 0.0f;

	TransformBufferHandler.set_model_transform(transform, model_num);
}

void draw_list::add_arc(vec3d *v1, vec3d *v2, color *primary, color *secondary, float arc_width)
{
	arc_effect new_arc;

	new_arc.transformation = Current_transform;
	new_arc.v1 = *v1;
	new_arc.v2 = *v2;
	new_arc.primary = *primary;
	new_arc.secondary = *secondary;
	new_arc.width = arc_width;

	Arcs.push_back(new_arc);
}

void draw_list::set_light_filter(int objnum, vec3d *pos, float rad)
{
	Scene_light_handler.setLightFilter(objnum, pos, rad);

	Current_lights_set = Scene_light_handler.bufferLights();
}

void draw_list::add_buffer_draw(model_material *render_material, indexed_vertex_source *vert_src, vertex_buffer *buffer, size_t texi, uint tmap_flags)
{
	queued_buffer_draw draw_data;

	render_material->set_deferred_lighting(Deferred_lighting);
	render_material->set_high_dynamic_range(High_dynamic_range);
	render_material->set_shadow_casting(Rendering_to_shadow_map ? true : false);

	if (tmap_flags & TMAP_FLAG_BATCH_TRANSFORMS && buffer->flags & VB_FLAG_MODEL_ID) {
		draw_data.transformation = transform();

		draw_data.scale.xyz.x = 1.0f;
		draw_data.scale.xyz.y = 1.0f;
		draw_data.scale.xyz.z = 1.0f;

		draw_data.transform_buffer_offset = TransformBufferHandler.get_buffer_offset();

		render_material->set_batching(true);
	} else {
		draw_data.transformation = Current_transform;
		draw_data.scale = Current_scale;
		draw_data.transform_buffer_offset = INVALID_SIZE;
		render_material->set_batching(false);
	}

	draw_data.sdr_flags = render_material->get_shader_flags();

	draw_data.vert_src = vert_src;
	draw_data.buffer = buffer;
	draw_data.texi = texi;
	draw_data.flags = tmap_flags;
	draw_data.render_material = *render_material;
	draw_data.lights = Current_lights_set;

	Render_elements.push_back(draw_data);
	Render_keys.push_back((int) (Render_elements.size() - 1));
}

void draw_list::render_buffer(queued_buffer_draw &render_elements)
{
	GR_DEBUG_SCOPE("Render buffer");

	gr_set_transform_buffer_offset(render_elements.transform_buffer_offset);

	if ( render_elements.render_material.is_lit() ) {
		Scene_light_handler.setLights(&render_elements.lights);
	} else {
		gr_set_lighting(false, false);

		Scene_light_handler.resetLightState();
	}

	g3_start_instance_matrix(&render_elements.transformation.origin, &render_elements.transformation.basis);

	gr_push_scale_matrix(&render_elements.scale);

	gr_render_model(&render_elements.render_material, render_elements.vert_src, render_elements.buffer, render_elements.texi);

	gr_pop_scale_matrix();

	g3_done_instance(true);
}

vec3d draw_list::get_view_position()
{
	matrix basis_world;

	// get the world basis of our current local space.
	vm_matrix_x_matrix(&basis_world, &Object_matrix, &Current_transform.basis);

	vec3d eye_pos_local;
	vm_vec_sub(&eye_pos_local, &Eye_position, &Current_transform.origin);

	vec3d return_val;
	vm_vec_rotate(&return_val, &eye_pos_local, &basis_world);

	return return_val;
}

void draw_list::clear_transforms()
{
	Current_transform = transform();
	Transform_stack.clear();
}

void draw_list::push_transform(vec3d *pos, matrix *orient)
{
	matrix basis;
	vec3d origin;

	if ( orient == NULL ) {
		basis = vmd_identity_matrix;
	} else {
		basis = *orient;
	}

	if ( pos == NULL ) {
		origin = vmd_zero_vector;
	} else {
		origin = *pos;
	}

	if ( Transform_stack.size() == 0 ) {
		Current_transform.basis = basis;
		Current_transform.origin = origin;

		Transform_stack.push_back(Current_transform);

		return;
	}

	vec3d tempv;
	transform newTransform = Current_transform;

	vm_vec_unrotate(&tempv, &origin, &Current_transform.basis);
	vm_vec_add2(&newTransform.origin, &tempv);

	vm_matrix_x_matrix(&newTransform.basis, &Current_transform.basis, &basis);

	Current_transform = newTransform;
	Transform_stack.push_back(Current_transform);
}

void draw_list::pop_transform()
{
	Assert( Transform_stack.size() > 0 );

	Transform_stack.pop_back();

	if ( Transform_stack.size() > 0 ) {
		Current_transform = Transform_stack.back();
	} else {
		Current_transform = transform();
	}
}

void draw_list::set_scale(vec3d *scale)
{
	if ( scale == NULL ) {
		Current_scale.xyz.x = 1.0f;
		Current_scale.xyz.y = 1.0f;
		Current_scale.xyz.z = 1.0f;
		return;
	}

	Current_scale = *scale;
}

void draw_list::init()
{
	reset();

	for ( int i = 0; i < Num_lights; ++i ) {
		if ( Lights[i].type == LT_DIRECTIONAL || !Deferred_lighting ) {
			Scene_light_handler.addLight(&Lights[i]);
		}
	}

	TransformBufferHandler.reset();
}

void draw_list::init_render(bool sort)
{
	if ( sort ) {
		sort_draws();
	}

	TransformBufferHandler.submit_buffer_data();
}

void draw_list::render_all(gr_zbuffer_type depth_mode)
{
	GR_DEBUG_SCOPE("Render draw list");

	Scene_light_handler.resetLightState();

	for ( size_t i = 0; i < Render_keys.size(); ++i ) {
		int render_index = Render_keys[i];

		if ( depth_mode == ZBUFFER_TYPE_DEFAULT || Render_elements[render_index].render_material.get_depth_mode() == depth_mode ) {
			PROFILE("Render buffer", render_buffer(Render_elements[render_index]));
		}
	}

	gr_alpha_mask_set(0, 1.0f);
}

void draw_list::render_arc(arc_effect &arc)
{
	g3_start_instance_matrix(&arc.transformation.origin, &arc.transformation.basis);

	model_render_arc(&arc.v1, &arc.v2, &arc.primary, &arc.secondary, arc.width);

	g3_done_instance(true);
}

void draw_list::render_arcs()
{
	int mode = gr_zbuffer_set(GR_ZBUFF_READ);

	for ( size_t i = 0; i < Arcs.size(); ++i ) {
		render_arc(Arcs[i]);
	}

	gr_zbuffer_set(mode);
}

void draw_list::add_insignia(model_render_params *params, polymodel *pm, int detail_level, int bitmap_num)
{
	insignia_draw_data new_insignia;

	new_insignia.transformation = Current_transform;
	new_insignia.pm = pm;
	new_insignia.detail_level = detail_level;
	new_insignia.bitmap_num = bitmap_num;

	new_insignia.clip = params->is_clip_plane_set();
	new_insignia.clip_normal = params->get_clip_plane_normal();
	new_insignia.clip_position = params->get_clip_plane_pos();

	Insignias.push_back(new_insignia);
}

void draw_list::render_insignia(insignia_draw_data &insignia_info)
{
	if ( insignia_info.clip ) {
		vec3d tmp;
		vm_vec_sub(&tmp, &insignia_info.transformation.origin, &insignia_info.clip_position);
		vm_vec_normalize(&tmp);

		if ( vm_vec_dot(&tmp, &insignia_info.clip_normal) < 0.0f) {
			return;
		}
	}

	g3_start_instance_matrix(&insignia_info.transformation.origin, &insignia_info.transformation.basis);

	model_render_insignias(&insignia_info);

	g3_done_instance(true);
}

void draw_list::render_insignias()
{
	for ( size_t i = 0; i < Insignias.size(); ++i ) {
		render_insignia(Insignias[i]);
	}
}

void draw_list::add_outline(vertex* vert_array, int n_verts, color *clr)
{
	outline_draw draw_info;

	draw_info.vert_array = vert_array;
	draw_info.n_verts = n_verts;
	draw_info.clr = *clr;
	draw_info.transformation = Current_transform;

	Outlines.push_back(draw_info);
}

void draw_list::render_outlines()
{
	gr_clear_states();

	for ( size_t i = 0; i < Outlines.size(); ++i ) {
		render_outline(Outlines[i]);
	}
}

void draw_list::render_outline(outline_draw &outline_info)
{
	g3_start_instance_matrix(&outline_info.transformation.origin, &outline_info.transformation.basis);

	material material_instance;

	material_instance.set_depth_mode(ZBUFFER_TYPE_READ);
	material_instance.set_blend_mode(ALPHA_BLEND_ALPHA_BLEND_ALPHA);
	material_instance.set_color(outline_info.clr);

	g3_render_primitives(&material_instance, outline_info.vert_array, outline_info.n_verts, PRIM_TYPE_LINES, false);

	g3_done_instance(true);
}

bool draw_list::sort_draw_pair(const int a, const int b)
{
	queued_buffer_draw *draw_call_a = &Target->Render_elements[a];
	queued_buffer_draw *draw_call_b = &Target->Render_elements[b];

	if ( draw_call_a->sdr_flags != draw_call_b->sdr_flags ) {
		return draw_call_a->sdr_flags < draw_call_b->sdr_flags;
	}

	if ( draw_call_a->vert_src->Vbuffer_handle != draw_call_b->vert_src->Vbuffer_handle ) {
		return draw_call_a->vert_src->Vbuffer_handle < draw_call_b->vert_src->Vbuffer_handle;
	}

	if ( draw_call_a->vert_src->Ibuffer_handle != draw_call_b->vert_src->Ibuffer_handle ) {
		return draw_call_a->vert_src->Ibuffer_handle < draw_call_b->vert_src->Ibuffer_handle;
	}

	if ( draw_call_a->render_material.get_texture_map(TM_BASE_TYPE) != draw_call_b->render_material.get_texture_map(TM_BASE_TYPE) ) {
		return draw_call_a->render_material.get_texture_map(TM_BASE_TYPE) < draw_call_b->render_material.get_texture_map(TM_BASE_TYPE);
	}

	if ( draw_call_a->render_material.get_texture_map(TM_SPECULAR_TYPE) != draw_call_b->render_material.get_texture_map(TM_SPECULAR_TYPE) ) {
		return draw_call_a->render_material.get_texture_map(TM_SPECULAR_TYPE) < draw_call_b->render_material.get_texture_map(TM_SPECULAR_TYPE);
	}

	if ( draw_call_a->render_material.get_texture_map(TM_SPEC_GLOSS_TYPE) != draw_call_b->render_material.get_texture_map(TM_SPEC_GLOSS_TYPE) ) {
		return draw_call_a->render_material.get_texture_map(TM_SPEC_GLOSS_TYPE) < draw_call_b->render_material.get_texture_map(TM_SPEC_GLOSS_TYPE);
	}

	if ( draw_call_a->render_material.get_texture_map(TM_GLOW_TYPE) != draw_call_b->render_material.get_texture_map(TM_GLOW_TYPE) ) {
		return draw_call_a->render_material.get_texture_map(TM_GLOW_TYPE) < draw_call_b->render_material.get_texture_map(TM_GLOW_TYPE);
	}

	if ( draw_call_a->render_material.get_texture_map(TM_NORMAL_TYPE) != draw_call_b->render_material.get_texture_map(TM_NORMAL_TYPE) ) {
		return draw_call_a->render_material.get_texture_map(TM_NORMAL_TYPE) < draw_call_b->render_material.get_texture_map(TM_NORMAL_TYPE);
	}

	if ( draw_call_a->render_material.get_texture_map(TM_HEIGHT_TYPE) != draw_call_b->render_material.get_texture_map(TM_HEIGHT_TYPE) ) {
		return draw_call_a->render_material.get_texture_map(TM_HEIGHT_TYPE) < draw_call_b->render_material.get_texture_map(TM_HEIGHT_TYPE);
	}

	if ( draw_call_a->render_material.get_texture_map(TM_AMBIENT_TYPE) != draw_call_b->render_material.get_texture_map(TM_AMBIENT_TYPE) ) {
		return draw_call_a->render_material.get_texture_map(TM_AMBIENT_TYPE) < draw_call_b->render_material.get_texture_map(TM_AMBIENT_TYPE);
	}

	if ( draw_call_a->render_material.get_texture_map(TM_MISC_TYPE) != draw_call_b->render_material.get_texture_map(TM_MISC_TYPE) ) {
		return draw_call_a->render_material.get_texture_map(TM_MISC_TYPE) < draw_call_b->render_material.get_texture_map(TM_MISC_TYPE);
	}

	return draw_call_a->lights.index_start < draw_call_b->lights.index_start;
}

