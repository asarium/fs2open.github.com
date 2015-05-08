
#include "chromium/ChromiumStateLogic.h"
#include "chromium/ClientImpl.h"
#include "osapi/osapi.h"
#include "graphics/2d.h"
#include "sound/sound.h"
#include "io/cursor.h"
#include "graphics/gropengl.h"

#include "freespace.h"

#include <ctime>
#include <SDL_video.h>
#include <SDL_syswm.h>

#include "include/cef_app.h"

namespace chromium
{
	ChromiumStateLogic::ChromiumStateLogic(const SCP_string& url) : mBrowser(nullptr), mLastUpdate(0)
	{
		mInitialUrl.FromString(url.c_str());

		int width, height;
		SDL_GetWindowSize(os_get_window(), &width, &height);

		mBrowser = Browser::CreateOffScreenBrowser(0, 0, width, height, false);
	}

	void ChromiumStateLogic::enterState(GameState oldState)
	{
		if (!mBrowser->Create(mInitialUrl))
		{
			Error(LOCATION, "Failed to initialize browser!");
		}

		mBrowser->RegisterEventHandlers();
		mBrowser->SetFocused(true);

		mLastUpdate = 0;
	}

	void ChromiumStateLogic::doFrame()
	{
		io::mouse::CursorManager::doFrame();

		clock_t now = clock();

		if (mLastUpdate != 0 && (static_cast<float>(now - mLastUpdate) / CLOCKS_PER_SEC) <= 1.0f / 60.0f)
		{
			os_sleep(5);
			return;
		}

		gr_set_color(255, 255, 255);
		gr_clear();

		if (mBrowser)
		{
			mBrowser->GetClient()->render();
		}

		gr_flip();

		mLastUpdate = clock();
	}

	void ChromiumStateLogic::leaveState(GameState newState)
	{
		mBrowser->RemoveEventHandlers();

		if (mBrowser)
		{
			mBrowser->Close();
		}
	}
}
