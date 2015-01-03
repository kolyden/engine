#pragma once
#include "core/uutObject.h"
#include "io/uutPath.h"

namespace uut
{
	class Resource;
	class Deserializer;

	class UUT_API ResourceLoader : public Object
	{
		BASEOBJECT(ResourceLoader)
	public:
		ResourceLoader(Context* context);

		virtual const HashString& GetResourceType() const = 0;
		virtual bool CanLoad(const Path& path) const = 0;
		virtual SharedPtr<Resource> Load(Deserializer& source) = 0;
	};
}