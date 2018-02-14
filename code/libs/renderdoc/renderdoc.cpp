
#include "renderdoc.h"
#include "renderdoc_app.h"

#include "globalincs/pstypes.h"

#include <dlfcn.h>

namespace {
bool api_loaded = false;
RENDERDOC_API_1_1_1* api;

pRENDERDOC_GetAPI load_getAPI() {
#ifdef SCP_UNIX
	auto handle = dlopen("librenderdoc.so", RTLD_NOLOAD);
	auto symbol = dlsym(handle, "RENDERDOC_GetAPI");

	if (handle != nullptr) {
		dlclose(handle);
	}

	return (pRENDERDOC_GetAPI)symbol;
#else
	Assertion(false, "Renderdoc API loading is not implemented for this platform yet!");
	return nullptr;
#endif
}

}

namespace renderdoc {

bool loadApi() {
	if (api_loaded) {
		return true;
	}

	auto getAPI = load_getAPI();

	mprintf(("getAPI: %p\n", getAPI));

	if (getAPI == nullptr) {
		return false;
	}

	auto res = getAPI(eRENDERDOC_API_Version_1_1_1, reinterpret_cast<void**>(&api));

	mprintf(("getAPI ret: %d\n", res));

	if (res != 1) {
		return false;
	}

	api_loaded = true;

	return true;
}

void triggerCapture() {
	if (!api_loaded) {
		// Do nothing if API is not available
		return;
	}

	api->TriggerCapture();
}
void startCapture() {
	if (api_loaded) {
		api->StartFrameCapture(nullptr, nullptr);
	}
}
bool isCapturing() {
	if (api_loaded) {
		return api->IsFrameCapturing() == 1;
	}

	return false;
}
void endCapture() {
	if (api_loaded) {
		api->EndFrameCapture(nullptr, nullptr);
	}
}

}
