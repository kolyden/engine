#include "uutImageLoader.h"
#include "uutImage.h"
#include "io/uutDeserializer.h"
#include "SDL_IMAGE/SDL_image.h"

namespace uut
{
	ImageLoader::ImageLoader(Context* context)
		: ResourceLoader(context)
	{
	}

	const HashString& ImageLoader::GetResourceType() const
	{
		return Image::GetTypeStatic();
	}

	bool ImageLoader::CanLoad(const Path& path) const
	{
		return true;
	}

	Resource* ImageLoader::Load(Deserializer& source)
	{
		auto rwops = CreatReadRWops(source);
		auto surface = IMG_Load_RW(rwops, 1);
		if (surface == 0)
			return 0;

		return new Image(_context, surface);
	}

}