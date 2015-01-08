#pragma once
#include "core/uutModule.h"
#include "container/uutDictionary.h"
#include "container/uutList.h"
#include "core/uutPtr.h"

namespace uut
{
	class Resource;
	class ResourceLoader;

	class ResourceCache : public Module
	{
		OBJECT(ResourceCache)
	public:
		ResourceCache(Context* context);

		void AddResource(Resource* resource, const String& path);
		Resource* GetResource(const HashString& type, const String& name);

		void AddLoader(ResourceLoader* loader);
		ResourceLoader* GetLoader(const HashString& type) const;

		Resource* Load(const HashString& type, const String& path);
		template<class T>T* Load(const String& path) { return dynamic_cast<T*>(Load(T::GetTypeStatic(), path)); }

	protected:
		struct ResourceGroup : RefCounted
		{
			Dictionary<String, SharedPtr<Resource>> resources;
		};

		Dictionary<HashString, SharedPtr<ResourceLoader>> _loaders;
		Dictionary<HashString, SharedPtr<ResourceGroup>> _types;

		SharedPtr<ResourceGroup> GetGroup(const HashString& type);
	};
}