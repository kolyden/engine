#pragma once
#include "core/uutModule.h"
#include "uutVideoDefs.h"
#include "uutColor.h"
#include "math/uutVector2.h"
#include "math/uutRect.h"
#include "math/uutMatrix.h"
#include "container/uutList.h"

struct SDL_Window;

namespace uut
{
    class Image;
    class Texture;
    class VideoBuffer;
    class ImageLoader;

    class UUT_API Video : public Module
    {
        OBJECT(Video);
    public:
        Video(Context* context);
        virtual ~Video();

        void SetWindowTitle(const char* title);
        bool SetMode(int width, int height, bool fullscreen,
			bool borderless, bool resizable, bool vsync,
			bool tripleBuffer, int multiSample);
        bool SetMode(int width, int height);

        bool BeginFrame();
        void EndFrame();

        bool SetRenderTarget(Texture* texture);
        Texture* GetRenderTarget() const;

        bool SetRenderState(ERenderState state, bool flag);
        bool SetBlendFunc(EBlendFunc srcFactor, EBlendFunc dstFactor);
        bool SetPolygonMode(EPolygonMode mode);

        bool BindTexture(Texture* texture, uint8_t index = 0);
		bool UnbindTexture(Texture* texture, uint8_t index = 0);
		
        void SetTransform(ETransformType type, const Matrix4f& mat);
		void SetViewPort(const Recti& rect);

        bool BindBuffer(VideoBuffer* buffer, uint32_t stride, const SDeclareType* declare, uint8_t count);
        void UnbindBuffer(VideoBuffer* buffer, const SDeclareType* declare, uint8_t count);

        bool DrawPrimitives(EPrimitiveType type, uint32_t count, uint32_t offset);
        bool DrawIndexedPrimitives(EPrimitiveType type, unsigned count, EValueType value);

        void SetColor(EColorType type, const Color& color);
        void Clear(bool buffer, bool depth, bool stencil);

        unsigned GetResolutions(List<Vector2i>& arr) const;

    protected:
        SDL_Window* _window;
        void* _glcontext;

        bool _fullscreen;
        bool _borderless;
        bool _resizable;
        bool _vsync;
        bool _tripleBuffer;
        int _multiSample;

		Vector2i _windowSize;
		String _windowTitle;

        SharedPtr<Texture> _renderTarget;

		virtual void OnRegister() override;
		virtual void OnInit() override;

        void Release(bool clearGPUObjects, bool closeWindow);
        void Restore();

        bool OpenWindow(int width, int height, bool resizable, bool borderless);
		bool UpdateViewport();
		void ResetStates();

        static unsigned primitiveToGL(EPrimitiveType primitive);
        static unsigned blendToGL(EBlendFunc blend);
        static unsigned valueToGL(EValueType type);

        static bool CheckGLError(const char* message);

    };
}