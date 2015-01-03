#include "uutTexture.h"
#include "core/uutContext.h"
#include "uutVideo.h"
#include "uutImage.h"

namespace uut
{
    Texture::Texture(Context* context)
        : Resource(context)
        , VideoObject(_context->GetModule<Video>())
        , _data(0)
		, _type(GL_TEXTURE_2D)
        , _size(0, 0)
        , _usage(TEXTURE_STATIC)
    {
    }

    Texture::~Texture()
    {
        Clear();
    }

	bool Texture::Create(const Vector2i& size, ETextureType usage)
    {
        Clear();

        if ((size._x <= 0) || (size._y <= 0))
            return false;

        int access = 0;
        switch (usage)
        {
        case TEXTURE_STATIC: access = SDL_TEXTUREACCESS_STATIC; break;
        case TEXTURE_DYNAMIC: access = SDL_TEXTUREACCESS_STREAMING; break;
        case TEXTURE_TARGET: access = SDL_TEXTUREACCESS_TARGET; break;
        }

        glGenTextures(1, &_data);
        glBindTexture(GL_TEXTURE_2D, _data);

        // Set-up texture properties.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Loads image data into OpenGL.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size._x, size._y, 0,
            GL_RGB, GL_UNSIGNED_BYTE, 0);

        glBindTexture(GL_TEXTURE_2D, 0);

        if (!CheckGLError("Error creating texture into OpenGL."))
            return false;

        _size = size;
        _usage = usage;

        return true;
    }

    void Texture::Clear()
    {
        if (!_data)
            return;

        ::glDeleteTextures(1, &_data);
        _data = 0;
    }

    bool Texture::Create(SharedPtr<Image> image)
    {
        if (!image)
            return false;

		return CreateFromSurface(image->_data);
    }

	//////////////////////////////////////////////////////////////////////////
	bool Texture::CreateFromSurface(SDL_Surface* surface)
	{
		if (surface == 0)
			return false;

		SDL_Surface* newSurface = 0;
		bool freeSurface = false;

		GLenum format;

		switch (surface->format->format)
		{
		case SDL_PIXELFORMAT_RGBA8888:
			format = GL_RGBA;
			break;

		case SDL_PIXELFORMAT_RGB888:
		case SDL_PIXELFORMAT_RGB24:
			format = GL_RGB;
			break;

		default:
			switch (surface->format->BitsPerPixel)
			{
			case 32:
				newSurface = SDL_ConvertSurfaceFormat(surface,
					SDL_PIXELFORMAT_RGBA8888, 0);
				format = GL_RGBA;
				break;

			case 24:
				newSurface = SDL_ConvertSurfaceFormat(surface,
					SDL_PIXELFORMAT_RGB888, 0);
				format = GL_RGB;
				break;
			}
			if (!surface && !newSurface)
				return false;

			surface = newSurface;
			freeSurface = true;
			break;
		}

		if ((SDL_LockSurface(surface) != 0) || !surface->pixels)
		{
			if (freeSurface)
				SDL_FreeSurface(surface);
			return false;
		}
		void* bits = surface->pixels;

		glGenTextures(1, &_data);
		if (!CheckGLError("Error creating texture into OpenGL."))
			return false;

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _data);
		if (!CheckGLError("Error creating texture into OpenGL."))
			return false;

		// Set-up texture properties.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Loads image data into OpenGL.
		glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0,
			format, GL_UNSIGNED_BYTE, bits);

		SDL_UnlockSurface(surface);
		if (freeSurface)
			SDL_FreeSurface(surface);

		if (!CheckGLError("Error creating texture into OpenGL."))
			return false;

		glBindTexture(GL_TEXTURE_2D, 0);

		_size = Vector2i(surface->w, surface->h);
		_usage = TEXTURE_STATIC;

		return true;
	}

}