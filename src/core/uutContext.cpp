#include "core/uutContext.h"
#include "core/uutModule.h"

namespace uut
{
	Context::Context() {}

	void Context::RegisterFactory(IObjectFactory* factory)
	{
		if (factory == 0)
			return;

		_factories.Add(factory->GetType(), SharedPtr<IObjectFactory>(factory));
	}

	IObjectFactory* Context::GetFactory(const HashString& type) const
	{
		SharedPtr<IObjectFactory> factory;
		if (!_factories.TryGetValue(type, &factory))
			return 0;

		return factory;
	}

	SharedPtr<Object> Context::CreateObject(const HashString& type) const
	{
		IObjectFactory* factory = GetFactory(type);
		if (factory == 0)
			return SharedPtr<Object>::EMPTY;

		return SharedPtr<Object>(factory->Create());
	}

	void Context::AddModule(Module* module)
	{
		if (module == 0)
			return;

		_modules.Add(module->GetBaseType(), SharedPtr<Module>(module));
		_modules.Add(module->GetType(), SharedPtr<Module>(module));
		module->OnRegister();
	}

	Module* Context::GetModule(const HashString& type) const
	{
		SharedPtr<Module> module;
		if (!_modules.TryGetValue(type, &module))
			return 0;

		return module;
	}

}