#pragma once
#include "core/uutModule.h"
#include "math/uutRect.h"
#include "uutVideoDefs.h"
#include "uutColor.h"

namespace uut
{
    class Image;
	class Texture;
	class Video;
	class VideoBuffer;

    class UUT_API Graphics : public Module
    {
        OBJECT(Graphics);
    public:
        Graphics(Context* context);

		void SetColor(const Color& color);

		void DrawLine(const Vector2f& start, const Vector2f& end);
		void DrawTexture(Texture* texture, const Rectf& rect);

		void Flush();
		void ResetStates();

	protected:
		const int BUFFER_SIZE = 1024 * 10;
		enum class VertexType
		{
			None,
			V2D,
			V3D,
		};

		WeakPtr<Video> _video;
		SharedPtr<VideoBuffer> _buffer;
		unsigned _currentCount;
		Color _currentColor;
		uint32_t _currentColorUint;
		EPrimitiveType _currentType;

		VertexType _vertexType;
		int _vertexMax;
		uint8_t* _data;

		SharedPtr<Texture> _texture;

		virtual void OnRegister() override;
		virtual void OnInit() override;

		void ChangeBufferParam(EPrimitiveType type, VertexType vert);
		void SetTexture(Texture* texture);
		void TestBufferCount(int count);
    };
}