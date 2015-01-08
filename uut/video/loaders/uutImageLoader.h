#pragma once
#include "resource/uutResourceLoader.h"

namespace uut
{
	class UUT_API ImageLoader : public ResourceLoader
	{
		OBJECT(ImageLoader)
	public:
		ImageLoader(Context* context);

		virtual const HashString& GetResourceType() const override;
		virtual bool CanLoad(const String& path) const override;
		virtual SharedPtr<Resource> Load(Stream& source) override;
	};
}