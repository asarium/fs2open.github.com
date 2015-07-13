
include(WriteCompilerDetectionHeader)

set(REQUIRED_FEATURES cxx_rvalue_references cxx_nullptr)

target_compile_features(code PUBLIC ${REQUIRED_FEATURES})

get_property(CMAKE_CXX_KNOWN_FEATURES GLOBAL PROPERTY CMAKE_CXX_KNOWN_FEATURES)

write_compiler_detection_header(
  FILE "${GENERATED_SOURCE_DIR}/code/scp_compiler_detection.h"
  PREFIX SCP
  COMPILERS AppleClang Clang GNU MSVC
  FEATURES ${CMAKE_CXX_KNOWN_FEATURES}
  VERSION 3.2
)
