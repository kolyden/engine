#pragma once
#include "resource/uutResourceLoader.h"

namespace uut
{
	class UUT_API ModelLoaderOBJ : public ResourceLoader
	{
		OBJECT(ModelLoaderOBJ)
	public:
		ModelLoaderOBJ(Context* context);

		virtual const HashString& GetResourceType() const override;
		virtual bool CanLoad(const String& path) const override;
		virtual SharedPtr<Resource> Load(Stream& source) override;
	};
}