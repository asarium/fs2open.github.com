#pragma once
//
//

#include "graphics/DeviceContext.h"

#include "graphics/opengl/gropengl.h"

namespace graphics {
namespace opengl {

ImageId make_id(GLenum target, GLuint id);

/**
 * @brief Extract OpenGL values from an ImageId
 *
 * @warning This will only return valid values if the ImageId was created by OpenGLContext!
 *
 * @param id The id to retrieve the values from
 * @return The texture target, The texture id
 */
std::tuple<GLenum, GLuint> get_gl_texture_values(ImageId id);

inline GLuint get_gl_texture_handle(ImageId id) {
	return std::get<1>(get_gl_texture_values(id));
}

GLuint get_gl_sampler(SamplerId id);

class OpenGLContext : public DeviceContext {
	void setObjectLabel(GLenum type, GLuint handle, const SCP_string& name);

  public:
	~OpenGLContext() override;

	ImageId createImage(ImageType type, ImageFormat format, uint32_t width, uint32_t height, uint32_t depth,
	                    uint32_t num_mipmaps) override;

	void deleteImage(ImageId image) override;

	void imageUpdateSubData(ImageId image, uint32_t mipmap_level, uint32_t x, uint32_t y, uint32_t z, uint32_t width,
	                        uint32_t height, uint32_t depth, DataFormat data_format, size_t data_size,
	                        const void* data) override;

	void imageGenerateMipmaps(ImageId image) override;

	SamplerId createSampler(const SamplerParameters& params) override;
	void deleteSampler(SamplerId sampler) override;

	void setObjectLabel(ImageId image, const SCP_string& name) override;
	void setObjectLabel(SamplerId image, const SCP_string& name) override;
};

} // namespace opengl
} // namespace graphics
