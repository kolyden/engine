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
		virtual bool CanLoad(const Path& path) const override;
		virtual Resource* Load(Deserializer& source) override;
	};
}