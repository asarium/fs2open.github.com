set(Boost_USE_STATIC_LIBS TRUE)

find_package(Boost REQUIRED)

add_library(boost INTERFACE)

target_include_directories(boost INTERFACE "${Boost_INCLUDE_DIRS}")
target_link_libraries(boost INTERFACE "${Boost_LIBRARIES}")
