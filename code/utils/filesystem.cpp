
#include "utils/filesystem.h"

namespace util {
namespace filesystem {

std::time_t last_write_time_t(const path& p) {
#if HAVE_FILESYSTEM || HAVE_EXPERIMENTAL_FILESYSTEM
	auto ftime = util::filesystem::last_write_time(p);
	return file_time_type::clock::to_time_t(ftime);
#else
	return util::filesystem::last_write_time(p);
#endif
}
void create_directories_if_not_exists(const path& dir, util::error_code& err) {
	auto path_status = status(dir, err);

	if (err) {
		return;
	}

	if (exists(path_status)) {
		if (!is_directory(path_status)) {
			mprintf(("Path %s existed but is not a directory!\n", dir.string().c_str()));
			return;
		}
		// Path exists and is a directory
		return;
	}

	util::filesystem::create_directories(dir, err);
}
void create_directories_if_not_exists(const path& p) {
	util::error_code err;
	create_directories_if_not_exists(p, err);

	// Discard error code
}

}
}