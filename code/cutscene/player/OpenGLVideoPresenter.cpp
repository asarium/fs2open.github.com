
#include "OpenGLVideoPresenter.h"

#include "graphics/opengl/gropenglstate.h"
#include "graphics/opengl/gropengltnl.h"
#include "graphics/opengl/gropengldraw.h"


using namespace cutscene;
using namespace cutscene::player;

namespace {
void convert_YUV_to_RGB(const VideoFramePtr& frame, std::unique_ptr<ubyte[]>& pixelbuf) {
	int Y1, Y2, U, V;
	int R = 0, G = 0, B = 0;
	int C, D, E;
	uint x, y;

	uint width_2 = static_cast<uint>(frame->ySize.width / 2);

	ubyte* pix = pixelbuf.get();

	auto ptrs = frame->getDataPointers();
	ubyte* y_ptr = ptrs.y;
	ubyte* u_ptr = ptrs.u;
	ubyte* v_ptr = ptrs.v;

	for (y = 0; y < (uint) frame->ySize.height; y++) {
		for (x = 0; x < width_2; x++) {
			// we need two pixels of Y
			Y1 = *y_ptr;
			y_ptr++;
			Y2 = *y_ptr;
			y_ptr++;

			// only one pixel of U and V (half the size of Y)
			U = u_ptr[x];
			V = v_ptr[x];

			D = (U - 128);
			E = (V - 128);

			// first pixel
			C = (Y1 - 16) * 298;

			R = ((C + 409 * E + 128) >> 8);
			G = ((C - 100 * D - 208 * E + 128) >> 8);
			B = ((C + 516 * D + 128) >> 8);

			CLAMP(R, 0, 255);
			CLAMP(G, 0, 255);
			CLAMP(B, 0, 255);

			*pix++ = (ubyte) B;
			*pix++ = (ubyte) G;
			*pix++ = (ubyte) R;

			// second pixel (U and V values are resused)
			C = (Y2 - 16) * 298;

			R = ((C + 409 * E + 128) >> 8);
			G = ((C - 100 * D - 208 * E + 128) >> 8);
			B = ((C + 516 * D + 128) >> 8);

			CLAMP(R, 0, 255);
			CLAMP(G, 0, 255);
			CLAMP(B, 0, 255);

			*pix++ = (ubyte) B;
			*pix++ = (ubyte) G;
			*pix++ = (ubyte) R;
		}

		y_ptr += (frame->ySize.stride - frame->ySize.width);

		// u and v have to be done every other row (it's a 2x2 block)
		if (y % 2) {
			u_ptr += frame->uvSize.stride;
			v_ptr += frame->uvSize.stride;
		}
	}
}
}

namespace cutscene {
namespace player {
OpenGLVideoPresenter::OpenGLVideoPresenter(const MovieProperties& props) : _scaleVideo(false),
																		   _ytex(0), _utex(0), _vtex(0) {
	GR_DEBUG_SCOPE("Init video");

	opengl_set_texture_target(GL_TEXTURE_2D);

	_vertexBuffer = gr_create_vertex_buffer(true);

	auto w = static_cast<int>(props.size.width);
	auto h = static_cast<int>(props.size.height);

	int sdr_handle = gr_maybe_create_shader(SDR_TYPE_VIDEO_PROCESS, 0);

	glGenTextures(1, &_ytex);
	glGenTextures(1, &_utex);
	glGenTextures(1, &_vtex);

	if (_ytex + _utex + _vtex == 0) {
		throw std::runtime_error("Can't create a GL texture");
	}
	opengl_shader_set_current(sdr_handle);

	gr_set_lighting(false, false);

	GL_state.SetAlphaBlendMode(ALPHA_BLEND_NONE);
	GL_state.SetZbufferType(ZBUFFER_TYPE_NONE);

	GL_state.Texture.SetActiveUnit(0);
	GL_state.Texture.SetTarget(GL_texture_target);
	GL_state.Texture.Enable(_ytex);
	glTexParameteri(GL_texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_texture_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_texture_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// NOTE: using NULL instead of pixelbuf crashes some drivers, but then so does pixelbuf
	glTexImage2D(GL_state.Texture.GetTarget(), 0, GL_RED, w, h, 0, GL_RED,
				 GL_UNSIGNED_BYTE, NULL);

	GL_state.Texture.SetActiveUnit(1);
	GL_state.Texture.SetTarget(GL_texture_target);
	GL_state.Texture.Enable(_utex);
	glTexParameteri(GL_texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_texture_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_texture_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// NOTE: using NULL instead of pixelbuf crashes some drivers, but then so does pixelbuf
	glTexImage2D(GL_state.Texture.GetTarget(), 0, GL_RED, w / 2, h / 2, 0, GL_RED,
				 GL_UNSIGNED_BYTE, NULL);

	GL_state.Texture.SetActiveUnit(2);
	GL_state.Texture.SetTarget(GL_texture_target);
	GL_state.Texture.Enable(_vtex);
	glTexParameteri(GL_texture_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_texture_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_texture_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_texture_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// NOTE: using NULL instead of pixelbuf crashes some drivers, but then so does pixelbuf
	glTexImage2D(GL_state.Texture.GetTarget(), 0, GL_RED, w / 2, h / 2, 0, GL_RED,
				 GL_UNSIGNED_BYTE, NULL);

	float screen_ratio = (float) gr_screen.max_w / (float) gr_screen.max_h;
	float movie_ratio = (float) props.size.width / (float) props.size.height;

	float scale_by;
	if (screen_ratio > movie_ratio) {
		scale_by = (float) gr_screen.max_h / (float) props.size.height;
	} else {
		scale_by = (float) gr_screen.max_w / (float) props.size.width;
	}

	// don't bother setting anything if we aren't going to need it
	if (!Cmdline_noscalevid && (scale_by != 1.0f)) {
		vec3d scale;

		scale.xyz.x = scale_by;
		scale.xyz.y = scale_by;
		scale.xyz.z = -1.0f;

		gr_push_scale_matrix(&scale);
		_scaleVideo = true;
	}

	int screenX;
	int screenY;

	if (_scaleVideo) {
		screenX = ((fl2i(gr_screen.max_w / scale_by + 0.5f) - static_cast<int>(props.size.width)) / 2);
		screenY = ((fl2i(gr_screen.max_h / scale_by + 0.5f) - static_cast<int>(props.size.height)) / 2);
	} else {
		// centers on 1024x768, fills on 640x480
		screenX = ((gr_screen.max_w - static_cast<int>(props.size.width)) / 2);
		screenY = ((gr_screen.max_h - static_cast<int>(props.size.height)) / 2);
	}

	// set additional values for screen width/height and UV coords
	int screenXW = screenX + static_cast<int>(props.size.width);
	int screenYH = screenY + static_cast<int>(props.size.height);

	Current_shader->program->Uniforms.setUniformi("ytex", 0);
	Current_shader->program->Uniforms.setUniformi("utex", 1);
	Current_shader->program->Uniforms.setUniformi("vtex", 2);

	Current_shader->program->Uniforms.setUniformMatrix4f("projMatrix", GL_projection_matrix);
	Current_shader->program->Uniforms.setUniformMatrix4f("modelViewMatrix", GL_model_view_matrix);

	GLfloat glVertices[4][4] = {{0}};
	glVertices[0][0] = (GLfloat)screenX;
	glVertices[0][1] = (GLfloat)screenY;
	glVertices[0][2] = 0.0f;
	glVertices[0][3] = 0.0f;

	glVertices[1][0] = (GLfloat)screenX;
	glVertices[1][1] = (GLfloat)screenYH;
	glVertices[1][2] = 0.0f;
	glVertices[1][3] = 1.0f;

	glVertices[2][0] = (GLfloat)screenXW;
	glVertices[2][1] = (GLfloat)screenY;
	glVertices[2][2] = 1.0f;
	glVertices[2][3] = 0.0f;

	glVertices[3][0] = (GLfloat)screenXW;
	glVertices[3][1] = (GLfloat)screenYH;
	glVertices[3][2] = 1.0f;
	glVertices[3][3] = 1.0f;

	vertex_layout vert_def;

	vert_def.add_vertex_component(vertex_format_data::POSITION2, sizeof(glVertices[0]), 0);
	vert_def.add_vertex_component(vertex_format_data::TEX_COORD, sizeof(glVertices[0]), sizeof(GLfloat) * 2);

	gr_update_buffer_data(_vertexBuffer, sizeof(glVertices[0]) * 4, glVertices);

	opengl_bind_buffer_object(_vertexBuffer);
	opengl_bind_vertex_layout(vert_def);
}

OpenGLVideoPresenter::~OpenGLVideoPresenter() {
	GR_DEBUG_SCOPE("Deinit video");

	if (_scaleVideo) {
		gr_pop_scale_matrix();
	}

	gr_delete_buffer(_vertexBuffer);
	_vertexBuffer = -1;

	GL_state.Texture.Delete(_ytex);
	GL_state.Texture.Delete(_utex);
	GL_state.Texture.Delete(_vtex);
	glDeleteTextures(1, &_ytex);
	glDeleteTextures(1, &_utex);
	glDeleteTextures(1, &_vtex);

	opengl_set_texture_target();

	_ytex = _utex = _vtex = 0;
	opengl_shader_set_current();
}

void OpenGLVideoPresenter::uploadVideoFrame(const VideoFramePtr& frame) {
	GR_DEBUG_SCOPE("Update video frame");
	auto ptrs = frame->getDataPointers();

	auto stride = static_cast<GLint>(frame->ySize.stride);
	auto width = static_cast<GLint>(frame->ySize.width);
	auto height = static_cast<GLint>(frame->ySize.height);

	GL_state.Texture.SetActiveUnit(0);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, stride);
	glTexSubImage2D(GL_state.Texture.GetTarget(), 0, 0, 0, width, height, GL_RED, GL_UNSIGNED_BYTE,
					ptrs.y);

	stride = static_cast<int>(frame->uvSize.stride);
	width = static_cast<int>(frame->uvSize.width);
	height = static_cast<int>(frame->uvSize.height);

	GL_state.Texture.SetActiveUnit(1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, stride);
	glTexSubImage2D(GL_state.Texture.GetTarget(), 0, 0, 0, width, height, GL_RED, GL_UNSIGNED_BYTE,
					ptrs.u);

	GL_state.Texture.SetActiveUnit(2);
	glTexSubImage2D(GL_state.Texture.GetTarget(), 0, 0, 0, width, height, GL_RED, GL_UNSIGNED_BYTE,
					ptrs.v);

	// Reset this back to default
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
}

void OpenGLVideoPresenter::displayFrame() {
	GR_DEBUG_SCOPE("Draw video frame");
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
}
}
