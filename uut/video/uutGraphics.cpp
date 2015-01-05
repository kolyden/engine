#include "uutGraphics.h"
#include "core/uutContext.h"
#include "uutVideo.h"
#include "uutImage.h"
#include "uutTexture.h"
#include "uutVideoBuffer.h"
#include "uutVertex2.h"
#include "uutVertex3.h"

namespace uut
{
    Graphics::Graphics(Context* context)
        : Module(context)
		, _currentCount(0)
		, _currentType(PRIMITIVE_TRIANGLES)
		, _vertexType(VertexType::None)
		, _vertexMax(0)
		, _data(0)
    {
		SetColor(Color::WHITE);
    }

	void Graphics::SetColor(const Color& color)
	{
		_currentColor = color;
		_currentColorUint = _currentColor.ToUint();
	}

	void Graphics::DrawLine(const Vector2f& start, const Vector2f& end)
	{
		ChangeBufferParam(PRIMITIVE_LINES, VertexType::V2D);
		SetTexture(0);

		auto verts = (Vertex2*)_data;
		verts[_currentCount++] = Vertex2(start, _currentColorUint);
		verts[_currentCount++] = Vertex2(end, _currentColorUint);
	}

	void Graphics::DrawTexture(Texture* texture, const Rectf& rect)
	{
		ChangeBufferParam(PRIMITIVE_TRIANGLES, VertexType::V2D);
		SetTexture(texture);

		const float x1 = rect.pos.x;
		const float y1 = rect.pos.y;
		const float x2 = x1 + rect.size.x;
		const float y2 = y1 + rect.size.y;

		const float tx1 = 0.0f, ty1 = 0.0f;
		const float tx2 = 1.0f, ty2 = 1.0f;

		auto verts = (Vertex2*)_data;
		verts[_currentCount++] = Vertex2(Vector2f(x1, y1), Vector2f(tx1, ty1), _currentColorUint);
		verts[_currentCount++] = Vertex2(Vector2f(x2, y1), Vector2f(tx2, ty1), _currentColorUint);
		verts[_currentCount++] = Vertex2(Vector2f(x1, y2), Vector2f(tx1, ty2), _currentColorUint);

		verts[_currentCount++] = Vertex2(Vector2f(x2, y1), Vector2f(tx2, ty1), _currentColorUint);
		verts[_currentCount++] = Vertex2(Vector2f(x2, y2), Vector2f(tx2, ty2), _currentColorUint);
		verts[_currentCount++] = Vertex2(Vector2f(x1, y2), Vector2f(tx1, ty2), _currentColorUint);
	}

	void Graphics::Flush()
	{
		if (_currentCount == 0)
			return;

		_buffer->UpdateData(0, _currentCount * Vertex2::DECLARE.size, _data);
		if (_video->BindBuffer(_buffer, Vertex2::DECLARE.size,
			Vertex2::DECLARE.types, Vertex2::DECLARE.count))
		{
			_video->SetColor(COLOR_DRAW, _currentColor);
			_video->DrawPrimitives(_currentType, _currentCount, 0);
			_video->UnbindBuffer(_buffer, Vertex2::DECLARE.types, Vertex2::DECLARE.count);
		}

		_currentCount = 0;
	}

	void Graphics::ResetStates()
	{
		Flush();

		_texture = 0;
		_vertexType = VertexType::None;
	}

	//////////////////////////////////////////////////////////////////////////
	void Graphics::OnRegister()
	{
		_video = _context->GetModule<Video>();
	}

	void Graphics::OnInit()
	{
		
	}

	void Graphics::ChangeBufferParam(EPrimitiveType type, VertexType vert)
	{
		if (!_buffer)
		{
			_buffer = SharedPtr<VideoBuffer>(new VideoBuffer(_context));
			_buffer->Create(BUFFER_VERTEX, BUFFER_SIZE, BUFFERFLAG_DYNAMIC);
			_data = new uint8_t[BUFFER_SIZE];
		}

		if (_currentType == type)
			return;

		Flush();
		_currentType = type;
		_vertexType = vert;
		switch (_vertexType)
		{
		case VertexType::V2D:
			_vertexMax = BUFFER_SIZE / Vertex2::DECLARE.size;
			break;

		case VertexType::V3D:
			_vertexMax = BUFFER_SIZE / Vertex3::DECLARE.size;
			break;
		}
	}

	void Graphics::SetTexture(Texture* texture)
	{
		if (_texture == texture)
			return;

		Flush();
		_texture = texture;
		_video->BindTexture(_texture);
	}

	void Graphics::TestBufferCount(int count)
	{
		if (_currentCount + count >= _vertexMax)
			Flush();
	}
}