#include "resource/uutResourceCache.h"
#include "resource/uutResource.h"

namespace uut
{
	ResourceCache::ResourceCache(Context* context)
		: Module(context)
	{
	}

	void ResourceCache::AddResource(Resource* resource)
	{
		if (resource == nullptr)
			return;

		SharedPtr<ResourceType> type = GetType(resource->GetType());
		type->resources.Add(SharedPtr<Resource>(resource));
	}

	Resource* ResourceCache::GetResource(const HashString& type, const String& name)
	{
		if (name.Empty())
			return 0;

		const SharedPtr<Resource>& existing = FindResource(type, name);
		//if (existing)
			return existing;

// 		SharedPtr<Resource> resource;
// 		resource = DynamicCast<Resource>(_context->CreateObject(type));
// 		if (!resource)
// 			return 0;
// 
// 		SharedPtr<File> file = SharedPtr<File>(new File(_context));
// 		if (!file->Open(name))
// 			return 0;
// 
// 		resource->SetName(name);
// 		if (!resource->Load(*(file.Get())))
// 		{
// 			return 0;
// 		}
// 
// 		_groups[type]._resources.push_back(resource);
// 		return resource;

	}

	//////////////////////////////////////////////////////////////////////////
	SharedPtr<ResourceCache::ResourceType> ResourceCache::GetType(const HashString& type)
	{
		SharedPtr<ResourceType> group;
		if (!_types.TryGetValue(type, &group))
		{
			group = new ResourceType();
			_types.Add(type, group);
		}

		return group;
	}

	SharedPtr<Resource> ResourceCache::FindResource(const HashString& type, const String& name) const
	{
		SharedPtr<ResourceType> group;
		if (_types.TryGetValue(type, &group))
		{
			for (int i = 0; i < group->resources.Count(); i++)
			{
				if (group->resources[i]->GetName().Equals(name, true))
					return group->resources[i];
			}
		}

		return SharedPtr<Resource>::EMPTY;
	}

}