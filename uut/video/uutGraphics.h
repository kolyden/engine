#pragma once
#include "core/uutModule.h"
#include "math/uutRect.h"
#include "uutVertex.h"
#include "uutVideoDefs.h"

namespace uut
{
    class Image;
	class Video;
	class VideoBuffer;

    class UUT_API Graphics : public Module
    {
        OBJECT(Graphics);
    public:
        Graphics(Context* context);

		void SetColor(const Color& color);

		void DrawLine(const Vector2& start, const Vector2& end);

		void Flush();

	protected:
		WeakPtr<Video> _video;
		SharedPtr<VideoBuffer> _buffer;
		unsigned _currentCount;
		Color _currentColor;
		uint32_t _currentColorUint;
		EPrimitiveType _currentType;

		virtual void OnRegister() override;
		virtual void OnInit() override;

		void ChangeBufferParam(EPrimitiveType type);
		void TestBufferCount(int count);
    };
}