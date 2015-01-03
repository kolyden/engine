#pragma once
#include "uutVideoDefs.h"
#include "Resource/uutResource.h"
#include "uutVideoObject.h"
#include "math/uutVector2.h"

namespace uut
{
    class Image;

    class UUT_API Texture : public Resource, public VideoObject
    {
        OBJECT(Texture);
    public:
        Texture(Context* context);
        virtual ~Texture();

		bool Create(const Vector2i& size, ETextureType usage = TEXTURE_STATIC);
        void Clear();

        bool Load(SharedPtr<Image> image);

		const Vector2i& GetSize() const { return _size; }
        ETextureType GetUsage() const { return _usage; }
//         EImageFormat GetFormat() const { return _format; }

    protected:
        unsigned _data;
		unsigned _type;
		Vector2i _size;
        ETextureType _usage;

        friend class Video;
    };
}