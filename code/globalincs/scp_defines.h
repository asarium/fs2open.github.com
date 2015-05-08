
#ifndef SCP_DEFINES_H
#define SCP_DEFINES_H
#pragma once

#include "compiler.h"

#ifdef HAS_CXX11_NOEXCEPT
#define SCP_NOEXCEPT noexcept
#else
#define SCP_NOEXCEPT
#endif

#ifdef HAS_CXX11_OVERRIDE
#define SCP_OVERRIDE override
#else
#define SCP_OVERRIDE
#endif


#endif // SCP_DEFINES_H
