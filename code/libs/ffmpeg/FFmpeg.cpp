
#include "libs/ffmpeg/FFmpeg.h"

#include "FFmpegHeaders.h"

#include "parse/parselo.h"

namespace {
const int MIN_LOG_LEVEL = AV_LOG_ERROR;

bool initialized = false;

void log_callback_report(void* ptr, int level, const char* fmt, va_list vl) {
	if (level > MIN_LOG_LEVEL) {
		return;
	}

	char buffer[1024];
	int print_prefix = 1;
	av_log_format_line(ptr, level, fmt, vl, buffer, sizeof(buffer), &print_prefix);

	mprintf(("FFMPEG Log: %s", buffer)); // no \n, ffmpeg handles that
}
}

namespace libs {
namespace ffmpeg {
void initialize() {
	if (initialized) {
		return;
	}

	av_register_all();

#ifndef NDEBUG
	av_log_set_callback(&log_callback_report);
	av_log_set_level(AV_LOG_ERROR);
#else
	av_log_set_level(AV_LOG_QUIET);
#endif

	mprintf(("FFmpeg library initialized!\n"));
	mprintf(("FFmpeg: License: %s\n", avformat_license()));

	initialized = true;
}
}
}
