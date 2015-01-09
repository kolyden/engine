#pragma once
#include "resource/uutResourceLoader.h"

namespace uut
{
	class UUT_API BitmapFontLoader : public ResourceLoader
	{
		OBJECT(BitmapFontLoader)
	public:
		BitmapFontLoader(Context* context);

		virtual const HashString& GetResourceType() const override;
		virtual bool CanLoad(const String& path) const override;
		virtual SharedPtr<Resource> Load(Stream& source) override;
	};
}