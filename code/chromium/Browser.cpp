#include <SDL_events.h>
#include <SDL_keyboard.h>
#include <SDL_syswm.h>
#include <SDL_video.h>
#include "include/cef_version.h"

#include "chromium/chromium.h"
#include "chromium/Browser.h"
#include "chromium/ApplicationImpl.h"

#include "osapi/osapi.h"
#include "io/cursor.h"

namespace
{
	uint32 GetCefModifiers()
	{
		uint32 state = 0;
		SDL_Keymod modifier = SDL_GetModState();

		if (modifier & KMOD_LSHIFT)
		{
			state |= EVENTFLAG_SHIFT_DOWN | EVENTFLAG_IS_LEFT;
		}
		if (modifier & KMOD_RSHIFT)
		{
			state |= EVENTFLAG_SHIFT_DOWN | EVENTFLAG_IS_RIGHT;
		}

		if (modifier & KMOD_LCTRL)
		{
			state |= EVENTFLAG_CONTROL_DOWN | EVENTFLAG_IS_LEFT;
		}
		if (modifier & KMOD_RCTRL)
		{
			state |= EVENTFLAG_CONTROL_DOWN | EVENTFLAG_IS_RIGHT;
		}

		if (modifier & KMOD_LALT)
		{
			state |= EVENTFLAG_ALT_DOWN | EVENTFLAG_IS_LEFT;
		}
		if (modifier & KMOD_RALT)
		{
			state |= EVENTFLAG_ALT_DOWN | EVENTFLAG_IS_RIGHT;
		}

		if (modifier & KMOD_LGUI)
		{
			state |= EVENTFLAG_COMMAND_DOWN | EVENTFLAG_IS_LEFT;
		}
		if (modifier & KMOD_RGUI)
		{
			state |= EVENTFLAG_COMMAND_DOWN | EVENTFLAG_IS_RIGHT;
		}

		if (modifier & KMOD_NUM)
		{
			state |= EVENTFLAG_NUM_LOCK_ON;
		}

		if (modifier & KMOD_CAPS)
		{
			state |= EVENTFLAG_CAPS_LOCK_ON;
		}

		return state;
	}
}

namespace chromium
{
	using namespace boost;
	
	bool Browser::MapMousePosition(CefMouseEvent& event)
	{
		CefRect *position = mClient->getPosition();
		
		if (event.x >= position->x && event.x <= position->x + position->width && event.y > position->y && event.y < position->y + position->width)
		{
			event.x -= position->x;
			event.y -= position->y;

			return true;
		}
		else
		{
			return false;
		}
	}

	bool Browser::MouseEvent(const SDL_Event& event)
	{
		if (mClient->getMainBrowser() == nullptr)
		{
			return false;
		}

		if (!::io::mouse::CursorManager::get()->isCursorShown())
		{
			// Mouse is not shown, don't report mouse events
			return false;
		}

		auto browser = mClient->getMainBrowser();
		auto host = browser->GetHost();

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		{
			CefMouseEvent mouseEvent;
			mouseEvent.x = event.button.x;
			mouseEvent.y = event.button.y;

			if (!MapMousePosition(mouseEvent))
			{
				return false;
			}

			mouseEvent.modifiers = GetCefModifiers();

			CefBrowserHost::MouseButtonType type;

			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				type = MBT_LEFT;
				break;
			case SDL_BUTTON_RIGHT:
				type = MBT_RIGHT;
				break;
			case SDL_BUTTON_MIDDLE:
				type = MBT_MIDDLE;
				break;
			default:
				return true;
			}

			host->SendMouseClickEvent(mouseEvent, type, event.button.state == SDL_RELEASED, 1);

			break;
		}
		case SDL_MOUSEMOTION:
		{
			CefMouseEvent mouseEvent;
			mouseEvent.x = event.motion.x;
			mouseEvent.y = event.motion.y;

			if (!MapMousePosition(mouseEvent))
			{
				return false;
			}

			mouseEvent.modifiers = GetCefModifiers();


			host->SendMouseMoveEvent(mouseEvent, false);
			break;
		}
		case SDL_MOUSEWHEEL:
		{
			CefMouseEvent mouseEvent;

			int mouseX;
			int mouseY;

			SDL_GetMouseState(&mouseX, &mouseY);

			mouseEvent.x = mouseX;
			mouseEvent.y = mouseY;

			if (!MapMousePosition(mouseEvent))
			{
				return false;
			}

			mouseEvent.modifiers = GetCefModifiers();

			// Multiplying it with 120 as that works for windows, needs testing on other platforms
			host->SendMouseWheelEvent(mouseEvent, event.wheel.x * 120, event.wheel.y * 120);
			break;
		}

		default:
			break;
		}

		return true;
	}

	bool Browser::SystemEvent(const SDL_Event& event)
	{
		if (!mClient->isFocused())
		{
			return false;
		}

#ifdef WIN32
		// TODO: Can we unify this and KeyEvent ?
		
		auto message = event.syswm.msg->msg.win.msg;
		auto wParam = event.syswm.msg->msg.win.wParam;
		auto lParam = event.syswm.msg->msg.win.lParam;

		switch (message)
		{
		case WM_SYSCHAR:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_CHAR:
			{
				CefKeyEvent keyEvent;
				keyEvent.windows_key_code = wParam;
				keyEvent.native_key_code = lParam;
				keyEvent.is_system_key = message == WM_SYSCHAR || message == WM_SYSKEYDOWN || message == WM_SYSKEYUP;

				if (message == WM_KEYDOWN || message == WM_SYSKEYDOWN)
				{
					keyEvent.type = KEYEVENT_RAWKEYDOWN;
				}
				else if (message == WM_KEYUP || message == WM_SYSKEYUP)
				{
					keyEvent.type = KEYEVENT_KEYUP;
				}
				else
				{
					keyEvent.type = KEYEVENT_CHAR;
				}

				keyEvent.modifiers = GetCefModifiers();

				if (mClient->getMainBrowser().get())
				{
					mClient->getMainBrowser()->GetHost()->SendKeyEvent(keyEvent);
				}
				
				// We handled the event...
				return true;
			}
		}
#endif

		return false;
	}
	
	bool Browser::KeyEvent(const SDL_Event& event)
	{
		if (!mClient->isFocused())
		{
			return false;
		}
		
#ifdef WIN32
		return true;
#else
		CefKeyEvent keyEvent;
		keyEvent.native_key_code = event.key.keysym.sym;
		
		if (event.type == SDL_KEYDOWN)
		{
			keyEvent.type = KEYEVENT_KEYDOWN;
		}
		else
		{
			keyEvent.type = KEYEVENT_KEYUP;
		}
		
		keyEvent.modifiers = GetCefModifiers();

		if (mClient->getMainBrowser().get())
		{
			mClient->getMainBrowser()->GetHost()->SendKeyEvent(keyEvent);
		}
		
		// We handled the event...
		return true;
#endif
	}

	void Browser::addEventHandler(SDL_EventType type, int weigth,
		const std::function<bool(const SDL_Event&)>& listener)
	{
		mHandlerIdentifiers.push_back(os::addEventListener(type, weigth, listener));
	}

	bool Browser::Create(const CefString& url)
	{
		Assertion(mClient != nullptr, "Can't create browser from default constructed object!");

		if (!validateURL(url))
		{
			Warning(LOCATION, "The specified URL '%s' is not a valid file!", url.ToString().c_str());
			return false;
		}

		CefWindowInfo info;

		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version); // initialize info structure with SDL version info

		if (!SDL_GetWindowWMInfo(os_get_window(), &wmInfo))
		{
			// call failed
			mprintf(("Couldn't get window information: %s\n", SDL_GetError()));
			return false;
		}

		CefBrowserSettings settings;
		
		#ifdef WIN32
			info.SetAsWindowless(wmInfo.info.win.window, mTransparent);
		#else
			info.SetAsWindowless(0, mTransparent);
		#endif
		
		settings.windowless_frame_rate = 60;
		
		settings.java = STATE_DISABLED;
		settings.javascript_close_windows = STATE_DISABLED;
		settings.javascript_open_windows = STATE_DISABLED;
		settings.plugins = STATE_DISABLED;
		
		CefString(&settings.default_encoding).FromASCII("UTF-8");

		return CefBrowserHost::CreateBrowser(info, mClient.get(), url, settings, nullptr);
	}

	void Browser::SetFocused(bool focused)
	{
		mClient->setFocused(focused);
	}

	void Browser::RegisterEventHandlers()
	{
		auto mouseHandler = std::bind(&Browser::MouseEvent, this, std::placeholders::_1);
		auto systemHandler = std::bind(&Browser::SystemEvent, this, std::placeholders::_1);
		auto keyHandler = std::bind(&Browser::KeyEvent, this, std::placeholders::_1);

		addEventHandler(SDL_MOUSEBUTTONDOWN, os::DEFAULT_LISTENER_WEIGHT - 1, mouseHandler);
		addEventHandler(SDL_MOUSEBUTTONUP, os::DEFAULT_LISTENER_WEIGHT - 1, mouseHandler);
		addEventHandler(SDL_MOUSEMOTION, os::DEFAULT_LISTENER_WEIGHT - 1, mouseHandler);
		addEventHandler(SDL_MOUSEWHEEL, os::DEFAULT_LISTENER_WEIGHT - 1, mouseHandler);

		addEventHandler(SDL_SYSWMEVENT, os::DEFAULT_LISTENER_WEIGHT - 1, systemHandler);

		addEventHandler(SDL_KEYDOWN, os::DEFAULT_LISTENER_WEIGHT - 1, keyHandler);
		addEventHandler(SDL_KEYUP, os::DEFAULT_LISTENER_WEIGHT - 1, keyHandler);

		addEventHandler(SDL_WINDOWEVENT, os::DEFAULT_LISTENER_WEIGHT - 1, [&](const SDL_Event& event)
		{
			auto browser = mClient->getMainBrowser();
			auto host = browser->GetHost();

			if (event.window.windowID == SDL_GetWindowID(os_get_window())) {
				switch (event.window.event) {
				case SDL_WINDOWEVENT_LEAVE:
					host->SendCaptureLostEvent();
					return true;
				}
			}

			return false;
		});
	}

	void Browser::RemoveEventHandlers()
	{
		for (auto ident : mHandlerIdentifiers)
		{
			os::removeEventListener(ident);
		}
	}

	void Browser::Close()
	{
		if (GetClient()->getMainBrowser() != nullptr)
		{
			GetClient()->getMainBrowser()->GetHost()->CloseBrowser(true);
		}
	}

	void Browser::LoadURL(const CefString& string)
	{
		if (!validateURL(string))
		{
			Warning(LOCATION, "The specified URL '%s' is not a valid file!", string.ToString().c_str());
			return;
		}

		if (GetClient()->getMainBrowser().get())
		{
			GetClient()->getMainBrowser()->GetMainFrame()->LoadURL(string);
		}
	}

	void Browser::Move(size_t x, size_t y)
	{
		GetClient()->move(static_cast<int>(x), static_cast<int>(y));
	}

	void Browser::Resize(size_t width, size_t height)
	{
		GetClient()->resize(static_cast<int>(width), static_cast<int>(height));
	}

	shared_ptr<Browser> Browser::CreateOffScreenBrowser(size_t x, size_t y, size_t width, size_t height, bool transparent)
	{
		if (!chromium::isInited())
		{
			Warning(LOCATION, "Chromium subsystem is not inited, that either means you haven't enabled chromium in your mod table or created a browser too early.");
			return nullptr;
		}

		int i_width, i_height;

		if (width == (size_t) -1 && height == (size_t) -1)
		{
			SDL_GetWindowSize(os_get_window(), &i_width, &i_height);
		}
		else
		{
			i_width = static_cast<int>(width);
			i_height = static_cast<int>(height);
		}

		shared_ptr<Browser> browser = shared_ptr<Browser>(new Browser());
		browser->mTransparent = transparent;

		browser->mClient = new ClientImpl(static_cast<int>(x), static_cast<int>(y), i_width, i_height);

		addBrowserInstance(weak_ptr<Browser>(browser));

		return browser;
	}
}
