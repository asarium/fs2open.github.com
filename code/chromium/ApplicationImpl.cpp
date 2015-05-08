
#include "chromium/ApplicationImpl.h"
#include "cfile/cfile.h"

#include <boost/unordered_map.hpp>

#include "include/cef_url.h"
#include "include/wrapper/cef_stream_resource_handler.h"

#include "VFSPP/util.hpp"
#include <boost/thread/lock_guard.hpp>
#include <chromium/jsapi/jsapi.h>

namespace
{
	CefString getExtension(const SCP_string& other)
	{
		size_t slash = other.find_last_of(vfspp::DirectorySeparatorStr);
		size_t dot = other.find_last_of(".");

		if (slash > dot)
		{
			return CefString();
		}
		
		if (dot != SCP_string::npos)
		{
			return CefString(other.substr(dot + 1).c_str());
		}
		
		return CefString();
	}
}

namespace chromium
{
	bool validateURL(const CefString& url)
	{
		CefURLParts parts;
		CefParseURL(url, parts);

		std::string path = CefString(&parts.path).ToString();

		SCP_string filePath = vfspp::util::normalizePath(path).c_str();

		return cfile::exists(filePath);
	}

	class CFileHandlerFactory : public CefSchemeHandlerFactory
	{
	public:
		CFileHandlerFactory()
		{
		}

		virtual CefRefPtr<CefResourceHandler> Create(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame, const CefString& scheme_name, CefRefPtr<CefRequest> request) override;

		IMPLEMENT_REFCOUNTING(CFileHandlerFactory);
	};
	
	class CFileHandler : public CefReadHandler
	{
	private:
		cfile::FileHandle* handle;

	public:
		explicit CFileHandler(cfile::FileHandle* handleIn) : handle(handleIn) {}

		~CFileHandler()
		{
			if (handle != nullptr)
			{
				cfile::io::close(handle);
			}
		}

		virtual size_t Read(void* ptr, size_t size, size_t n) override
		{
			return cfile::io::read(ptr, size, n, handle);
		}

		virtual int Seek(int64 offset, int whence) override
		{
			cfile::SeekMode mode;
			switch (whence)
			{
			case SEEK_CUR:
				mode = cfile::SEEK_MODE_CUR;
				break;
			case SEEK_END:
				mode = cfile::SEEK_MODE_END;
				break;
			case SEEK_SET:
				mode = cfile::SEEK_MODE_SET;
				break;
			default:
				mode = cfile::SEEK_MODE_SET;
				break;
			}

			return cfile::io::seek(handle, static_cast<int>(offset), mode);
		}

		virtual int64 Tell() override
		{
			return cfile::io::tell(handle);
		}

		virtual int Eof() override
		{
			return cfile::io::eof(handle) ? 1 : 0;
		}
		
		virtual bool MayBlock() override
		{
			return true;
		}

		IMPLEMENT_REFCOUNTING(CFileHandler);
	};

	CefRefPtr<CefResourceHandler> CFileHandlerFactory::Create(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame, const CefString& scheme_name, CefRefPtr<CefRequest> request)
	{
		if (!validateURL(request->GetURL()))
		{
			// URL is not valid!
			return nullptr;
		}

		CefURLParts parts;
		CefParseURL(request->GetURL(), parts);

		std::string path = CefString(&parts.path).ToString();

		SCP_string filePath = vfspp::util::normalizePath(path).c_str();

		cfile::FileHandle *handle = cfile::io::open(filePath);

		if (handle == nullptr)
		{
			return nullptr;
		}
		
		auto mimeType = CefGetMimeType(getExtension(filePath));
		// Return a new resource handler instance to handle the request.
		return new CefStreamResourceHandler(mimeType, CefStreamReader::CreateForHandler(new CFileHandler(handle)));
	}

	void ApplicationImpl::AddCallbackName(CefString const& name)
	{
		boost::lock_guard<boost::mutex> guard(mCallbacknamesLock);

		mCallbackNames.push_back(name);
	}

	void ApplicationImpl::RemoveCallback(CefString const& name)
	{
		boost::lock_guard<boost::mutex> guard(mCallbacknamesLock);

		mCallbackNames.erase(remove(mCallbackNames.begin(), mCallbackNames.end(), name));
	}

	void ApplicationImpl::OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar)
	{
		// Register custom schemes here
	}

	void ApplicationImpl::OnRenderProcessThreadCreated(CefRefPtr<CefListValue> extra_info)
	{
		boost::lock_guard<boost::mutex> guard(mCallbacknamesLock);

		CefRefPtr<CefListValue> callbackNames = CefListValue::Create();
		callbackNames->SetSize(mCallbackNames.size());

		int i = 0;
		for (auto& name : mCallbackNames)
		{
			callbackNames->SetString(i, name);

			++i;
		}

		extra_info->SetList(0, callbackNames);

		SCP_vector<CefString> apiFunctions;
		jsapi::getFunctionNames(apiFunctions);

		CefRefPtr<CefListValue> extraFunctions = CefListValue::Create();
		extraFunctions->SetSize(apiFunctions.size());

		i = 0;
		for (auto& name : apiFunctions)
		{
			extraFunctions->SetString(i, name);

			++i;
		}

		extra_info->SetList(1, extraFunctions);
	}

	void ApplicationImpl::OnContextInitialized()
	{
		CefRegisterSchemeHandlerFactory("http", "fso", new CFileHandlerFactory());
	}
}
