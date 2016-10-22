#pragma once

#include "globalincs/pstypes.h"

#if HAVE_FILESYSTEM
#include <filesystem>
#elif HAVE_EXPERIMENTAL_FILESYSTEM
#include <experimental/filesystem>
#else
#include <boost/filesystem.hpp>

#if BOOST_VERSION < 105800
namespace boost
{
namespace filesystem {
// Compatibility code so that range based for loops work with older boost versions
inline directory_iterator begin(directory_iterator __iter) SCP_NOEXCEPT { return __iter; }

inline directory_iterator end(directory_iterator) SCP_NOEXCEPT { return directory_iterator(); }
}
}
#endif
#endif

namespace util {
#if HAVE_FILESYSTEM || HAVE_EXPERIMENTAL_FILESYSTEM
using error_code = std::error_code;
#else
using error_code = boost::system::error_code;
#endif

namespace filesystem {

#if HAVE_FILESYSTEM
#if HAVE_FILESYSTEM_IN_FILESYSTEM
using namespace std::filesystem;
#elif HAVE_FILESYSTEM_IN_EXPERIMENTAL
using namespace std::experimental::filesystem;
#elif HAVE_FILESYSTEM_IN_TR2
using namespace std::tr2::sys;
#else
#error No filesystem namespace found in <filesystem> header!
#endif
#elif HAVE_EXPERIMENTAL_FILESYSTEM
using namespace std::experimental::filesystem;
#else
using namespace boost::filesystem;
#endif

std::time_t last_write_time_t(const path& p);

void create_directories_if_not_exists(const path& p, error_code& err);
void create_directories_if_not_exists(const path& p);
}
}
