#pragma once
#include "uutVideoDefs.h"
#include "resource/uutResource.h"
#include "math/uutVector2.h"
#include "uutColor.h"

namespace uut
{
    class UUT_API Image : public Resource
    {
        OBJECT(Image);
    public:
        Image(Context* context);
        Image(Context* context, SDL_Surface* surface);
        virtual ~Image();

		bool Create(const Vector2i& size);
        void Clear();

        bool Fill(const Color& color);

		bool CopyTo(Image* dst, const Vector2i& dstPos);

        void* Lock();
        void Unlock();

		const Vector2i& GetSize() const { return _size; }
        const unsigned GetPitch() const { return _pitch; }

    protected:
        SDL_Surface* _data;
		Vector2i _size;
        unsigned _pitch;

        uint32_t ColorConvert(const Color& color) const;

        friend class Video;
        friend class Texture;
        friend class Graphics;
    };
}