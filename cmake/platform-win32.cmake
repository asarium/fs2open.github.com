
MESSAGE(STATUS "Configuring Windows specific things and stuff...")

SET(PLATFORM_INCLUDES "" CACHE INTERNAL "Compiler specific includes")
SET(PLATFORM_LBRARIES "" CACHE INTERNAL "Compiler specific libraries")

# DirectX libraries are still used on windows
SET(DIRECTX_DIRECTORY ${CMAKE_SOURCE_DIR}/code/directx)

SET(PLATFORM_LBRARIES
	comctl32.lib
	msacm32.lib
	odbc32.lib
	odbccp32.lib
	vfw32.lib
	winmm.lib
	wsock32.lib)


ADD_DEFINITIONS(-DWIN32)
ADD_DEFINITIONS(-DUSE_OPENAL)
ADD_DEFINITIONS(-D_WINDOWS)

SET(EXE_GUI_TYPE WIN32)
