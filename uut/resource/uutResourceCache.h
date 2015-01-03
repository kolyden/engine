#pragma once
#include "core/uutModule.h"
#include "container/uutDictionary.h"
#include "container/uutList.h"
#include "core/uutPtr.h"
#include "io/uutPath.h"

namespace uut
{
	class Resource;
	class ResourceLoader;

	class ResourceCache : public Module
	{
		OBJECT(ResourceCache)
	public:
		ResourceCache(Context* context);

		void AddResource(Resource* resource, const Path& path);
		Resource* GetResource(const HashString& type, const Path& name);

		void AddLoader(ResourceLoader* loader);
		ResourceLoader* GetLoader(const HashString& type) const;

		Resource* Load(const HashString& type, const Path& path);
		template<class T>T* Load(const Path& path) { return dynamic_cast<T*>(Load(T::GetTypeStatic(), path)); }

	protected:
		struct ResourceGroup : RefCounted
		{
			Dictionary<Path,SharedPtr<Resource>> resources;
		};

		Dictionary<HashString, SharedPtr<ResourceLoader>> _loaders;
		Dictionary<HashString, SharedPtr<ResourceGroup>> _types;

		SharedPtr<ResourceGroup> GetGroup(const HashString& type);
		SharedPtr<Resource> FindResource(const HashString& type, const Path& name) const;
	};
}