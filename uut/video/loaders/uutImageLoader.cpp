#include "uutImageLoader.h"
#include "video/uutImage.h"
#include "io/uutStream.h"
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

	bool ImageLoader::CanLoad(const String& path) const
	{
		return true;
	}

	SharedPtr<Resource> ImageLoader::Load(Stream& source)
	{
		auto rwops = Stream::CreatReadRWops(&source);
		auto surface = IMG_Load_RW(rwops, 1);
		if (surface == 0)
			return SharedPtr<Resource>::EMPTY;

		return SharedPtr<Resource>(new Image(_context, surface));
	}

}