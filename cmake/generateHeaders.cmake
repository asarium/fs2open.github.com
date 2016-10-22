

include(Cxx11)
include(platformChecks)

CONFIGURE_FILE(${CMAKE_CURRENT_LIST_DIR}/fred_rc.h.in ${GENERATED_SOURCE_DIR}/fred_rc.h)
