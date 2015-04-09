# largely inspired from http://doc.qt.io/qt-5/cmake-manual.html
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Widgets OpenGL REQUIRED)

qt5_wrap_ui(qtfred_UIS ui/mainwindow.ui)
qt5_wrap_cpp(qtfred_MOC include/renderwidget.h include/mainwindow.h)
qt5_add_resources(qtfred_QRC resources/resources.qrc)

set(QTFRED_SRC
    src/main.cpp
    src/fredrender.cpp
    src/fredstubs.cpp
    src/object.cpp
    src/renderwidget.cpp
    src/mainwindow.cpp
    src/editor.cpp

    src/FredRenderer.cpp
)

set(QTFRED_HEADERS
    include/iterators.h
    include/editor.h
    include/fredrender.h
    include/mainwindow.h
    include/object.h
    include/renderwidget.h
    include/wing.h

    include/FredRenderer.h
)

add_executable(qtfred ${EXE_GUI_TYPE}
    ${QTFRED_SRC}
    ${QTFRED_HEADERS}
    ${qtfred_MOC}
    ${qtfred_UIS}
    ${qtfred_QRC}
    $<TARGET_OBJECTS:code_objs>
)
set_target_properties(qtfred PROPERTIES OUTPUT_NAME "qtfred_${FSO_BINARY_SUFFIX}")

SET_TARGET_PROPERTIES(qtfred PROPERTIES DEBUG_POSTFIX "-DEBUG")
target_compile_definitions(qtfred PRIVATE "$<$<CONFIG:RELEASE>:NDEBUG>;$<$<CONFIG:DEBUG>:_DEBUG;$<$<CXX_COMPILER_ID:MSVC>:PDB_DEBUGGING=1>>")

add_definitions(-DFRED)
if(UNIX)
  add_definitions(-DSCP_UNIX -DLUA_USE_LINUX)
endif(UNIX)

target_include_directories(qtfred PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${GENERATED_SOURCE_DIR}
  ${COMPILER_INCLUDES}
  ${PLATFORM_INCLUDES}
)

target_link_libraries(qtfred
    PUBLIC
    code
    Qt5::Widgets Qt5::OpenGL
    ${PLATFORM_LBRARIES} ${COMPILER_LIBRARIES})

include(CreateLaunchers)
create_target_launcher(qtfred
    WORKING_DIRECTORY ${FSO_FREESPACE_PATH}/data
    ARGS ${FSO_RUN_ARGUMENTS})

INSTALL(
    TARGETS qtfred
    RUNTIME DESTINATION ${BINARY_DESTINATION}
    BUNDLE DESTINATION ${BINARY_DESTINATION}
    CONFIGURATIONS Debug Release
)
COPY_FILES_TO_TARGET(qtfred)

if (WIN32)
    set(additional_dlls
        icudt52.dll
        icuin52.dll
        icuuc52.dll
    )

    include(util)
    list_target_dependencies(qtfred qtfred_deps)

    get_target_property (QT_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    execute_process(COMMAND ${QT_QMAKE_EXECUTABLE} -query QT_INSTALL_BINS OUTPUT_VARIABLE QT_INSTALL_BINS OUTPUT_STRIP_TRAILING_WHITESPACE)

    set(file_paths)
    foreach(dep ${qtfred_deps})
        if ("${dep}" MATCHES "(^|;)Qt5::[A-Za-z0-9_]")
            set(file_paths ${file_paths} "$<TARGET_FILE:${dep}>")
        endif ("${dep}" MATCHES "(^|;)Qt5::[A-Za-z0-9_]")
    endforeach(dep)

    foreach(dll ${additional_dlls})
        set(file_paths ${file_paths} "${QT_INSTALL_BINS}/${dll}")
    endforeach(dll)

    foreach(path ${file_paths})
        add_custom_command(TARGET qtfred
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${path}"  "$<TARGET_FILE_DIR:qtfred>"
        VERBATIM)
    endforeach(path)

    install(FILES ${file_paths}
        DESTINATION ${BINARY_DESTINATION}
        CONFIGURATIONS Debug Release
    )
endif(WIN32)
