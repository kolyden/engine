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

	protected:
		String _name;
	};
}