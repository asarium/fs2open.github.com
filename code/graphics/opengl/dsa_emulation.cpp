#include "dsa_emulation.h"
#include "graphics/opengl/gropenglstate.h"
#include "globalincs/pstypes.h"

#include <glad/glad.h>

#ifdef WIN32   //WINDOWS
#define __FUNCTION_NAME__   __FUNCTION__
#else          //*NIX
#define __FUNCTION_NAME__   __func__
#endif

#define UNIMPLEMENTED Assertion(false, "Unimplemented DSA emulation function %s called! Get a coder!", __FUNCTION_NAME__)

namespace {
// Texture state lookup functions
struct texture_data {
	GLenum target;
};
SCP_unordered_map<GLuint, texture_data> texture_lookup;

PFNGLDELETETEXTURESPROC real_glDeleteTextures = nullptr;
void APIENTRY DeleteTextures(GLsizei n, const GLuint* textures) {
	for (GLsizei i = 0; i < n; ++i) {
		auto iter = texture_lookup.find(textures[i]);
		if (iter != texture_lookup.end()) {
			texture_lookup.erase(iter);
		}
	}

	real_glDeleteTextures(n, textures);
}
GLenum getTextureTarget(GLuint tex) {
	auto iter = texture_lookup.find(tex);
	Assertion(iter != texture_lookup.end(), "Failed to find texture %d in texture lookup!", tex);

	return iter->second.target;
}
GLenum bindTexture(GLuint tex) {
	auto target = getTextureTarget(tex);

	GL_state.Texture.SetActiveUnit(0);
	GL_state.Texture.SetTarget(target);
	GL_state.Texture.Enable(tex);

	return target;
}


// We need to bind buffers for some thing and the COPY buffer targets have no special meaning otherwise so we can use
// those. This will minimize the state changes when doing a lot of buffer modifications
const GLenum FIRST_BUFFER_TARGET = GL_COPY_READ_BUFFER;
const GLenum SECOND_BUFFER_TARGET = GL_COPY_WRITE_BUFFER;
GLuint copy_read_buffer_state = 0;
GLuint copy_write_buffer_state = 0;
void bindFirstBuffer(GLuint buffer) {
	if (copy_read_buffer_state == buffer) {
		return;
	}

	copy_read_buffer_state = buffer;
	glBindBuffer(FIRST_BUFFER_TARGET, buffer);
}
void bindSecondBuffer(GLuint buffer) {
	if (copy_write_buffer_state == buffer) {
		return;
	}

	copy_write_buffer_state = buffer;
	glBindBuffer(SECOND_BUFFER_TARGET, buffer);
}

/* Transform Feedback object functions */

void APIENTRY CreateTransformFeedbacks(GLsizei n, GLuint* ids) {
	UNIMPLEMENTED;
}

void APIENTRY TransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer) {
	UNIMPLEMENTED;
}

void APIENTRY TransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) {
	UNIMPLEMENTED;
}

void APIENTRY GetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint* param) {
	UNIMPLEMENTED;
}

void APIENTRY GetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint* param) {
	UNIMPLEMENTED;
}

void APIENTRY GetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64* param) {
	UNIMPLEMENTED;
}


/* Buffer object functions */

void APIENTRY CreateBuffers(GLsizei n, GLuint* buffers) {
	glGenBuffers(n, buffers);
}

void APIENTRY NamedBufferStorage(GLuint buffer, GLsizeiptr size, const void* data, GLbitfield flags) {
	bindFirstBuffer(buffer);
	glBufferStorage(FIRST_BUFFER_TARGET, size, data, flags);
}

void APIENTRY NamedBufferData(GLuint buffer, GLsizeiptr size, const void* data, GLenum usage) {
	bindFirstBuffer(buffer);
	glBufferData(FIRST_BUFFER_TARGET, size, data, usage);
}

void APIENTRY NamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data) {
	bindFirstBuffer(buffer);
	glBufferSubData(FIRST_BUFFER_TARGET, offset, size, data);
}

void APIENTRY CopyNamedBufferSubData(GLuint readBuffer,
									 GLuint writeBuffer,
									 GLintptr readOffset,
									 GLintptr writeOffset,
									 GLsizeiptr size) {
	bindFirstBuffer(readBuffer);
	bindSecondBuffer(writeBuffer);
	glCopyBufferSubData(FIRST_BUFFER_TARGET, SECOND_BUFFER_TARGET, readOffset, writeOffset, size);
}

void APIENTRY ClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void* data) {
	UNIMPLEMENTED;
}

void APIENTRY ClearNamedBufferSubData(GLuint buffer,
									  GLenum internalformat,
									  GLintptr offset,
									  GLsizeiptr size,
									  GLenum format,
									  GLenum type,
									  const void* data) {
	UNIMPLEMENTED;
}

void* APIENTRY MapNamedBuffer(GLuint buffer, GLenum access) {
	bindFirstBuffer(buffer);
	return glMapBuffer(FIRST_BUFFER_TARGET, access);
}

void* APIENTRY MapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access) {
	bindFirstBuffer(buffer);
	return glMapBufferRange(FIRST_BUFFER_TARGET, offset, length, access);
}

GLboolean APIENTRY UnmapNamedBuffer(GLuint buffer) {
	bindFirstBuffer(buffer);
	return glUnmapBuffer(FIRST_BUFFER_TARGET);
}

void APIENTRY FlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length) {
	bindFirstBuffer(buffer);
	glFlushMappedBufferRange(FIRST_BUFFER_TARGET, offset, length);
}

void APIENTRY GetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint* params) {
	UNIMPLEMENTED;
}

void APIENTRY GetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64* params) {
	UNIMPLEMENTED;
}

void APIENTRY GetNamedBufferPointerv(GLuint buffer, GLenum pname, void** params) {
	UNIMPLEMENTED;
}

void APIENTRY GetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, void* data) {
	UNIMPLEMENTED;
}


/* Framebuffer object functions */

void APIENTRY CreateFramebuffers(GLsizei n, GLuint* framebuffers) {
	glGenFramebuffers(n, framebuffers);
}

void APIENTRY
NamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {
	GL_state.BindFrameBuffer(framebuffer);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, renderbuffertarget, renderbuffer);
}

void APIENTRY NamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param) {
	UNIMPLEMENTED;
}

void APIENTRY NamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level) {
	GL_state.BindFrameBuffer(framebuffer);
	glFramebufferTexture(GL_FRAMEBUFFER, attachment, texture, level);
}

void APIENTRY
NamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer) {
	GL_state.BindFrameBuffer(framebuffer);

	auto textarget = getTextureTarget(texture);
	if (textarget == GL_TEXTURE_CUBE_MAP) {
		// FramebufferTextureLayer can also handle cube maps in DSA OpenGL but not before that
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_CUBE_MAP_POSITIVE_X + layer, texture, level);
	} else {
		glFramebufferTextureLayer(GL_FRAMEBUFFER, attachment, texture, level, layer);
	}
}

void APIENTRY NamedFramebufferDrawBuffer(GLuint framebuffer, GLenum mode) {
	GL_state.BindFrameBuffer(framebuffer);
	glDrawBuffer(mode);
}

void APIENTRY NamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum* bufs) {
	GL_state.BindFrameBuffer(framebuffer);
	glDrawBuffers(n, bufs);
}

void APIENTRY NamedFramebufferReadBuffer(GLuint framebuffer, GLenum mode) {
	GL_state.BindFrameBuffer(framebuffer);
	glReadBuffer(mode);
}

void APIENTRY InvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum* attachments) {
	UNIMPLEMENTED;
}

void APIENTRY InvalidateNamedFramebufferSubData(GLuint framebuffer,
												GLsizei numAttachments,
												const GLenum* attachments,
												GLint x,
												GLint y,
												GLsizei width,
												GLsizei height) {
	UNIMPLEMENTED;
}

void APIENTRY ClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint* value) {
	UNIMPLEMENTED;
}

void APIENTRY ClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint* value) {
	UNIMPLEMENTED;
}

void APIENTRY ClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat* value) {
	GL_state.BindFrameBuffer(framebuffer);
	glClearBufferfv(buffer, drawbuffer, value);
}

void APIENTRY
ClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) {
	UNIMPLEMENTED;
}

void APIENTRY BlitNamedFramebuffer(GLuint readFramebuffer,
								   GLuint drawFramebuffer,
								   GLint srcX0,
								   GLint srcY0,
								   GLint srcX1,
								   GLint srcY1,
								   GLint dstX0,
								   GLint dstY0,
								   GLint dstX1,
								   GLint dstY1,
								   GLbitfield mask,
								   GLenum filter) {
	GL_state.BindReadFrameBuffer(readFramebuffer);
	GL_state.BindWriteFrameBuffer(drawFramebuffer);
	glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

GLenum APIENTRY CheckNamedFramebufferStatus(GLuint framebuffer, GLenum target) {
	GL_state.BindFrameBuffer(framebuffer);
	return glCheckFramebufferStatus(GL_FRAMEBUFFER);
}

void APIENTRY GetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint* param) {
	UNIMPLEMENTED;
}

void APIENTRY
GetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params) {
	UNIMPLEMENTED;
}

GLuint current_render_buffer = 0;
void bindRenderBuffer(GLuint name) {
	if (current_render_buffer == name) {
		return;
	}
	glBindRenderbuffer(GL_RENDERBUFFER, name);
	current_render_buffer = name;
}

/* Renderbuffer object functions */

void APIENTRY CreateRenderbuffers(GLsizei n, GLuint* renderbuffers) {
	glGenRenderbuffers(n, renderbuffers);
}

void APIENTRY NamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height) {
	bindRenderBuffer(renderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, internalformat, width, height);
}

void APIENTRY NamedRenderbufferStorageMultisample(GLuint renderbuffer,
												  GLsizei samples,
												  GLenum internalformat,
												  GLsizei width,
												  GLsizei height) {
	bindRenderBuffer(renderbuffer);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, internalformat, width, height);
}

void APIENTRY GetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint* params) {
	UNIMPLEMENTED;
}


/* Texture object functions */

void APIENTRY CreateTextures(GLenum target, GLsizei n, GLuint* textures) {
	glGenTextures(n, textures);

	for (GLsizei i = 0; i < n; ++i) {
		GL_state.Texture.SetTarget(target);
		GL_state.Texture.Enable(textures[i]);

		texture_data data{};
		data.target = target;
		texture_lookup.insert(std::make_pair(textures[i], data));
	}
}

void APIENTRY TextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer) {
	auto target = bindTexture(texture);
	glTexBuffer(target, internalformat, buffer);
}

void APIENTRY
TextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) {
	UNIMPLEMENTED;
}

void APIENTRY TextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width) {
	auto target = bindTexture(texture);
	glTexStorage1D(target, levels, internalformat, width);
}

void APIENTRY TextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) {
	auto target = bindTexture(texture);
	glTexStorage2D(target, levels, internalformat, width, height);
}

void APIENTRY
TextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) {
	auto target = bindTexture(texture);
	glTexStorage3D(target, levels, internalformat, width, height, depth);
}

void APIENTRY TextureStorage2DMultisample(GLuint texture,
										  GLsizei samples,
										  GLenum internalformat,
										  GLsizei width,
										  GLsizei height,
										  GLboolean fixedsamplelocations) {
	UNIMPLEMENTED;
}

void APIENTRY TextureStorage3DMultisample(GLuint texture,
										  GLsizei samples,
										  GLenum internalformat,
										  GLsizei width,
										  GLsizei height,
										  GLsizei depth,
										  GLboolean fixedsamplelocations) {
	UNIMPLEMENTED;
}

void APIENTRY TextureSubImage1D(GLuint texture,
								GLint level,
								GLint xoffset,
								GLsizei width,
								GLenum format,
								GLenum type,
								const void* pixels) {
	auto target = bindTexture(texture);
	glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
}

void APIENTRY TextureSubImage2D(GLuint texture,
								GLint level,
								GLint xoffset,
								GLint yoffset,
								GLsizei width,
								GLsizei height,
								GLenum format,
								GLenum type,
								const void* pixels) {
	auto target = bindTexture(texture);
	glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void APIENTRY TextureSubImage3D(GLuint texture,
								GLint level,
								GLint xoffset,
								GLint yoffset,
								GLint zoffset,
								GLsizei width,
								GLsizei height,
								GLsizei depth,
								GLenum format,
								GLenum type,
								const void* pixels) {
	auto target = bindTexture(texture);
	if (target == GL_TEXTURE_CUBE_MAP) {
		Assertion(zoffset >= 0 && zoffset < 6, "Invalid cube map face %i specified for TextureSubImage3D!", zoffset);
		Assertion(depth == 1, "Specifying more than one cube map face is not supported yet!");
		glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + zoffset,
						level,
						xoffset,
						yoffset,
						width,
						height,
						format,
						type,
						pixels);
	} else {
		glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	}
}

void APIENTRY CompressedTextureSubImage1D(GLuint texture,
										  GLint level,
										  GLint xoffset,
										  GLsizei width,
										  GLenum format,
										  GLsizei imageSize,
										  const void* data) {
	auto target = bindTexture(texture);
	glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
}

void APIENTRY CompressedTextureSubImage2D(GLuint texture,
										  GLint level,
										  GLint xoffset,
										  GLint yoffset,
										  GLsizei width,
										  GLsizei height,
										  GLenum format,
										  GLsizei imageSize,
										  const void* data) {
	auto target = bindTexture(texture);
	glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

void APIENTRY CompressedTextureSubImage3D(GLuint texture,
										  GLint level,
										  GLint xoffset,
										  GLint yoffset,
										  GLint zoffset,
										  GLsizei width,
										  GLsizei height,
										  GLsizei depth,
										  GLenum format,
										  GLsizei imageSize,
										  const void* data) {
	auto target = bindTexture(texture);
	glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

void APIENTRY CopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) {
	auto target = bindTexture(texture);
	glCopyTexSubImage1D(target, level, xoffset, x, y, width);
}

void APIENTRY CopyTextureSubImage2D(GLuint texture,
									GLint level,
									GLint xoffset,
									GLint yoffset,
									GLint x,
									GLint y,
									GLsizei width,
									GLsizei height) {
	auto target = bindTexture(texture);
	glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

void APIENTRY CopyTextureSubImage3D(GLuint texture,
									GLint level,
									GLint xoffset,
									GLint yoffset,
									GLint zoffset,
									GLint x,
									GLint y,
									GLsizei width,
									GLsizei height) {
	auto target = bindTexture(texture);
	glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

void APIENTRY TextureParameterf(GLuint texture, GLenum pname, GLfloat param) {
	auto target = bindTexture(texture);
	glTexParameterf(target, pname, param);
}

void APIENTRY TextureParameterfv(GLuint texture, GLenum pname, const GLfloat* param) {
	auto target = bindTexture(texture);
	glTexParameterfv(target, pname, param);
}

void APIENTRY TextureParameteri(GLuint texture, GLenum pname, GLint param) {
	auto target = bindTexture(texture);
	glTexParameteri(target, pname, param);
}

void APIENTRY TextureParameterIiv(GLuint texture, GLenum pname, const GLint* params) {
	auto target = bindTexture(texture);
	glTexParameterIiv(target, pname, params);
}

void APIENTRY TextureParameterIuiv(GLuint texture, GLenum pname, const GLuint* params) {
	auto target = bindTexture(texture);
	glTexParameterIuiv(target, pname, params);
}

void APIENTRY TextureParameteriv(GLuint texture, GLenum pname, const GLint* param) {
	auto target = bindTexture(texture);
	glTexParameteriv(target, pname, param);
}

void APIENTRY GenerateTextureMipmap(GLuint texture) {
	auto target = bindTexture(texture);
	glGenerateMipmap(target);
}

void APIENTRY BindTextureUnit(GLuint unit, GLuint texture) {
	auto target = getTextureTarget(texture);
	GL_state.Texture.Enable(unit, target, texture);
}

void APIENTRY GetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void* pixels) {
	auto target = bindTexture(texture);
	glGetTexImage(target, level, format, type, pixels);
}

void APIENTRY GetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void* pixels) {
	auto target = bindTexture(texture);
	glGetCompressedTexImage(target, level, pixels);
}

void APIENTRY GetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat* params) {
	auto target = bindTexture(texture);
	glGetTexLevelParameterfv(target, level, pname, params);
}

void APIENTRY GetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint* params) {
	auto target = bindTexture(texture);
	glGetTexLevelParameteriv(target, level, pname, params);
}

void APIENTRY GetTextureParameterfv(GLuint texture, GLenum pname, GLfloat* params) {
	auto target = bindTexture(texture);
	glGetTexParameterfv(target, pname, params);
}

void APIENTRY GetTextureParameterIiv(GLuint texture, GLenum pname, GLint* params) {
	auto target = bindTexture(texture);
	glGetTexParameterIiv(target, pname, params);
}

void APIENTRY GetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint* params) {
	auto target = bindTexture(texture);
	glGetTexParameterIuiv(target, pname, params);
}

void APIENTRY GetTextureParameteriv(GLuint texture, GLenum pname, GLint* params) {
	auto target = bindTexture(texture);
	glGetTexParameteriv(target, pname, params);
}


/* Vertex Array object functions */

void APIENTRY CreateVertexArrays(GLsizei n, GLuint* arrays) {
	glGenVertexArrays(n, arrays);
}

void APIENTRY DisableVertexArrayAttrib(GLuint vaobj, GLuint index) {
	GL_state.BindVertexArray(vaobj);
	glDisableVertexAttribArray(index);
}

void APIENTRY EnableVertexArrayAttrib(GLuint vaobj, GLuint index) {
	GL_state.BindVertexArray(vaobj);
	glEnableVertexAttribArray(index);
}

void APIENTRY VertexArrayElementBuffer(GLuint vaobj, GLuint buffer) {
	UNIMPLEMENTED;
}

void APIENTRY
VertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) {
	UNIMPLEMENTED;
}

void APIENTRY VertexArrayVertexBuffers(GLuint vaobj,
									   GLuint first,
									   GLsizei count,
									   const GLuint* buffers,
									   const GLintptr* offsets,
									   const GLsizei* strides) {
	UNIMPLEMENTED;
}

void APIENTRY VertexArrayAttribFormat(GLuint vaobj,
									  GLuint attribindex,
									  GLint size,
									  GLenum type,
									  GLboolean normalized,
									  GLuint relativeoffset) {
	GL_state.BindVertexArray(vaobj);
	glVertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
}

void APIENTRY
VertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) {
	UNIMPLEMENTED;
}

void APIENTRY
VertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) {
	UNIMPLEMENTED;
}

void APIENTRY VertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex) {
	UNIMPLEMENTED;
}

void APIENTRY VertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor) {
	UNIMPLEMENTED;
}

void APIENTRY GetVertexArrayiv(GLuint vaobj, GLenum pname, GLint* param) {
	UNIMPLEMENTED;
}

void APIENTRY GetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint* param) {
	UNIMPLEMENTED;
}

void APIENTRY GetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64* param) {
	UNIMPLEMENTED;
}

/* Sampler object functions */

void APIENTRY CreateSamplers(GLsizei n, GLuint* samplers) {
	UNIMPLEMENTED;
}


/* Program Pipeline object functions */

void APIENTRY CreateProgramPipelines(GLsizei n, GLuint* pipelines) {
	UNIMPLEMENTED;
}


/* Query object functions */

void APIENTRY CreateQueries(GLenum target, GLsizei n, GLuint* ids) {
	UNIMPLEMENTED;
}
void APIENTRY GetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) {
	UNIMPLEMENTED;
}
void APIENTRY GetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) {
	UNIMPLEMENTED;
}
void APIENTRY GetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) {
	UNIMPLEMENTED;
}
void APIENTRY GetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) {
	UNIMPLEMENTED;
}

}

namespace graphics {
namespace opengl {

void emulate_dsa() {
	glad_glCreateTransformFeedbacks = CreateTransformFeedbacks;
	glad_glTransformFeedbackBufferBase = TransformFeedbackBufferBase;
	glad_glTransformFeedbackBufferRange = TransformFeedbackBufferRange;
	glad_glGetTransformFeedbackiv = GetTransformFeedbackiv;
	glad_glGetTransformFeedbacki_v = GetTransformFeedbacki_v;
	glad_glGetTransformFeedbacki64_v = GetTransformFeedbacki64_v;
	glad_glCreateBuffers = CreateBuffers;
	glad_glNamedBufferStorage = NamedBufferStorage;
	glad_glNamedBufferData = NamedBufferData;
	glad_glNamedBufferSubData = NamedBufferSubData;
	glad_glCopyNamedBufferSubData = CopyNamedBufferSubData;
	glad_glClearNamedBufferData = ClearNamedBufferData;
	glad_glClearNamedBufferSubData = ClearNamedBufferSubData;
	glad_glMapNamedBuffer = MapNamedBuffer;
	glad_glMapNamedBufferRange = MapNamedBufferRange;
	glad_glUnmapNamedBuffer = UnmapNamedBuffer;
	glad_glFlushMappedNamedBufferRange = FlushMappedNamedBufferRange;
	glad_glGetNamedBufferParameteriv = GetNamedBufferParameteriv;
	glad_glGetNamedBufferParameteri64v = GetNamedBufferParameteri64v;
	glad_glGetNamedBufferPointerv = GetNamedBufferPointerv;
	glad_glGetNamedBufferSubData = GetNamedBufferSubData;
	glad_glCreateFramebuffers = CreateFramebuffers;
	glad_glNamedFramebufferRenderbuffer = NamedFramebufferRenderbuffer;
	glad_glNamedFramebufferParameteri = NamedFramebufferParameteri;
	glad_glNamedFramebufferTexture = NamedFramebufferTexture;
	glad_glNamedFramebufferTextureLayer = NamedFramebufferTextureLayer;
	glad_glNamedFramebufferDrawBuffer = NamedFramebufferDrawBuffer;
	glad_glNamedFramebufferDrawBuffers = NamedFramebufferDrawBuffers;
	glad_glNamedFramebufferReadBuffer = NamedFramebufferReadBuffer;
	glad_glInvalidateNamedFramebufferData = InvalidateNamedFramebufferData;
	glad_glInvalidateNamedFramebufferSubData = InvalidateNamedFramebufferSubData;
	glad_glClearNamedFramebufferiv = ClearNamedFramebufferiv;
	glad_glClearNamedFramebufferuiv = ClearNamedFramebufferuiv;
	glad_glClearNamedFramebufferfv = ClearNamedFramebufferfv;
	glad_glClearNamedFramebufferfi = ClearNamedFramebufferfi;
	glad_glBlitNamedFramebuffer = BlitNamedFramebuffer;
	glad_glCheckNamedFramebufferStatus = CheckNamedFramebufferStatus;
	glad_glGetNamedFramebufferParameteriv = GetNamedFramebufferParameteriv;
	glad_glGetNamedFramebufferAttachmentParameteriv = GetNamedFramebufferAttachmentParameteriv;
	glad_glCreateRenderbuffers = CreateRenderbuffers;
	glad_glNamedRenderbufferStorage = NamedRenderbufferStorage;
	glad_glNamedRenderbufferStorageMultisample = NamedRenderbufferStorageMultisample;
	glad_glGetNamedRenderbufferParameteriv = GetNamedRenderbufferParameteriv;
	glad_glCreateTextures = CreateTextures;
	glad_glTextureBuffer = TextureBuffer;
	glad_glTextureBufferRange = TextureBufferRange;
	glad_glTextureStorage1D = TextureStorage1D;
	glad_glTextureStorage2D = TextureStorage2D;
	glad_glTextureStorage3D = TextureStorage3D;
	glad_glTextureStorage2DMultisample = TextureStorage2DMultisample;
	glad_glTextureStorage3DMultisample = TextureStorage3DMultisample;
	glad_glTextureSubImage1D = TextureSubImage1D;
	glad_glTextureSubImage2D = TextureSubImage2D;
	glad_glTextureSubImage3D = TextureSubImage3D;
	glad_glCompressedTextureSubImage1D = CompressedTextureSubImage1D;
	glad_glCompressedTextureSubImage2D = CompressedTextureSubImage2D;
	glad_glCompressedTextureSubImage3D = CompressedTextureSubImage3D;
	glad_glCopyTextureSubImage1D = CopyTextureSubImage1D;
	glad_glCopyTextureSubImage2D = CopyTextureSubImage2D;
	glad_glCopyTextureSubImage3D = CopyTextureSubImage3D;
	glad_glTextureParameterf = TextureParameterf;
	glad_glTextureParameterfv = TextureParameterfv;
	glad_glTextureParameteri = TextureParameteri;
	glad_glTextureParameterIiv = TextureParameterIiv;
	glad_glTextureParameterIuiv = TextureParameterIuiv;
	glad_glTextureParameteriv = TextureParameteriv;
	glad_glGenerateTextureMipmap = GenerateTextureMipmap;
	glad_glBindTextureUnit = BindTextureUnit;
	glad_glGetTextureImage = GetTextureImage;
	glad_glGetCompressedTextureImage = GetCompressedTextureImage;
	glad_glGetTextureLevelParameterfv = GetTextureLevelParameterfv;
	glad_glGetTextureLevelParameteriv = GetTextureLevelParameteriv;
	glad_glGetTextureParameterfv = GetTextureParameterfv;
	glad_glGetTextureParameterIiv = GetTextureParameterIiv;
	glad_glGetTextureParameterIuiv = GetTextureParameterIuiv;
	glad_glGetTextureParameteriv = GetTextureParameteriv;
	glad_glCreateVertexArrays = CreateVertexArrays;
	glad_glDisableVertexArrayAttrib = DisableVertexArrayAttrib;
	glad_glEnableVertexArrayAttrib = EnableVertexArrayAttrib;
	glad_glVertexArrayElementBuffer = VertexArrayElementBuffer;
	glad_glVertexArrayVertexBuffer = VertexArrayVertexBuffer;
	glad_glVertexArrayVertexBuffers = VertexArrayVertexBuffers;
	glad_glVertexArrayAttribBinding = VertexArrayAttribBinding;
	glad_glVertexArrayAttribFormat = VertexArrayAttribFormat;
	glad_glVertexArrayAttribIFormat = VertexArrayAttribIFormat;
	glad_glVertexArrayAttribLFormat = VertexArrayAttribLFormat;
	glad_glVertexArrayBindingDivisor = VertexArrayBindingDivisor;
	glad_glGetVertexArrayiv = GetVertexArrayiv;
	glad_glGetVertexArrayIndexediv = GetVertexArrayIndexediv;
	glad_glGetVertexArrayIndexed64iv = GetVertexArrayIndexed64iv;
	glad_glCreateSamplers = CreateSamplers;
	glad_glCreateProgramPipelines = CreateProgramPipelines;
	glad_glCreateQueries = CreateQueries;
	glad_glGetQueryBufferObjecti64v = GetQueryBufferObjecti64v;
	glad_glGetQueryBufferObjectiv = GetQueryBufferObjectiv;
	glad_glGetQueryBufferObjectui64v = GetQueryBufferObjectui64v;
	glad_glGetQueryBufferObjectuiv = GetQueryBufferObjectuiv;

	GLAD_GL_ARB_direct_state_access = 1;

	real_glDeleteTextures = glad_glDeleteTextures;
	glad_glDeleteTextures = DeleteTextures;
}

}
}
