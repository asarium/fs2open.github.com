#include <SDL_syswm.h>

#include "include/cef_version.h"
#include "include/cef_url.h"

#include "bmpman/bmpman.h"
#include "chromium/ClientImpl.h"
#include "chromium/jsapi/jsapi.h"
#include "cmdline/cmdline.h"
#include "graphics/2d.h"
#include "osapi/osapi.h"


namespace
{
	class ForbidEverythingHandler : public CefResourceHandler
	{
	public:
		virtual bool ProcessRequest(CefRefPtr<CefRequest> request, CefRefPtr<CefCallback> callback)
		{
			callback->Continue();
			return true;
		}

		virtual void GetResponseHeaders(CefRefPtr<CefResponse> response, int64& response_length, CefString& redirectUrl)
		{
			// Use forbidden HTTP code
			response->SetStatus(403);
			response_length = 0;
		}

		virtual bool ReadResponse(void* data_out, int bytes_to_read, int& bytes_read, CefRefPtr<CefCallback> callback)
		{
			bytes_read = 0;
			return false;
		}

		virtual void Cancel()
		{
		}

		IMPLEMENT_REFCOUNTING(ForbidEverythingHandler);
	};
}

namespace chromium
{
	ClientImpl::ClientImpl() : bitmapData(nullptr), browserBitmapHandle(-1),
		mPaintingPopup(false), mPosition(0, 0, -1, -1)
	{
		// Don't create the bitmap data
	}

	ClientImpl::ClientImpl(int widthIn, int heightIn)
		: bitmapData(nullptr), browserBitmapHandle(-1),
		mPaintingPopup(false), mPosition(0, 0, widthIn, heightIn)
	{
		resize(widthIn, heightIn);
	}

	ClientImpl::ClientImpl(int xIn, int yIn, int widthIn, int heightIn)
		: bitmapData(nullptr), browserBitmapHandle(-1),
		mPaintingPopup(false), mPosition(xIn, yIn, widthIn, heightIn)
	{
		move(xIn, yIn);
		resize(widthIn, heightIn);
	}

	ClientImpl::~ClientImpl()
	{
		if (browserBitmapHandle >= 0)
		{
			bm_release(browserBitmapHandle);
			browserBitmapHandle = -1;
		}

		if (bitmapData != nullptr)
		{
			vm_free(bitmapData);
			bitmapData = nullptr;
		}
	}

	void ClientImpl::executeCallback(CefString const& callbackName, CefRefPtr<CefListValue> values)
	{
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(jsapi::CALLBACK_MESSAGE_NAME);

		CefRefPtr<CefListValue> argumentList = message->GetArgumentList();

		argumentList->SetString(0, callbackName);
		argumentList->SetList(1, values);

		mainBrowser->SendProcessMessage(PID_RENDERER, message);
	}

	void ClientImpl::executeCallback(CefString const& callbackName, CefRefPtr<CefDictionaryValue> values)
	{
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(jsapi::CALLBACK_MESSAGE_NAME);

		CefRefPtr<CefListValue> argumentList = message->GetArgumentList();

		argumentList->SetString(0, callbackName);
		argumentList->SetDictionary(1, values);

		mainBrowser->SendProcessMessage(PID_RENDERER, message);
	}

	void ClientImpl::move(int x, int y)
	{
		mPosition.x = x;
		mPosition.y = y;
	}

	void ClientImpl::resize(int width, int height)
	{
		if (browserBitmapHandle >= 0)
		{
			bm_release(browserBitmapHandle);
			browserBitmapHandle = -1;
		}

		if (bitmapData != nullptr)
		{
			vm_free(bitmapData);
			bitmapData = nullptr;
		}

		// 32-bit per pixel ==> 4 Bytes for each pixel
		bitmapData = vm_malloc(width * height * 4);
		memset(bitmapData, 0, width * height * 4);

		browserBitmapHandle = bm_create(32, width, height, bitmapData, BMP_TEX_XPARENT);
		mPosition.width = width;
		mPosition.height = height;

		if (getMainBrowser() != nullptr)
		{
			getMainBrowser()->GetHost()->WasResized();
		}
	}

	void ClientImpl::render()
	{
		if (bm_is_valid(browserBitmapHandle))
		{
			gr_set_bitmap(browserBitmapHandle);
			gr_bitmap(mPosition.x, mPosition.y, false);
		}
	}

	bool ClientImpl::forceClose()
	{
		if (mainBrowser == nullptr)
		{
			return false;
		}

		mainBrowser->GetHost()->CloseBrowser(true);

		return false;
	}

	void ClientImpl::setFocused(bool focused)
	{
		mFocused = focused;

		if (mainBrowser != nullptr)
		{
			mainBrowser->GetHost()->SendFocusEvent(mFocused);
		}
	}

	bool ClientImpl::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
	{
		if (mainBrowser == nullptr)
		{
			return false;
		}

		if (!mainBrowser->IsSame(browser))
		{
			return false;
		}

		if (message->GetName() == jsapi::API_MESSAGE_NAME)
		{
			jsapi::processRendererMessage(browser, message);

			return true;
		}

		return false;
	}

    bool ClientImpl::OnBeforePopup(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        const CefString& target_url,
        const CefString& target_frame_name,
        CefLifeSpanHandler::WindowOpenDisposition target_disposition,
        bool user_gesture,
        const CefPopupFeatures& popupFeatures,
        CefWindowInfo& windowInfo,
        CefRefPtr<CefClient>& client,
        CefBrowserSettings& settings,
        bool* no_javascript_access)
	{
		return true; // Always dissallow creating of popups
	}

	void ClientImpl::OnAfterCreated(CefRefPtr<CefBrowser> browser)
	{
		Assertion(mainBrowser.get() == nullptr, "Sub-browsers are not supported!");

		mainBrowser = browser;
	}

	void ClientImpl::OnBeforeClose(CefRefPtr<CefBrowser> browser)
	{
		mainBrowser = nullptr;
	}

	bool ClientImpl::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect)
	{
		rect.width = mPosition.width;
		rect.height = mPosition.height;

		return true;
	}

	bool ClientImpl::GetRootScreenRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
	{
		SDL_GetWindowSize(os_get_window(), &rect.width, &rect.height);
		SDL_GetWindowPosition(os_get_window(), &rect.x, &rect.y);

		return true;
	}

	bool ClientImpl::GetScreenPoint(CefRefPtr<CefBrowser> browser, int viewX, int viewY,
		int& screenX, int& screenY)
	{
		if (os_get_window() == nullptr)
		{
			return false;
		}

		int windowX;
		int windowY;

		SDL_GetWindowPosition(os_get_window(), &windowX, &windowY);

		screenX = windowX + viewX;
		screenY = windowY + viewY;

		return true;
	}

	void ClientImpl::OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type,
		const RectList &dirtyRects, const void *buffer, int width, int height)
	{
		if (mPaintingPopup)
		{
			ActualPaint(type, dirtyRects, buffer, width, height);
			return;
		}

		ActualPaint(type, dirtyRects, buffer, width, height);

		if (type == PET_VIEW && !mPopupRect.IsEmpty())
		{
			mPaintingPopup = true;

			browser->GetHost()->Invalidate(PET_POPUP);

			mPaintingPopup = false;
		}
	}

	void ClientImpl::ActualPaint(PaintElementType type,
		const RectList &dirtyRects, const void *buffer, int width, int height)
	{
		if (type == PET_VIEW)
		{
			Assertion(mPosition.width == width, "Paint event width is not the same as the set width!");
			Assertion(mPosition.height == height, "Paint event height is not the same as the set height!");

			gr_update_texture(browserBitmapHandle, 32, buffer, width, height);
		}
		else if (type == PET_POPUP && mPopupRect.width > 0 && mPopupRect.height > 0)
		{
			gr_update_texture(browserBitmapHandle, 32, buffer, width, height, mPopupRect.x, mPopupRect.y);
		}
	}

	void ClientImpl::OnPopupShow(CefRefPtr<CefBrowser> browser, bool show)
	{
		if (!show)
		{
			ClearPopupRects();
			browser->GetHost()->Invalidate(PET_VIEW);
		}
	}

	void ClientImpl::OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect)
	{
		if (rect.width <= 0 || rect.height <= 0)
			return;

		mOriginalPopupRect = rect;
		mPopupRect = GetPopupRectInWebView(mOriginalPopupRect);
	}

	CefRect ClientImpl::GetPopupRectInWebView(const CefRect& original_rect)
	{
		CefRect rc(original_rect);
		// if x or y are negative, move them to 0.
		if (rc.x < 0)
			rc.x = 0;
		if (rc.y < 0)
			rc.y = 0;
		// if popup goes outside the view, try to reposition origin
		if (rc.x + rc.width > mPosition.width)
			rc.x = mPosition.width - rc.width;
		if (rc.y + rc.height > mPosition.height)
			rc.y = mPosition.height - rc.height;
		// if x or y became negative, move them to 0 again.
		if (rc.x < 0)
			rc.x = 0;
		if (rc.y < 0)
			rc.y = 0;
		return rc;
	}

	void ClientImpl::ClearPopupRects()
	{
		mPopupRect.Set(0, 0, 0, 0);
		mOriginalPopupRect.Set(0, 0, 0, 0);
	}

	CefRefPtr<CefResourceHandler> ClientImpl::GetResourceHandler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request)
	{
		// If this arg is set, allow network access
		if (Cmdline_chromium_network)
		{
			return nullptr;
		}

		CefURLParts parts;
		CefParseURL(request->GetURL(), parts);

		if (CefString(&parts.scheme) == "http" || CefString(&parts.scheme) == "https")
		{
			if (CefString(&parts.host) == "fso")
			{
				// Only allow http|s://fso/... URLs, block everything else
				return nullptr;
			}
		}

		return new ForbidEverythingHandler();
	}
}