
INCLUDE(util)

MESSAGE(STATUS "Configuring UNIX specific things and stuff...")

target_compile_definitions(platform INTERFACE SCP_UNIX USE_OPENAL)

FIND_PACKAGE(OpenGL REQUIRED)

target_include_directories(platform INTERFACE ${PLATFORM_INCLUDES} ${OPENGL_INCLUDE_DIR})
target_link_libraries(platform INTERFACE ${PLATFORM_LBRARIES} ${OPENGL_LIBRARY})

IF(APPLE)
	include(platform-mac)
ELSE(APPLE)
	SET(EXE_GUI_TYPE)
ENDIF(APPLE)
