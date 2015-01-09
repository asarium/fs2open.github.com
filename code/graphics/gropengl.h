/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/ 



#ifndef _GROPENGL_H
#define _GROPENGL_H



#include "graphics/gl/gl_2_1.h"

#ifdef _WIN32
#include "graphics/gl/glu.h"
#elif defined(SCP_UNIX)
#ifdef __APPLE__
#define GL_GLEXT_LEGACY // I'd like to punch the idiot that made this needed
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif // __APPLE__
#endif

#include "globalincs/pstypes.h"
#include "graphics/grinternal.h"

const ubyte GL_zero_3ub[3] = { 0, 0, 0 };

bool gr_opengl_init();
void gr_opengl_cleanup(int minimize=1);
int opengl_check_for_errors(char *err_at = NULL);

#ifndef NDEBUG
#define GL_CHECK_FOR_ERRORS(s)	opengl_check_for_errors((s))
#else
#define GL_CHECK_FOR_ERRORS(s)
#endif

extern int GL_version;

extern int Use_VBOs;
extern int Use_PBOs;
extern int Use_GLSL;

#endif
