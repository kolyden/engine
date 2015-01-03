#pragma once
#include "resource/uutResourceLoader.h"

namespace uut
{
	class UUT_API TextureLoader : public ResourceLoader
	{
		OBJECT(ResourceLoader)
	public:
		TextureLoader(Context* context);

		virtual const HashString& GetResourceType() const override;
		virtual bool CanLoad(const Path& path) const override;
		virtual SharedPtr<Resource> Load(Deserializer& source) override;
	};
}