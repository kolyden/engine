#pragma once
#include "resource/uutResourceLoader.h"

namespace uut
{
	class LevelLoader : public ResourceLoader
	{
		OBJECT(LevelLoader)
	public:
		LevelLoader(Context* context);

		virtual const HashString& GetResourceType() const override;
		virtual bool CanLoad(const String& path) const override;
		virtual SharedPtr<Resource> Load(Stream& source) override;
	};
}