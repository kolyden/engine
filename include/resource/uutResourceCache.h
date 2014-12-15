#pragma once
#include "core/uutModule.h"
#include "container/uutDictionary.h"
#include "container/uutList.h"
#include "core/uutPtr.h"

namespace uut
{
	class Resource;

	class ResourceCache : public Module
	{
		OBJECT(ResourceCache)
	public:
		ResourceCache(Context* context);

		void AddResource(Resource* resource);
		Resource* GetResource(const HashString& type, const String& name);

	protected:
		struct ResourceType : RefCounted
		{
			List<SharedPtr<Resource>> resources;
		};

		Dictionary<HashString, SharedPtr<ResourceType>> _types;

		SharedPtr<ResourceType> GetType(const HashString& type);
		SharedPtr<Resource> FindResource(const HashString& type, const String& name) const;
	};
}