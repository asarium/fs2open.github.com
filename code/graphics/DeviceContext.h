#pragma once
//
//

#include "globalincs/pstypes.h"
#include "utils/hash.h"
#include "utils/id.h"

#include <cinttypes>
#include <cstdint>

namespace graphics {

struct device_image_tag {};
using ImageId = ::util::ID<device_image_tag, std::int64_t, -1>;

enum class ImageType { Type2D, Type2DArray, Type3D, TypeCubeMap };

enum class ImageFormat {
	R8,
	R8G8,
	R8G8B8,
	R8G8B8A8,

	R5G5B5,
	R5G5B5A1,

	R16G16B16A16F,
	R32G32B32AF,

	S3tcRgbDxt1,
	S3tcRgbaDxt3,
	S3tcRgbaDxt5,

	DepthComponent,
	DepthComponent24,
	DepthComponent32,
};

enum class DataFormat { A1R5G5B5, A8R8G8B8, B8G8R8, R8, RGB_S3TC_DXT1, RGBA_S3TC_DXT1, RGBA_S3TC_DXT3, RGBA_S3TC_DXT5 };

enum class FilterType { Nearest, Linear };

enum class MipmapMode { Nearest, Linear };

enum class WrapMode { ClampToEdge, Repeat, MirroredRepeat };

struct device_sampler_tag {};
using SamplerId = ::util::ID<device_sampler_tag, std::int64_t, -1>;

struct SamplerParameters {
	FilterType minFilter = FilterType::Nearest;
	FilterType magFilter = FilterType::Nearest;

	MipmapMode mipmapMode = MipmapMode::Nearest;

	WrapMode addressModeU = WrapMode::ClampToEdge;
	WrapMode addressModeV = WrapMode::ClampToEdge;
	WrapMode addressModeW = WrapMode::ClampToEdge;

	bool anisotropyEnable = false;
	float maxAnisotropy = -1.0f;

	explicit SamplerParameters(FilterType minFilter_in = FilterType::Nearest, FilterType magFilter_in = FilterType::Nearest,
	                           MipmapMode mipmapMode_in = MipmapMode::Nearest,
	                           WrapMode addressModeU_in = WrapMode::ClampToEdge,
	                           WrapMode addressModeV_in = WrapMode::ClampToEdge,
	                           WrapMode addressModeW_in = WrapMode::ClampToEdge, bool anisotropyEnable_in = false,
	                           float maxAnisotropy_in = -1.0f);

	friend bool operator==(const SamplerParameters& lhs, const SamplerParameters& rhs);
	friend bool operator!=(const SamplerParameters& lhs, const SamplerParameters& rhs);
};

/**
 * @brief A graphics device context
 *
 * This provides an abstract API for interacting with a graphics API. This API is designed to be similar to the Vulkan
 * API which will ensure that porting to that API in the future will not be an impossible task. If any new functions are
 * added to this API they should be designed with that in mind.
 */
class DeviceContext {
  public:
	virtual ~DeviceContext();

	virtual ImageId createImage(ImageType type, ImageFormat format, uint32_t width, uint32_t height, uint32_t depth,
	                            uint32_t num_mipmaps) = 0;

	virtual void deleteImage(ImageId image) = 0;

	virtual void imageUpdateSubData(ImageId image, uint32_t mipmap_level, uint32_t x, uint32_t y, uint32_t z,
	                                uint32_t width, uint32_t height, uint32_t depth, DataFormat data_format,
	                                size_t data_size, const void* data) = 0;

	virtual void imageGenerateMipmaps(ImageId image) = 0;

	virtual SamplerId createSampler(const SamplerParameters& params) = 0;

	virtual void deleteSampler(SamplerId sampler) = 0;

	virtual void setObjectLabel(ImageId handle, const SCP_string& name)   = 0;
	virtual void setObjectLabel(SamplerId handle, const SCP_string& name) = 0;
};

} // namespace graphics

DEFINE_ENUM_HASH(graphics::FilterType)
DEFINE_ENUM_HASH(graphics::MipmapMode)
DEFINE_ENUM_HASH(graphics::WrapMode)
