
#include <algorithm>
#include "Application.h"
#include "jsapi.h"
#include "include/cef_runnable.h"

namespace
{
	const char* const API_FIELD_NAME = "name";

	const char* const API_FIELD_ARGS = "args";

	const char* const API_FIELD_CALLBACK = "callback";

	const char* const CALLBACK_REGISTER = "registerCallback";

	const char* const CALLBACK_UNREGISTER = "unregisterCallback";

	template<typename Index, typename List>
	bool setV8Value(const Index& index, List list, CefRefPtr<CefV8Value> value, CefString& exception)
	{
		if (value->IsArray())
		{
			CefRefPtr<CefListValue> newList = CefListValue::Create();
			newList->SetSize(value->GetArrayLength());

			for (int i = 0; i < value->GetArrayLength(); ++i)
			{
				if (!setV8Value(i, newList, value->GetValue(i), exception))
				{
					return false;
				}
			}

			list->SetList(index, newList);
		}
		else if (value->IsBool())
		{
			list->SetBool(index, value->GetBoolValue());
		}
		else if (value->IsDouble())
		{
			list->SetDouble(index, value->GetDoubleValue());
		}
		else if(value->IsInt())
		{
			list->SetInt(index, value->GetIntValue());
		}
		else if (value->IsNull())
		{
			list->SetNull(index);
		}
		else if (value->IsString())
		{
			list->SetString(index, value->GetStringValue());
		}
		else if (value->IsUInt())
		{
			list->SetInt(index, value->GetUIntValue());
		}
		else if (value->IsUndefined())
		{
			list->SetNull(index);
		}
		else if (value->IsObject())
		{
			std::vector<CefString> keys;

			if (!value->GetKeys(keys))
			{
				exception = "Failed to get object keys!";
				return false;
			}

			CefRefPtr<CefDictionaryValue> dictionary = CefDictionaryValue::Create();

			for (const CefString& key : keys)
			{
				if (!setV8Value(key, dictionary, value->GetValue(key), exception))
				{
					return false;
				}
			}

			list->SetDictionary(index, dictionary);
		}
		else
		{
			exception = "The specified argument cannot be passed to a query!";
			return false;
		}

		return true;
	}

	template<typename Index, typename List>
	CefRefPtr<CefV8Value> getV8Value(const Index& index, List list)
	{
		CefValueType type = list->GetType(index);

		switch (type)
		{
		case VTYPE_NULL:
			return CefV8Value::CreateNull();
		case VTYPE_BOOL:
			return CefV8Value::CreateBool(list->GetBool(index));
		case VTYPE_INT:
			return CefV8Value::CreateInt(list->GetInt(index));
		case VTYPE_DOUBLE:
			return CefV8Value::CreateDouble(list->GetDouble(index));
		case VTYPE_STRING:
			return CefV8Value::CreateString(list->GetString(index));
		case VTYPE_DICTIONARY:
		{
			CefRefPtr<CefDictionaryValue> dictionaryVal = list->GetDictionary(index);
			CefRefPtr<CefV8Value> v8Obj = CefV8Value::CreateObject(nullptr);

			CefDictionaryValue::KeyList keys;
			dictionaryVal->GetKeys(keys);

			for (auto& key : keys)
			{
				v8Obj->SetValue(key, getV8Value(key, dictionaryVal), V8_PROPERTY_ATTRIBUTE_NONE);
			}

			return v8Obj;
		}
		case VTYPE_LIST:
		{
			CefRefPtr<CefListValue> listVal = list->GetList(index);
			CefRefPtr<CefV8Value> v8List = CefV8Value::CreateArray(listVal->GetSize());

			for (int i = 0; i < (int)listVal->GetSize(); ++i)
			{
				v8List->SetValue(i, getV8Value(i, listVal));
			}

			return v8List;
		}
		default:
			return CefV8Value::CreateString("Invalid message value type, please report!");
		}
	}

	template<typename IndexType, typename ListType>
	void CopyValue(const IndexType& destIndex, const IndexType& sourceIndex, ListType destination, ListType source)
	{
		CefValueType type = source->GetType(sourceIndex);

		switch (type)
		{
		case VTYPE_NULL:
			destination->SetNull(destIndex);
			break;
		case VTYPE_BOOL:
			destination->SetBool(destIndex, source->GetBool(sourceIndex));
			break;
		case VTYPE_INT:
			destination->SetInt(destIndex, source->GetInt(sourceIndex));
			break;
		case VTYPE_DOUBLE:
			destination->SetDouble(destIndex, source->GetDouble(sourceIndex));
			break;
		case VTYPE_STRING:
			destination->SetString(destIndex, source->GetString(sourceIndex));
			break;
		case VTYPE_DICTIONARY:
		{
			CefRefPtr<CefDictionaryValue> dictionaryVal = source->GetDictionary(sourceIndex);
			CefRefPtr<CefDictionaryValue> newDict = CefDictionaryValue::Create();

			CefDictionaryValue::KeyList keys;
			dictionaryVal->GetKeys(keys);

			for (auto& key : keys)
			{
				CopyValue(key, key, newDict, dictionaryVal);
			}

			destination->SetDictionary(destIndex, newDict);
			break;
		}
		case VTYPE_LIST:
		{
			CefRefPtr<CefListValue> listVal = source->GetList(sourceIndex);
			CefRefPtr<CefListValue> newList = CefListValue::Create();
			newList->SetSize(listVal->GetSize());

			for (int i = 0; i < (int)listVal->GetSize(); ++i)
			{
				CopyValue(i, i, newList, listVal);
			}

			destination->SetList(destIndex, newList);
			break;
		}
		default:
			break;
		}
	}

	class FunctionHandler : public CefV8Handler
	{
	private:
		CefRefPtr<Application> mApplication;

		CefRefPtr<CefProcessMessage> constructAPIMessage(const CefString& name, CefRefPtr<CefV8Value> arg, int& id, CefString& exception)
		{
			id = mApplication->mApiIdProvider.getAndIncrement();

			CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(chromium::jsapi::API_MESSAGE_NAME);

			CefRefPtr<CefListValue> argumentList = message->GetArgumentList();
			argumentList->SetSize(3);

			argumentList->SetInt(0, id);
			argumentList->SetString(1, name);

			// We wrap the argument into a list so we have a uniform interface in the browser process
			CefRefPtr<CefListValue> argumentWrapper = CefListValue::Create();
			argumentWrapper->SetSize(1);

			if (!setV8Value(0, argumentWrapper, arg, exception))
			{
				return nullptr;
			}
			else
			{
				argumentList->SetList(2, argumentWrapper);
				return message;
			}
		}
	public:
		FunctionHandler(CefRefPtr<Application> application) : mApplication(application)
		{}

		void handleQuery(const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
		{
			if (arguments.size() != 1 || !arguments.at(0)->IsObject())
			{
				exception = "A query needs exectly one object paramter!";
				return;
			}

			CefRefPtr<CefV8Value> queryArg = arguments.at(0);

			CefRefPtr<CefV8Value> nameValue = queryArg->GetValue(API_FIELD_NAME);
			if (!nameValue.get() || !nameValue->IsString())
			{
				exception = std::string("Query needs a field named '") + API_FIELD_NAME + "' which is of type string!";
				return;
			}

			CefRefPtr<CefV8Value> callbackValue = queryArg->GetValue(API_FIELD_CALLBACK);
			if (callbackValue.get() && (!callbackValue->IsFunction() && !callbackValue->IsUndefined()))
			{
				exception = std::string("The query field '") + API_FIELD_CALLBACK + "' must be either a function or undefined!";
				return;
			}

			CefRefPtr<CefV8Value> argsValue = queryArg->GetValue(API_FIELD_ARGS);

			if (mApplication->HasAPIFunction(nameValue->GetStringValue()))
			{
				int id;
				CefRefPtr<CefProcessMessage> message = constructAPIMessage(nameValue->GetStringValue(), argsValue, id, exception);

				if (message.get())
				{
					CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
					if (context->GetBrowser()->SendProcessMessage(PID_BROWSER, message))
					{
						if (callbackValue.get() && callbackValue->IsFunction())
						{
							// Save the callback and its ID
							mApplication->AddAPICallbackFunction(id, callbackValue, context);
						}
					}
				}
				else
				{
					// Don't set a return value here so the exception gets thrown
					return;
				}
			}
			else
			{
				exception = std::string("The callback '") + nameValue->GetStringValue().ToString() + "' doesn't exist!";
				return;
			}

			retval = CefV8Value::CreateNull();

			return;
		}

		void handleRegisterCallback(const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
		{
			if (arguments.size() != 2)
			{
				exception = "Exactly two arguments are needed!";
				return;
			}

			if (!arguments.at(0)->IsString())
			{
				exception = "First argument must be a string!";
				return;
			}

			if (!arguments.at(1)->IsFunction())
			{
				exception = "Second argument must be a function!";
				return;
			}

			CefString callbackName = arguments.at(0)->GetStringValue();

			if (!mApplication->HasCallback(callbackName))
			{
				exception = "The specified callback name is not known!";
				return;
			}

			try
			{
				int id = mApplication->AddApplicationCallback(callbackName, arguments.at(1), CefV8Context::GetCurrentContext());

				retval = CefV8Value::CreateInt(id);
			}
			catch (...)
			{
				// Ignore, this is here to not access the context if an exception has been thrown
			}

			return;
		}

		void handleUnregisterCallback(const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
		{
			if (arguments.size() != 1)
			{
				exception = "Need exactly one argument1";
				return;
			}

			if (!arguments.at(0)->IsInt())
			{
				exception = "Argument needs to be an int!";
				return;
			}

			int id = arguments.at(0)->GetIntValue();

			retval = CefV8Value::CreateBool(mApplication->RemoveApplicationCallback(id));
		}

		virtual bool Execute(const CefString& name, CefRefPtr<CefV8Value> object,
			const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
		{
			if (name == "queryFunc")
			{
				handleQuery(arguments, retval, exception);

				return true;
			}
			else if (name == CALLBACK_REGISTER)
			{
				handleRegisterCallback(arguments, retval, exception);

				return true;
			}
			else if (name == CALLBACK_UNREGISTER)
			{
				handleUnregisterCallback(arguments, retval, exception);

				return true;
			}

			return false;
		}

		IMPLEMENT_REFCOUNTING(FunctionHandler)
	};

	void apiCallbackExecutor(bool successfull, CefRefPtr<CefV8Value> function, CefRefPtr<CefV8Context> context, CefRefPtr<CefListValue> arguments)
	{
		context->Enter();

		CefRefPtr<CefV8Value> successVal = CefV8Value::CreateBool(successfull);
		CefRefPtr<CefV8Value> value = getV8Value(2, arguments);

		CefV8ValueList list({ successVal, value });

		// We may not rethrow exceptions!
		function->SetRethrowExceptions(false);
		function->ExecuteFunction(nullptr, list);

		// If there was an exception there is nothing we can do about it so just clear it.
		function->ClearException();

		context->Exit();
	}

	class CallbackTask : public CefTask
	{
	private:
		CefRefPtr<CefV8Value> mFunction;
		
		CefRefPtr<CefV8Context> mContext;

		CefRefPtr<CefListValue> mArguments;

	public:
		CallbackTask(CefRefPtr<CefV8Value> function,
			CefRefPtr<CefV8Context> context,
			CefRefPtr<CefListValue> arguments) :
			mFunction(function), mContext(context), mArguments(arguments)
		{
		}

		void Execute() override
		{
			if (!mContext->IsValid())
			{
				return;
			}

			mContext->Enter();

			CefRefPtr<CefV8Value> value = getV8Value(0, mArguments);

			CefV8ValueList list({ value });

			// We may not rethrow exceptions!
			mFunction->SetRethrowExceptions(false);
			mFunction->ExecuteFunction(nullptr, list);

			// If there was an exception there is nothing we can do about it so just clear it.
			mFunction->ClearException();

			mContext->Exit();
		}

		IMPLEMENT_REFCOUNTING(CallbackTask);
	};

	
}

Application::Application()
{
}

void Application::AddAPICallbackFunction(int id, CefRefPtr<CefV8Value> function, CefRefPtr<CefV8Context> context)
{
	// Make sure we are here only once
	base::AutoLock guard(m_lock);

	mApiCallbackMap.insert(std::make_pair(id, std::make_pair(function, context)));
}

int Application::AddApplicationCallback(const CefString& name, CefRefPtr<CefV8Value> function, CefRefPtr<CefV8Context> context)
{
	// Make sure we are here only once
	base::AutoLock guard(m_lock);

	int id = mApplicationCallbackIdProvider.getAndIncrement();

	mApplicationCallbackMap.insert(std::make_pair(std::make_pair(id, name), std::make_pair(function, context)));

	return id;
}

bool Application::RemoveApplicationCallback(int id)
{
	// Make sure we are here only once
	base::AutoLock guard(m_lock);

	// We sadly need to use this O(n) algorithm
	for (auto it = mApplicationCallbackMap.cbegin(); it != mApplicationCallbackMap.cend();)
	{
		if (it->first.first == id)
		{
			// Erase all entries that use this context
			mApplicationCallbackMap.erase(it++);

			// This assumes that ids are unique, which is hopefully the case
			return true;
		}
		else
		{
			++it;
		}
	}

	return false;
}

void Application::ExecuteCallback(const CefString& callbackName, CefRefPtr<CefListValue> argList, int argListIndex)
{
	// Make sure we are here only once
	base::AutoLock guard(m_lock);

	for (auto it = mApplicationCallbackMap.cbegin(); it != mApplicationCallbackMap.cend(); ++it)
	{
		if (it->first.second == callbackName)
		{
			CefRefPtr<CefListValue> callbackList = CefListValue::Create();
			callbackList->SetSize(1);

			// Copy over the specified argument so we can use it in the callback task
			CopyValue(0, argListIndex, callbackList, argList);

			it->second.second->GetTaskRunner()->PostTask(new CallbackTask(it->second.first, it->second.second, callbackList));
		}
	}
}

bool Application::HasCallback(const CefString& callbackName)
{
	return std::find(mApplicationCallbacks.begin(), mApplicationCallbacks.end(), callbackName) != mApplicationCallbacks.end();
}

bool Application::HasAPIFunction(const CefString& apiFunction)
{
	return std::find(mAPIFunctions.begin(), mAPIFunctions.end(), apiFunction) != mAPIFunctions.end();
}

bool Application::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
	if (message->GetName() == chromium::jsapi::API_MESSAGE_NAME)
	{
		auto argList = message->GetArgumentList();

		int id = argList->GetInt(0);
		bool successfull = argList->GetBool(1);

		// Lock the callback map so we get a consistent view
		base::AutoLock guard(m_lock);

		auto iter = mApiCallbackMap.find(id);

		if (iter == mApiCallbackMap.end())
		{
			// We don't know this ID, the context might already have been released
			return true;
		}

		auto& pair = iter->second;

		CefRefPtr<CefV8Value> function = pair.first;
		CefRefPtr<CefV8Context> context = pair.second;
		// Copy this as we will need it at a later point
		auto argCopy = message->GetArgumentList()->Copy();

		// We must execute the function in the context thread
		context->GetTaskRunner()->PostTask(NewCefRunnableFunction(apiCallbackExecutor, successfull, function, context, argCopy));

		return true;
	}
	else if (message->GetName() == chromium::jsapi::CALLBACK_MESSAGE_NAME)
	{
		CefRefPtr<CefListValue> argumentList = message->GetArgumentList();
		ExecuteCallback(argumentList->GetString(0), argumentList, 1);

		return true;
	}

	return false;
}

// This is an automatically generated header with our extension code
#include "fsoExtension.js.h"

void Application::OnWebKitInitialized()
{
	// Create an instance of my CefV8Handler object.
	CefRefPtr<CefV8Handler> handler = new FunctionHandler(this);

	// Register an extension which exposes the FSO API
	CefRegisterExtension("fsoExtension", FSOExtensionCode, handler);
}

void Application::OnContextReleased(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context)
{
	for (auto it = mApiCallbackMap.cbegin(); it != mApiCallbackMap.cend();)
	{
		if (it->second.second->IsSame(context))
		{
			// Erase all entries that use this context
			mApiCallbackMap.erase(it++);
		}
		else
		{
			++it;
		}
	}

	// Also go through application callbacks
	for (auto it = mApplicationCallbackMap.cbegin(); it != mApplicationCallbackMap.cend();)
	{
		if (it->second.second->IsSame(context))
		{
			// Erase all entries that use this context
			mApplicationCallbackMap.erase(it++);
		}
		else
		{
			++it;
		}
	}
}

void Application::OnRenderThreadCreated(CefRefPtr<CefListValue> extra_info)
{
	auto callbackList = extra_info->GetList(0);

	if (callbackList != nullptr)
	{
		for (int i = 0; i < static_cast<int>(callbackList->GetSize()); ++i)
		{
			mApplicationCallbacks.push_back(callbackList->GetString(i));
		}
	}

	auto extraFunctions = extra_info->GetList(1);

	if (extraFunctions != nullptr)
	{
		for (int i = 0; i < static_cast<int>(extraFunctions->GetSize()); ++i)
		{
			mAPIFunctions.push_back(extraFunctions->GetString(i));
		}
	}
}