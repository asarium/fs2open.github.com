//
//

#include "DeviceContext.h"

namespace graphics {
DeviceContext::~DeviceContext() = default;

SamplerParameters::SamplerParameters(FilterType minFilter_in, FilterType magFilter_in, MipmapMode mipmapMode_in,
                                     WrapMode addressModeU_in, WrapMode addressModeV_in, WrapMode addressModeW_in,
                                     bool anisotropyEnable_in, float maxAnisotropy_in)
    : minFilter(minFilter_in), magFilter(magFilter_in), mipmapMode(mipmapMode_in), addressModeU(addressModeU_in),
      addressModeV(addressModeV_in), addressModeW(addressModeW_in), anisotropyEnable(anisotropyEnable_in),
      maxAnisotropy(maxAnisotropy_in)
{
}
bool operator==(const SamplerParameters& lhs, const SamplerParameters& rhs)
{
	return lhs.minFilter == rhs.minFilter && lhs.magFilter == rhs.magFilter && lhs.mipmapMode == rhs.mipmapMode &&
	       lhs.addressModeU == rhs.addressModeU && lhs.addressModeV == rhs.addressModeV &&
	       lhs.addressModeW == rhs.addressModeW && lhs.anisotropyEnable == rhs.anisotropyEnable &&
	       lhs.maxAnisotropy == rhs.maxAnisotropy;
}
bool operator!=(const SamplerParameters& lhs, const SamplerParameters& rhs) { return !(rhs == lhs); }
}
