
include(WriteCompilerDetectionHeader)

set(REQUIRED_FEATURES cxx_rvalue_references cxx_nullptr)
set(OPTIONAL_FEATURES cxx_variadic_templates cxx_constexpr cxx_deleted_functions
    cxx_final cxx_noexcept cxx_override cxx_alignas cxx_alignof cxx_static_assert
    cxx_attribute_deprecated cxx_thread_local)

target_compile_features(code PUBLIC ${REQUIRED_FEATURES})

write_compiler_detection_header(
  FILE "${GENERATED_SOURCE_DIR}/code/scp_compiler_detection.h"
  PREFIX SCP
  COMPILERS AppleClang Clang GNU MSVC
  FEATURES ${OPTIONAL_FEATURES}
  VERSION 3.2
)
