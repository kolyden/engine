#pragma once
#include "container/uutDictionary.h"
#include "core/uutObject.h"
#include "core/uutPtr.h"

namespace uut
{
	class Module;

	class UUT_API Context
	{
	public:
		Context();

		void Init();

		void RegisterFactory(IObjectFactory* factory);
		IObjectFactory* GetFactory(const HashString& type) const;

		template<class T>SharedPtr<T> NewObject() { return SharedPtr<T>(new T(this)); }

		SharedPtr<Object> CreateObject(const HashString& type) const;

		void AddModule(Module* module);
		Module* GetModule(const HashString& type) const;

		template<class T>void RegisterFactory() { RegisterFactory(new ObjectFactory<T>(this)); }
		template<class T> T* GetModule()
		{
			T* module = static_cast<T*>(GetModule(T::GetTypeStatic()));
			if (!module)
				module = static_cast<T*>(GetModule(T::GetBaseTypeStatic()));
			return module;
		}

	protected:
		bool _inited;
		Dictionary<HashString, SharedPtr<IObjectFactory>> _factories;
		Dictionary<HashString, SharedPtr<Module>> _modules;
	};
}