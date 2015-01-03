#pragma once
#include "core/uutObject.h"
#include "io/uutPath.h"

namespace uut
{
	class Resource : public Object
	{
		BASEOBJECT(Resource)
	public:
		Resource(Context* context);

		const String& GetName() const { return _name; }
		const Path& GetResourcePath() const { return _resourcePath; }

	private:
		String _name;
		Path _resourcePath;

		friend class ResourceCache;
	};
}