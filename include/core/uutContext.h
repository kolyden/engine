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

		void RegisterFactory(IObjectFactory* factory);
		IObjectFactory* GetFactory(const HashString& type) const;

		SharedPtr<Object> CreateObject(const HashString& type) const;

		void AddModule(Module* module);
		Module* GetModule(const HashString& type) const;

		template<class T>void RegisterFactory() { RegisterFactory(new ObjectFactory<T>()); }

	protected:
		Dictionary<HashString, SharedPtr<IObjectFactory>> _factories;
		Dictionary<HashString, SharedPtr<Module>> _modules;
	};
}