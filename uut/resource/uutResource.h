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
		const Path& GetResourcePath() const { return _path; }

	protected:
		String _name;
		Path _path;
	};
}