#pragma once
#include "core/uutObject.h"

namespace uut
{
	class Resource : public Object
	{
		BASEOBJECT(Resource)
	public:
		Resource(Context* context);

		const String& GetName() const { return _name; }
		const String& GetResourcePath() const { return _resourcePath; }

	private:
		String _name;
		String _resourcePath;

		friend class ResourceCache;
	};
}