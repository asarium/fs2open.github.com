
#ifndef APPLICATION_H
#define APPLICATION_H
#pragma once

#include <map>

#include "main.h"

#include "include/cef_app.h"
#include "include/base/cef_lock.h"

template<class T>
class IDProvider
{
private:
    T m_NextId;
    base::Lock m_idLock;

public:
    IDProvider(const T& nextId = 0) : m_NextId(nextId) {}

    T getAndIncrement()
    {
        base::AutoLock guard(m_idLock);

        return m_NextId++;
    }
};

class Application : public CefApp,
                            CefRenderProcessHandler
{
private:
    std::map<int, std::pair<CefRefPtr<CefV8Value>, CefRefPtr<CefV8Context>>> mApiCallbackMap;

    std::vector<CefString> mApplicationCallbacks;
    std::map<std::pair<int, CefString>, std::pair<CefRefPtr<CefV8Value>, CefRefPtr<CefV8Context>>> mApplicationCallbackMap;

    std::vector<CefString> mAPIFunctions;

    IDProvider<int> mApplicationCallbackIdProvider;

    base::Lock m_lock;

public:
    IDProvider<int> mApiIdProvider;

    Application();

    void AddAPICallbackFunction(int id, CefRefPtr<CefV8Value> function, CefRefPtr<CefV8Context> context);

    int AddApplicationCallback(const CefString& name, CefRefPtr<CefV8Value> function, CefRefPtr<CefV8Context> context);

    bool RemoveApplicationCallback(int id);

    void ExecuteCallback(const CefString& callbackName, CefRefPtr<CefListValue> argList, int argListIndex);

    bool HasCallback(const CefString& callbackName);

    bool HasAPIFunction(const CefString& callbackName);

    // CefApp interface
public:
    virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() { return this; }

    // CefRenderProcessHandler interface
public:
    virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message);

    virtual void OnWebKitInitialized();

    virtual void OnContextReleased(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context);

    virtual void OnRenderThreadCreated(CefRefPtr<CefListValue> extra_info) override;

    IMPLEMENT_REFCOUNTING(Application);
};

#endif // APPLICATION_H
