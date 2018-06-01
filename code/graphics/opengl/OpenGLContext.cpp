//
//

#include "OpenGLContext.h"

#include "graphics/opengl/gropengl.h"
#include "graphics/opengl/gropenglstate.h"

using namespace graphics;

namespace {

GLenum map_image_type(ImageType type)
{
	switch (type) {
	case ImageType::Type2D:
		return GL_TEXTURE_2D;
	case ImageType::Type2DArray:
		return GL_TEXTURE_2D_ARRAY;
	case ImageType::Type3D:
		return GL_TEXTURE_3D;
	case ImageType::TypeCubeMap:
		return GL_TEXTURE_CUBE_MAP;
	default:
		UNREACHABLE("Unhandled enum value");
		return GL_INVALID_ENUM;
	}
}

GLenum map_image_format(ImageFormat format)
{
	switch (format) {
	case ImageFormat::R8:
		return GL_R8;
	case ImageFormat::R8G8:
		return GL_RG8;
	case ImageFormat::R8G8B8:
		return GL_RGB8;
	case ImageFormat::R8G8B8A8:
		return GL_RGBA8;
	case ImageFormat::R5G5B5:
		return GL_RGB5;
	case ImageFormat::R5G5B5A1:
		return GL_RGB5_A1;
	case ImageFormat::R16G16B16A16F:
		return GL_RGBA16F;
	case ImageFormat::R32G32B32AF:
		return GL_RGB32F;
	case ImageFormat::S3tcRgbDxt1:
		return GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
	case ImageFormat::S3tcRgbaDxt3:
		return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	case ImageFormat::S3tcRgbaDxt5:
		return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	case ImageFormat::DepthComponent:
		return GL_DEPTH_COMPONENT;
	case ImageFormat::DepthComponent24:
		return GL_DEPTH_COMPONENT24;
	case ImageFormat::DepthComponent32:
		return GL_DEPTH_COMPONENT32;
	default:
		UNREACHABLE("Unhandled enum value");
		return GL_INVALID_ENUM;
	}
}

bool format_is_compressed(DataFormat format)
{
	switch (format) {
	case DataFormat::A1R5G5B5:
	case DataFormat::A8R8G8B8:
	case DataFormat::B8G8R8:
	case DataFormat::R8:
		return false;
	case DataFormat::RGB_S3TC_DXT1:
	case DataFormat::RGBA_S3TC_DXT1:
	case DataFormat::RGBA_S3TC_DXT3:
	case DataFormat::RGBA_S3TC_DXT5:
		return true;
	default:
		UNREACHABLE("Unhandled enum value");
		return false;
	}
}

GLenum map_filter_type(FilterType type)
{
	switch (type) {
	case FilterType::Nearest:
		return GL_NEAREST;
	case FilterType::Linear:
		return GL_LINEAR;
	default:
		UNREACHABLE("Unhandled enum value");
		return GL_INVALID_ENUM;
	}
}

GLenum map_filter_mipmap_type(FilterType type, MipmapMode mode)
{
	if (type == FilterType::Nearest && mode == MipmapMode::Nearest) {
		return GL_NEAREST_MIPMAP_NEAREST;
	} else if (type == FilterType::Nearest && mode == MipmapMode::Linear) {
		return GL_NEAREST_MIPMAP_LINEAR;
	} else if (type == FilterType::Linear && mode == MipmapMode::Nearest) {
		return GL_LINEAR_MIPMAP_NEAREST;
	} else if (type == FilterType::Linear && mode == MipmapMode::Linear) {
		return GL_LINEAR_MIPMAP_LINEAR;
	}

	UNREACHABLE("Unhandled enum value");
	return GL_INVALID_ENUM;
}

GLenum map_wrap_mode(WrapMode mode)
{
	switch (mode) {
	case WrapMode::ClampToEdge:
		return GL_CLAMP_TO_EDGE;
	case WrapMode::Repeat:
		return GL_REPEAT;
	case WrapMode::MirroredRepeat:
		return GL_MIRRORED_REPEAT;
	default:
		UNREACHABLE("Unhandled enum value");
		return GL_INVALID_ENUM;
	}
}

std::tuple<GLenum, GLenum> map_data_format(DataFormat format)
{
	switch (format) {
		// GL_BGRA_EXT is *much* faster with some hardware/drivers
	case DataFormat::A1R5G5B5:
		return std::tuple<GLenum, GLenum>(GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV);
	case DataFormat::A8R8G8B8:
		return std::tuple<GLenum, GLenum>(GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV);
	case DataFormat::B8G8R8:
		return std::tuple<GLenum, GLenum>(GL_BGR, GL_UNSIGNED_BYTE);
	case DataFormat::R8:
		return std::tuple<GLenum, GLenum>(GL_RED, GL_UNSIGNED_BYTE);
	case DataFormat::RGB_S3TC_DXT1:
		return std::tuple<GLenum, GLenum>(GL_COMPRESSED_RGB_S3TC_DXT1_EXT, GL_INVALID_ENUM);
	case DataFormat::RGBA_S3TC_DXT1:
		return std::tuple<GLenum, GLenum>(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, GL_INVALID_ENUM);
	case DataFormat::RGBA_S3TC_DXT3:
		return std::tuple<GLenum, GLenum>(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, GL_INVALID_ENUM);
	case DataFormat::RGBA_S3TC_DXT5:
		return std::tuple<GLenum, GLenum>(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, GL_INVALID_ENUM);
	default:
		UNREACHABLE("Unhandled enum value");
		return std::tuple<GLenum, GLenum>(GL_INVALID_ENUM, GL_INVALID_ENUM);
	}
}

void opengl_init_2d_texture(GLenum target, GLuint texture, GLint levels, GLenum internalFormat, GLsizei width,
                            GLsizei height, GLenum data_format, GLenum data_type, const void* data)
{
	GL_state.Texture.SetTarget(target);
	GL_state.Texture.Enable(texture);

	if (GLAD_GL_ARB_texture_storage) {
		glTexStorage2D(target, levels, internalFormat, width, height);

		if (data != nullptr) {
			Assertion(levels == 1, "Multiple levels cannot be initialized using one data pointer!");
			// Need to upload the data separately
			glTexSubImage2D(target, 0, 0, 0, width, height, data_format, data_type, data);
		}
	} else {
		Assertion(data == nullptr || levels == 1, "Multiple levels cannot be initialized using one data pointer!");

		if (target == GL_TEXTURE_CUBE_MAP) {
			Assertion(data == nullptr, "Initial data is not supported for cube maps!");

			// glTexStorage2D automatically handles all cubemap faces but that is not the case for glTexImage2D
			for (auto i = 0; i < 6; ++i) {
				auto mip_width  = width;
				auto mip_height = height;
				for (auto j = 0; j < levels; j++) {
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, j, internalFormat, mip_width, mip_height, 0,
					             data_format, data_type, data);
					mip_width  = std::max(1, (mip_width / 2));
					mip_height = std::max(1, (mip_height / 2));
				}
			}
		} else {
			auto mip_width  = width;
			auto mip_height = height;
			for (auto j = 0; j < levels; j++) {
				glTexImage2D(target, j, internalFormat, mip_width, mip_height, 0, data_format, data_type, data);
				mip_width  = std::max(1, (mip_width / 2));
				mip_height = std::max(1, (mip_height / 2));
			}

			glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, levels);
		}
	}
}
void opengl_init_3d_texture(GLenum target, GLuint texture, GLint levels, GLenum internalFormat, GLsizei width,
                            GLsizei height, GLsizei depth, GLenum data_format, GLenum data_type, const void* data)
{
	GL_state.Texture.SetTarget(target);
	GL_state.Texture.Enable(texture);

	if (GLAD_GL_ARB_texture_storage) {
		// This version has a better way of specifying the texture storage
		glTexStorage3D(target, levels, internalFormat, width, height, depth);

		if (data != nullptr) {
			Assertion(levels == 1, "Multiple levels cannot be initialized using one data pointer!");
			// Need to upload the data separately
			glTexSubImage3D(target, 0, 0, 0, 0, width, height, depth, data_format, data_type, data);
		}
	} else {
		Assertion(data == nullptr || levels == 1, "Multiple levels cannot be initialized using one data pointer!");
		Assertion(target == GL_TEXTURE_2D_ARRAY, "Only 2D texture arrays are supported here!");

		for (auto i = 0; i < levels; i++) {
			glTexImage3D(target, i, internalFormat, width, height, depth, 0, data_format, data_type, nullptr);
			width  = std::max(1, (width / 2));
			height = std::max(1, (height / 2));
		}

		glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, levels);
	}
}

} // namespace

namespace graphics {
namespace opengl {

union id_converter {
	struct {
		GLenum target;
		GLuint handle;
	} gl_vals;
	ImageId::impl_type id_val;

	static_assert(sizeof(gl_vals) == sizeof(id_val),
	              "The size of the texture target + the texture handle is too large to fit into the handle type!");
};

ImageId make_id(GLenum target, GLuint id)
{
	id_converter conv;
	conv.gl_vals.target = target;
	conv.gl_vals.handle = id;

	return ImageId(conv.id_val);
}
std::tuple<GLenum, GLuint> get_gl_texture_values(ImageId id)
{
	if (!id.isValid()) {
		return std::make_tuple(GL_NONE, 0);
	}

	id_converter conv;
	conv.id_val = id.value();

	return std::make_tuple(conv.gl_vals.target, conv.gl_vals.handle);
}
GLuint get_gl_sampler(SamplerId id) { return id.isValid() ? static_cast<GLuint>(id.value()) : 0; }

OpenGLContext::~OpenGLContext() = default;
ImageId OpenGLContext::createImage(ImageType type, ImageFormat format, uint32_t width, uint32_t height, uint32_t depth,
                                   uint32_t num_mipmaps)
{
	GLuint id;
	glGenTextures(1, &id);

	if (id == 0) {
		return ImageId::invalid();
	}
	auto gl_target = map_image_type(type);
	auto gl_format = map_image_format(format);

	GL_state.Texture.SetTarget(gl_target);
	GL_state.Texture.Enable(id);

	switch (type) {
	case ImageType::TypeCubeMap:
		Assertion(depth == 1, "Cube map array textures are not supported at this moment!");
		FALLTHROUGH;
	case ImageType::Type2D:
		opengl_init_2d_texture(gl_target, id, num_mipmaps, gl_format, width, height, GL_RGBA, GL_UNSIGNED_BYTE,
		                       nullptr);
		break;
	case ImageType::Type2DArray:
	case ImageType::Type3D:
		opengl_init_3d_texture(gl_target, id, num_mipmaps, gl_format, width, height, depth, GL_RGBA, GL_UNSIGNED_BYTE,
		                       nullptr);
		break;
	default:
		UNREACHABLE("Unhandled enum value!");
	}

	return make_id(gl_target, id);
}
void OpenGLContext::deleteImage(ImageId image)
{
	GR_DEBUG_SCOPE("Delete texture");

	Assertion(image.isValid(), "Invalid image handle passed!");

	GLenum target;
	GLuint handle;

	std::tie(target, handle) = get_gl_texture_values(image);

	GL_state.Texture.Delete(handle);
	glDeleteTextures(1, &handle);
}
void OpenGLContext::imageUpdateSubData(ImageId image, uint32_t mipmap_level, uint32_t x, uint32_t y, uint32_t z,
                                       uint32_t width, uint32_t height, uint32_t depth, DataFormat data_format,
                                       size_t data_size, const void* data)
{
	Assertion(image.isValid(), "Invalid image handle passed!");

	GLenum target;
	GLuint handle;

	std::tie(target, handle) = get_gl_texture_values(image);
	GL_state.Texture.SetTarget(target);
	GL_state.Texture.Enable(handle);

	GLenum format, type;
	std::tie(format, type) = map_data_format(data_format);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	switch (target) {
	case GL_TEXTURE_2D:
		Assertion(z == 0, "2D textures only have one level!");
		Assertion(depth == 1, "Cannot upload more than one level of data to a 2D texture!");
		if (format_is_compressed(data_format)) {
			glCompressedTexSubImage2D(target, mipmap_level, x, y, width, height, format, data_size, data);
		} else {
			glTexSubImage2D(target, mipmap_level, x, y, width, height, format, type, data);
		}
		break;
	case GL_TEXTURE_2D_ARRAY:
	case GL_TEXTURE_3D:
		if (format_is_compressed(data_format)) {
			glCompressedTexSubImage3D(target, mipmap_level, x, y, z, width, height, depth, format, data_size, data);
		} else {
			glTexSubImage3D(target, mipmap_level, x, y, z, width, height, depth, format, type, data);
		}
		break;
	case GL_TEXTURE_CUBE_MAP:
		Assertion(z < 6, "Cube maps only have 6 faces!");
		Assertion(depth == 1, "Cannot upload more than one level of data to a 2D texture!");
		if (format_is_compressed(data_format)) {
			glCompressedTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + z, mipmap_level, x, y, width, height, format,
			                          data_size, data);
		} else {
			glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + z, mipmap_level, x, y, width, height, format, type, data);
		}
		break;
	default:
		UNREACHABLE("Unhandled enum value");
		break;
	}
}
void OpenGLContext::imageGenerateMipmaps(ImageId image)
{
	Assertion(image.isValid(), "Invalid image handle passed!");

	GLenum target;
	GLuint handle;

	std::tie(target, handle) = get_gl_texture_values(image);
	GL_state.Texture.SetTarget(target);
	GL_state.Texture.Enable(handle);

	glGenerateMipmap(target);
}
SamplerId OpenGLContext::createSampler(const SamplerParameters& params) {
	GLuint sampler;
	glGenSamplers(1, &sampler);

	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, map_wrap_mode(params.addressModeU));
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_R, map_wrap_mode(params.addressModeV));
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, map_wrap_mode(params.addressModeW));

	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, map_filter_mipmap_type(params.minFilter, params.mipmapMode));
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, map_filter_type(params.magFilter));

	if (params.anisotropyEnable) {
		if (GLAD_GL_EXT_texture_filter_anisotropic) {
			glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, params.maxAnisotropy);
		}
	}

	return graphics::SamplerId(static_cast<std::int64_t>(sampler));
}
void OpenGLContext::deleteSampler(SamplerId sampler) {
	auto gl_sampler = get_gl_sampler(sampler);
	glDeleteSamplers(1, &gl_sampler);
}
void OpenGLContext::setObjectLabel(ImageId image, const SCP_string& name)
{
	Assertion(image.isValid(), "Invalid handle passed!");

	GLenum target;
	GLuint handle;

	std::tie(target, handle) = get_gl_texture_values(image);

	setObjectLabel(GL_TEXTURE, handle, name);
}
void OpenGLContext::setObjectLabel(SamplerId sampler, const SCP_string& name)
{
	Assertion(sampler.isValid(), "Invalid handle passed!");

	setObjectLabel(GL_SAMPLER, get_gl_sampler(sampler), name);
}
void OpenGLContext::setObjectLabel(GLenum type, GLuint handle, const SCP_string& name)
{
	if (GLAD_GL_KHR_debug) {
		glObjectLabel(type, handle, (GLsizei)name.size(), name.c_str());
	}
}
} // namespace opengl
} // namespace graphics
