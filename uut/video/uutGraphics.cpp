#include "uutGraphics.h"
#include "core/uutContext.h"
#include "uutVideo.h"
#include "uutImage.h"
#include "uutVideoBuffer.h"

namespace uut
{
	static const unsigned gVertCount = 2048;
	static Vertex2 gVert[gVertCount];

	//////////////////////////////////////////////////////////////////////////
    Graphics::Graphics(Context* context)
        : Module(context)
		, _currentCount(0)
		, _currentType(PRIMITIVE_TRIANGLES)
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
		ChangeBufferParam(PRIMITIVE_LINES);

		gVert[_currentCount++] = Vertex2(start, _currentColorUint);
		gVert[_currentCount++] = Vertex2(end, _currentColorUint);
	}

	void Graphics::Flush()
	{
		if (_currentCount == 0)
			return;

		_buffer->UpdateData(0, _currentCount * Vertex2::SIZE, gVert);
		if (_video->BindBuffer(_buffer, Vertex2::SIZE, Vertex2::DECLARE, Vertex2::DECLARE_COUNT))
		{
			_video->SetColor(COLOR_DRAW, _currentColor);
			_video->DrawPrimitives(_currentType, _currentCount, 0);
			_video->UnbindBuffer(_buffer, Vertex2::DECLARE, Vertex2::DECLARE_COUNT);
		}

		_currentCount = 0;
	}

	//////////////////////////////////////////////////////////////////////////
	void Graphics::OnRegister()
	{
		_video = _context->GetModule<Video>();
	}

	void Graphics::OnInit()
	{
		
	}

	void Graphics::ChangeBufferParam(EPrimitiveType type)
	{
		if (!_buffer)
		{
			_buffer = SharedPtr<VideoBuffer>(new VideoBuffer(_context));
			_buffer->Create(BUFFER_VERTEX,
				gVertCount * Vertex2::SIZE, BUFFERFLAG_DYNAMIC);
		}

		if (_currentType == type)
			return;

		Flush();
		_currentType = type;
	}

	void Graphics::TestBufferCount(int count)
	{
		if (_currentCount + count >= gVertCount)
			Flush();
	}
}