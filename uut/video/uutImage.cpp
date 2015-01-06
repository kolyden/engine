#include "uutImage.h"

namespace uut
{
    Image::Image(Context* context)
        : Resource(context)
        , _data(0)
        , _size(0, 0)
        , _pitch(0)
    {
    }

    Image::Image(Context* context, SDL_Surface* surface)
        : Resource(context)
        , _data(surface)
        , _size(0, 0)
        , _pitch(0)
    {
        if (_data)
        {
            _size.x = _data->w;
            _size.y = _data->h;
            _pitch = _data->pitch;
        }
    }

    Image::~Image()
    {
        Clear();
    }

	bool Image::Create(const Vector2i& size)
    {
        Clear();

        if ((size.x <= 0) || (size.y <= 0))
            return false;

        _data = SDL_CreateRGBSurface(0, size.x, size.y,
            32, 0, 0, 0, 0);

        if (!_data)
            return false;

        _size = size;
        _pitch = _data->pitch;

        return true;
    }

    void Image::Clear()
    {
        if (!_data)
            return;

        SDL_FreeSurface(_data);
        _data = 0;
		_size = Vector2i::ZERO;
    }

    bool Image::Fill(const Color& color)
    {
        if (!_data)
            return false;

        SDL_FillRect(_data, 0, ColorConvert(color));

        return true;
    }

	bool Image::CopyTo(Image* dst, const Vector2i& dstPos)
    {
        if (!_data || !dst || !dst->_data)
            return false;

        SDL_Rect dstrect;
        dstrect.x = dstPos.x;
        dstrect.y = dstPos.y;
        dstrect.w = _size.x;
        dstrect.h = _size.y;
        SDL_BlitSurface(_data, 0, dst->_data, &dstrect);

        return true;
    }

    void* Image::Lock()
    {
        if (!_data)
            return 0;

        SDL_LockSurface(_data);
        return _data->pixels;
    }

    void Image::Unlock()
    {
        if (!_data)
            return;

        SDL_UnlockSurface(_data);
    }

    //////////////////////////////////////////////////////////////////////////
    uint32_t Image::ColorConvert(const Color& color) const
    {
        if (!_data)
            return 0;

        uint8_t r, g, b, a;
        color.Convert(&r, &g, &b, &a);
        return SDL_MapRGBA(_data->format, r, g, b, a);
    }

}