
#ifndef _UNIFORM_STRUCTS_H
#define _UNIFORM_STRUCTS_H
#pragma once

namespace graphics {

/**
 * @brief A structure which contains various matrices used while rendering
 *
 * The members are properly aligned for the std140 layout.
 */
struct ViewMatrices {
	matrix4 modelViewMatrix;
	matrix4 modelMatrix;
	matrix4 viewMatrix;
	matrix4 projMatrix;
	matrix4 textureMatrix;
};

struct UniformLight {
	vec4 lightPosition;
	vec3d lightDirection;
	int lightType;
	vec3d lightDiffuseColor;
	float lightAttenuation;
	vec3d lightSpecColor;
	float padding;
};

struct UniformLightData {
	UniformLight lights[MAX_LIGHTS];
	vec3d ambientFactor;
	int n_lights;
	vec3d diffuseFactor;
	float defaultGloss;
	vec3d emissionFactor;
	float padding;
};

}

#endif //_UNIFORM_STRUCTS_H
