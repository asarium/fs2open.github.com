
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

}

#endif //_UNIFORM_STRUCTS_H
