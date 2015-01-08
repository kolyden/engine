#include "uutResourceCache.h"
#include "uutResource.h"
#include "uutResourceLoader.h"
#include "core/uutDebug.h"
#include "io/uutFileStream.h"

namespace uut
{
	ResourceCache::ResourceCache(Context* context)
		: Module(context)
	{
	}

	void ResourceCache::AddResource(Resource* resource, const String& path)
	{
		if (resource == nullptr)
			return;

		resource->_resourcePath = path;
		SharedPtr<ResourceGroup> type = GetGroup(resource->GetType());
		type->resources.Add(path, SharedPtr<Resource>(resource));
	}

	Resource* ResourceCache::GetResource(const HashString& type, const String& name)
	{
		SharedPtr<ResourceGroup> group;
		if (_types.TryGetValue(type, &group))
		{
			SharedPtr<Resource> res;
			if (group->resources.TryGetValue(name, &res))
				return res;
		}

		return SharedPtr<Resource>::EMPTY;
	}

	void ResourceCache::AddLoader(ResourceLoader* loader)
	{
		if (loader == 0)
			return;

		_loaders.Add(loader->GetResourceType(), SharedPtr<ResourceLoader>(loader));
	}

	ResourceLoader* ResourceCache::GetLoader(const HashString& type) const
	{
		SharedPtr<ResourceLoader> loader;
		if (_loaders.TryGetValue(type, &loader))
			return loader;

		return SharedPtr<ResourceLoader>::EMPTY;
	}

	Resource* ResourceCache::Load(const HashString& type, const String& path)
	{
		auto existing = GetResource(type, path);
		if (existing)
			return existing;

		auto loader = GetLoader(type);
		if (!loader)
		{
			Debug::LogError("Can't find loader");
			return 0;
		}

		if (!loader->CanLoad(path))
		{
			Debug::LogError("Can't load resource");
			return 0;
		}

		auto file = SharedPtr<FileStream>(new FileStream());
		if (!file->Open(path, FileMode::Open, FileAccess::Read, FileShare::Read))
		{
			Debug::LogError("Can't open file");
			return 0;
		}

		auto res = loader->Load(*file);
		if (res == 0)
			return 0;

		AddResource(res, path);

		return res;
	}

	//////////////////////////////////////////////////////////////////////////
	SharedPtr<ResourceCache::ResourceGroup> ResourceCache::GetGroup(const HashString& type)
	{
		SharedPtr<ResourceGroup> group;
		if (!_types.TryGetValue(type, &group))
		{
			group = new ResourceGroup();
			_types.Add(type, group);
		}

		return group;
	}
}