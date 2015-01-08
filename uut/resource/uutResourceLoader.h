#pragma once
#include "core/uutObject.h"

namespace uut
{
	class Resource;
	class Stream;

	class UUT_API ResourceLoader : public Object
	{
		BASEOBJECT(ResourceLoader)
	public:
		ResourceLoader(Context* context);

		virtual const HashString& GetResourceType() const = 0;
		virtual bool CanLoad(const String& path) const = 0;
		virtual SharedPtr<Resource> Load(Stream& source) = 0;
	};
}