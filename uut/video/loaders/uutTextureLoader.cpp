#include "uutTextureLoader.h"
#include "video/uutTexture.h"
#include "video/uutImage.h"
#include "io/uutDeserializer.h"
#include "SDL_IMAGE/SDL_image.h"

namespace uut
{
	TextureLoader::TextureLoader(Context* context)
		: ResourceLoader(context)
	{

	}

	//////////////////////////////////////////////////////////////////////////
	const HashString& TextureLoader::GetResourceType() const
	{
		return Texture::GetTypeStatic();
	}

	bool TextureLoader::CanLoad(const Path& path) const
	{
		return true;
	}

	SharedPtr<Resource> TextureLoader::Load(Deserializer& source)
	{
		auto rwops = CreatReadRWops(source);
		auto surface = IMG_Load_RW(rwops, 0);
		if (surface == 0)
			return SharedPtr<Resource>::EMPTY;

		auto tex = SharedPtr<Texture>(new Texture(_context));
		if (!tex->CreateFromSurface(surface))
			return SharedPtr<Resource>::EMPTY;

		return DynamicCast<Resource>(tex);
	}

}