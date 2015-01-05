#pragma once
#include "core/uutModule.h"
#include "math/uutRect.h"
#include "uutVideoDefs.h"
#include "uutColor.h"
#include "uutVertex3.h"

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
		void DrawLine(const Vector3f& start, const Vector3f& end);
		void DrawTexture(Texture* tex, const Rectf& rect);

		void DrawTriangle(Texture* tex, const Vertex3& v0, const Vertex3& v1, const Vertex3& v2);
		void DrawQuad(Texture* tex, const Vertex3& v0, const Vertex3& v1, const Vertex3& v2, const Vertex3& v3);

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
		unsigned _vertexMax;
		uint8_t* _data;

		SharedPtr<Texture> _texture;

		virtual void OnRegister() override;
		virtual void OnInit() override;

		void ChangeBufferParam(EPrimitiveType type, VertexType vert);
		void SetTexture(Texture* texture);
		void TestBufferCount(int count);
    };
}