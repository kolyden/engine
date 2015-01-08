#pragma once
#include "resource/uutResourceLoader.h"

namespace uut
{
	class LevelDataLoader : public ResourceLoader
	{
		OBJECT(LevelDataLoader)
	public:
		LevelDataLoader(Context* context);

		virtual const HashString& GetResourceType() const override;
		virtual bool CanLoad(const String& path) const override;
		virtual SharedPtr<Resource> Load(Stream& source) override;
	};
}