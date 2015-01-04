#include "uutVideo.h"
#include "core/uutContext.h"
#include "core/uutDebug.h"
#include "resource/uutResourceCache.h"
#include "uutImage.h"
#include "uutTexture.h"
#include "uutVideoBuffer.h"
#include "loaders/uutImageLoader.h"
#include "loaders/uutTextureLoader.h"
#include "loaders/uutModelLoaderOBJ.h"
#include "SDL_IMAGE/SDL_image.h"

namespace uut
{
    Video::Video(Context* context)
        : Module(context)
        , _window(0)
        , _glcontext(0)
        , _fullscreen(false)
        , _borderless(false)
        , _resizable(false)
        , _vsync(false)
        , _tripleBuffer(false)
        , _multiSample(1)
        , _windowTitle("Title")
    {
    }

    Video::~Video()
    {
        if (_window)
        {
            SDL_DestroyWindow(_window);
            _window = 0;
        }
    }

    void Video::SetWindowTitle(const char* title)
    {
        _windowTitle = title ? title : "";
        if (_window)
            SDL_SetWindowTitle(_window, _windowTitle.GetData());
    }

    bool Video::SetMode(int width, int height, bool fullscreen,
        bool borderless, bool resizable, bool vsync,
        bool tripleBuffer, int multiSample)
    {
        bool maximize = false;

        if (fullscreen || borderless)
            resizable = false;

        multiSample = Math::Clamp(multiSample, 1, 16);

        if (_window && (_fullscreen == fullscreen) && 
            (_borderless == borderless) && (_resizable == resizable) &&
            (_tripleBuffer == tripleBuffer) && (multiSample == multiSample))
        {
            if (_vsync == vsync)
                return true;

            SDL_GL_SetSwapInterval(vsync ? 1 : 0);
            _vsync = vsync;
            return true;
        }

        if ((width <= 0) || (height <= 0))
        {
            if (fullscreen || borderless)
            {
                SDL_DisplayMode mode;
                SDL_GetDesktopDisplayMode(0, &mode);
                width = mode.w;
                height = mode.h;
            }
            else
            {
                maximize = resizable;
                width = 1024;
                height = 768;
            }
        }

#if !defined(ANDROID) && !defined(IOS) && !defined(RASPI)
        if (fullscreen)
        {
            List<Vector2i> resolutions;
            GetResolutions(resolutions);
            fullscreen = false;
            for (int i = 0; i < resolutions.Count(); ++i)
            {
                if ((width == resolutions[i].x) && (height == resolutions[i].y))
                {
                    fullscreen = true;
                    break;
                }
            }
        }
#endif

        if (!_glcontext)
        {
            Release(false, true);
#ifdef IOS
            SDL_SetHint(SDL_HINT_ORIENTATIONS, "LandscapeLeft LandscapeRight");

            // On iOS window needs to be resizable to handle orientation changes properly
            resizable = true;
#endif

            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
#ifndef GL_ES_VERSION_2_0
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);
            SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
#endif
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

            if (multiSample > 1)
            {
                SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
                SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, multiSample);
            }
            else
            {
                SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
                SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
            }

            int x = fullscreen ? 0 : SDL_WINDOWPOS_UNDEFINED;
            int y = fullscreen ? 0 : SDL_WINDOWPOS_UNDEFINED;

            unsigned flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
            if (fullscreen)
                flags |= SDL_WINDOW_FULLSCREEN;
            if (resizable)
                flags |= SDL_WINDOW_RESIZABLE;
            if (borderless)
                flags |= SDL_WINDOW_BORDERLESS;

            for (;;)
            {
                _window = SDL_CreateWindow(_windowTitle.GetData(), x, y, width, height, flags);

                if (_window)
                    break;

                if (multiSample > 1)
                {
                    // If failed with multisampling, retry first without
                    multiSample = 1;
                    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
                    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
                }
                else
                {
                    Debug::LogError("Could not open window");
                    return false;
                }
            }

//             if (maximize)
//                 Maximize();

            Restore();

            if (!_glcontext)
            {
				Debug::LogError("Could not create OpenGL context");
                return false;
            }

            GLenum err = glewInit();
            if (GLEW_OK != err)
            {
				Debug::LogError("Cannot initialize OpenGL");
                Release(true, true);
                return false;
            }
        }

        SDL_GL_SetSwapInterval(vsync ? 1 : 0);

        _fullscreen = fullscreen;
        _resizable = resizable;
        _borderless = borderless;
        _vsync = vsync;
        _tripleBuffer = tripleBuffer;
        _multiSample = multiSample;

        SDL_GetWindowSize(_window, &_windowSize.x, &_windowSize.y);

        Clear(true, true, true);
        SDL_GL_SwapWindow(_window);

		UpdateViewport();
		ResetStates();

        return true;
    }

    bool Video::SetMode(int width, int height)
    {
        return SetMode(width, height, _fullscreen, _borderless,
            _resizable, _vsync, _tripleBuffer, _multiSample);
    }

    bool Video::BeginFrame()
    {
        return _glcontext != 0;
    }

    void Video::EndFrame()
    {
        SDL_GL_SwapWindow(_window);
    }

    bool Video::SetRenderTarget(Texture* texture)
    {
        return false;

//         if (!_renderer || !SDL_RenderTargetSupported(_renderer))
//             return false;
// 
//         if (texture && (texture->GetUsage() != TEXTURE_TARGET))
//             return false;
// 
//         if (_renderTarget != texture)
//         {
//             _renderTarget = texture;
// 
//             SDL_Texture* tex = _renderTarget ? _renderTarget->_data : 0;
//             return (SDL_SetRenderTarget(_renderer, tex) == 0);
//         }
    }

    Texture* Video::GetRenderTarget() const
    {
        return _renderTarget;
    }

    bool Video::SetRenderState(ERenderState state, bool flag)
    {
        static const GLenum convert[] = {GL_BLEND, GL_ALPHA_TEST, GL_DEPTH_TEST, GL_LIGHTING};

        if (flag) glEnable(convert[state]);
        else glDisable(convert[state]);

        return true;
    }

    bool Video::SetBlendFunc(EBlendFunc srcFactor, EBlendFunc dstFactor)
    {
        glBlendFunc(blendToGL(srcFactor), blendToGL(dstFactor));

        return false;
    }

    bool Video::SetPolygonMode(EPolygonMode mode)
    {
        static const GLenum convert[] = {GL_POINT, GL_LINE, GL_FILL};

        ::glPolygonMode(GL_FRONT_AND_BACK, convert[mode]);
        return true;
    }

    bool Video::BindTexture(Texture* texture, uint8_t index)
    {
        static const GLenum index2enum[] = {GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3, GL_TEXTURE4, GL_TEXTURE5};

        if (!texture || (texture->_data == 0))
            return false;

		glEnable(texture->_type);
        glActiveTexture(index2enum[index]);
        if (!CheckGLError("Error creating texture into OpenGL."))
            return false;

        glBindTexture(texture->_type, texture->_data);
        if (!CheckGLError("Error creating texture into OpenGL."))
            return false;

        return true;
    }

	bool Video::UnbindTexture(Texture* texture, uint8_t index)
	{
		static const GLenum index2enum[] = {GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, GL_TEXTURE3, GL_TEXTURE4, GL_TEXTURE5};

		if (!texture || (texture->_data == 0))
			return false;

		glDisable(texture->_type);
		glActiveTexture(index2enum[index]);
		if (!CheckGLError("Error creating texture into OpenGL."))
			return false;

		glBindTexture(texture->_type, 0);
		if (!CheckGLError("Error creating texture into OpenGL."))
			return false;

		return true;

	}

	void Video::SetTransform(ETransformType type, const Matrix4f& mat)
    {
        switch (type)
        {
        case TRANSFORM_VIEW: ::glMatrixMode(GL_MODELVIEW); break;
        case TRANSFORM_PROJECTION: ::glMatrixMode(GL_PROJECTION); break;

        default:
            return;
            break;
        }

        ::glLoadMatrixf(mat.get_value());
    }
	
	void Video::SetViewPort(const Recti& rect)
	{
		glViewport(
			rect.pos.x,
			rect.pos.y,
			rect.size.x,
			rect.size.y);
	}

    bool Video::BindBuffer(VideoBuffer* buffer, uint32_t stride, const SDeclareType* _declare, uint8_t count)
    {
        if (!buffer || !buffer->Bind())
            return false;

        if (buffer->GetDataType() == BUFFER_INDEX)
            return true;

        for (uint8_t i = 0; i < count; i++)
        {
            const SDeclareType& declare = _declare[i];
            const GLenum type = valueToGL(declare.value);

            switch (declare.usage)
            {
            case USAGE_POSITION:
                glVertexPointer(declare.count, type, stride, (void*)declare.offset);
                CheckGLError("glVertexPointer");
                glEnableClientState(GL_VERTEX_ARRAY);
                CheckGLError("glEnableClientState GL_TEXTURE_COORD_ARRAY");
                break;

            case USAGE_COLOR:
                glColorPointer(declare.count, type, stride, (void*)declare.offset);
                CheckGLError("glColorPointer");
                glEnableClientState(GL_COLOR_ARRAY);
                CheckGLError("glEnableClientState GL_TEXTURE_COORD_ARRAY");
                break;

            case USAGE_TEXCOORDS:
                glTexCoordPointer(declare.count, type, stride, (void*)declare.offset);
                CheckGLError("glTexCoordPointer");
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                CheckGLError("glEnableClientState GL_TEXTURE_COORD_ARRAY");
                break;
            }
        }

        return true;
    }

    void Video::UnbindBuffer(VideoBuffer* buffer, const SDeclareType* declare, uint8_t count)
    {
        if (!buffer)
            return;

        buffer->Unbind();

        if (buffer->GetDataType() == BUFFER_INDEX)
            return;

        for (uint8_t i = 0; i < count; i++)
        {
            switch (declare[i].usage)
            {
            case USAGE_POSITION: ::glDisableClientState(GL_VERTEX_ARRAY); break;
            case USAGE_COLOR: ::glDisableClientState(GL_COLOR_ARRAY); break;
            case USAGE_TEXCOORDS: ::glDisableClientState(GL_TEXTURE_COORD_ARRAY); break;
            }
        }
    }

    bool Video::DrawPrimitives(EPrimitiveType type, uint32_t count, uint32_t offset)
    {
        ::glDrawArrays(primitiveToGL(type), offset, count);
        return CheckGLError("drawPrimitives");
    }

    bool Video::DrawIndexedPrimitives(EPrimitiveType type, unsigned count, EValueType value)
    {
        glDrawElements(primitiveToGL(type), count, valueToGL(value), 0);
        return CheckGLError("drawIndexedPrimitives");
    }

    void Video::SetColor(EColorType type, const Color& color)
    {
        switch (type)
        {
        case COLOR_CLEAR:
            glClearColor(color._r, color._g, color._b, color._a);
            break;

        case COLOR_DRAW:
            glColor4f(color._r, color._g, color._b, color._a);
            break;
        }
    }

    void Video::Clear(bool buffer, bool depth, bool stencil)
    {
        GLbitfield flags = 0;

        if (buffer) flags |= GL_COLOR_BUFFER_BIT;
        if (depth) flags |= GL_DEPTH_BUFFER_BIT;
        if (stencil) flags |= GL_STENCIL_BUFFER_BIT;

        glClear(flags);
    }

	unsigned Video::GetResolutions(List<Vector2i>& arr) const
    {
        const unsigned count = SDL_GetNumDisplayModes(0);
        for (unsigned i = 0; i < count; ++i)
        {
            SDL_DisplayMode mode;
            SDL_GetDisplayMode(0, i, &mode);

			arr.Add(Vector2i(mode.w, mode.h));
        }

        return count;
    }

    //////////////////////////////////////////////////////////////////////////
	void Video::OnRegister()
	{
		_context->RegisterFactory<Image>();
		_context->RegisterFactory<Texture>();
		_context->RegisterFactory<VideoBuffer>();
	}

	void Video::OnInit()
	{
		auto cache = _context->GetModule<ResourceCache>();
		cache->AddLoader(new ImageLoader(_context));
		cache->AddLoader(new TextureLoader(_context));
		cache->AddLoader(new ModelLoaderOBJ(_context));

		if (!IMG_Init(IMG_INIT_PNG))
			Debug::LogError("SDL Image init failed");
	}

    void Video::Release(bool clearGPUObjects, bool closeWindow)
    {
        if (!_window)
            return;

        if (_glcontext)
        {
            // Do not log this message if we are exiting
            if (!clearGPUObjects)
                Debug::LogError("OpenGL context lost");

            SDL_GL_DeleteContext(_glcontext);
            _glcontext = 0;
        }

        if (closeWindow)
        {
            SDL_ShowCursor(SDL_TRUE);
            SDL_DestroyWindow(_window);
            _window = 0;
        }
    }

    void Video::Restore()
    {
        if (!_window)
            return;

#ifdef ANDROID
        // On Android the context may be lost behind the scenes as the application is minimized
        if (impl_->context_ && !SDL_GL_GetCurrentContext())
        {
            impl_->context_ = 0;
            // Mark GPU objects lost without a current context. In this case they just mark their internal state lost
            // but do not perform OpenGL commands to delete the GL objects
            Release(false, false);
        }
#endif

        // Ensure first that the context exists
        if (!_glcontext)
        {
            _glcontext = SDL_GL_CreateContext(_window);
#ifdef IOS
            glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)&impl_->systemFbo_);
#endif
        }
    }

    bool Video::OpenWindow(int width, int height,
        bool resizable, bool borderless)
    {
        Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
        if (resizable)
            flags |= SDL_WINDOW_RESIZABLE;
        if (borderless)
            flags |= SDL_WINDOW_BORDERLESS;

        _window = SDL_CreateWindow(_windowTitle.GetData(),
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            width, height, flags);

        if (!_window)
            return false;

        return true;
    }

	bool Video::UpdateViewport()
	{
// 		glViewport(0, 0,
// 			_windowSize._x,
// 			_windowSize._y);
// 
// 		glMatrixMode(GL_PROJECTION);
// 		glLoadIdentity();
// 		glOrtho((GLdouble)0,
// 				(GLdouble)_windowSize._x,
// 				(GLdouble)_windowSize._y,
// 				(GLdouble)0,
// 				0.0, 1.0);
// 
// 		return CheckGLError("Update Viewport");

		return true;
	}

	void Video::ResetStates()
	{
		glEnable(GL_TEXTURE_2D);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

    unsigned Video::primitiveToGL(EPrimitiveType primitive)
    {
        static const GLenum convert[] = {GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN};
        return convert[primitive];
    }

    unsigned Video::blendToGL(EBlendFunc blend)
    {
        static const GLenum convert[] = {
            GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
            GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA_SATURATE
        };

        return convert[blend];
    }

    unsigned Video::valueToGL(EValueType type)
    {
        static const GLenum convert[] = {
            GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT,
            GL_FLOAT, GL_FIXED
        };

        return convert[type];
    }

    bool Video::CheckGLError(const char* message)
    {
        const GLenum error = ::glGetError();
        switch (error)
        {
        case GL_NO_ERROR:
            return true;
            break;

		case GL_INVALID_ENUM: Debug::LogError("%s - Invalid Enum", message); break;
		case GL_INVALID_VALUE: Debug::LogError("%s - Invalid Value", message); break;
		case GL_INVALID_OPERATION: Debug::LogError("%s - Invalid Operation", message); break;
		case GL_OUT_OF_MEMORY: Debug::LogError("%s - Out Of Memory", message); break;

        default:
            break;
        }

        return false;
    }

}