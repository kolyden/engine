#include "main.h"
#include "video/uutVideo.h"
#include "resource/uutResourceCache.h"
#include "video/uutTexture.h"
#include "video/uutVideoBuffer.h"
#include "video/uutGraphics.h"
#include "platform/uutTime.h"
#include "io/uutInput.h"

RUNAPP(uut::MyApp);

namespace uut
{
	struct SVertex
	{
		float x, y;
		float u, v;
		uint32_t color;
	};

	static const SDeclareType gVertDecl[] =
	{
		{ 0, USAGE_POSITION, 2, VALUE_FLOAT, 0 },
		{ 0, USAGE_TEXCOORDS, 2, VALUE_FLOAT, offsetof(SVertex, u) },
		{ 0, USAGE_COLOR, 4, VALUE_UBYTE, offsetof(SVertex, color) }
	};

	MyApp::MyApp()
		: _color(0, 0, 0)
		, _pos(100, 100)
		, _paused(false)
		, _size(800, 600)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void MyApp::OnInit()
	{
		_video->SetMode(_size._x, _size._y);
		_video->SetRenderState(RENDERSTATE_DEPTH_TEST, false);
		_video->SetRenderState(RENDERSTATE_LIGHTNING, false);
	}

	void MyApp::OnStart()
	{
		_tex0 = _cache->Load<Texture>("Data/zazaka.png");

		_vbuf = SharedPtr<VideoBuffer>(new VideoBuffer(_context));
		_vbuf->Create(BUFFER_VERTEX, sizeof(SVertex)* 4, BUFFERFLAG_DYNAMIC);

		UpdateBuffer(_pos, Vector2(200.0f));
	}

	void MyApp::OnUpdate()
	{
		_paused = _input->IsKey(KEYCODE_SPACE);
		if (_paused)
			return;

		const Vector2i newPos = _input->GetMousePos();
		if (_input->IsKey(KEYCODE_ESCAPE)) 
			Stop();

		if (_pos != newPos)
		{
			_pos = newPos;
			UpdateBuffer(_pos, Vector2(200.0f));//IntVector2(_pos._x, 600 - _pos._y));
		}

		_color._g += _time->GetDelta();
		while (_color._g > 1)
			_color._g -= 1.0f;
	}

	void MyApp::OnRender()
	{
		_video->SetColor(COLOR_CLEAR, _color);
		_video->Clear(true, false, false);

		_graphics->SetColor(Color::RED);
		_graphics->DrawLine(Vector2(0, 0), _pos);
		_graphics->Flush();

		if (_vbuf && _video->BindBuffer(_vbuf, sizeof(SVertex), gVertDecl, 3))
		{
			_video->SetColor(COLOR_DRAW, Color::WHITE);
			_video->SetRenderState(RENDERSATE_BLEND, true);
			_video->SetBlendFunc(BLEND_SRC_ALPHA, BLEND_ONE_MINUS_SRC_ALPHA);
			_video->BindTexture(_tex0);

			if (_ibuf)
			{
				_video->BindBuffer(_ibuf, 0, 0, 0);
				_video->DrawIndexedPrimitives(PRIMITIVE_TRIANGLES, 6, VALUE_UBYTE);
				_video->UnbindBuffer(_ibuf, 0, 0);
			}
			else _video->DrawPrimitives(PRIMITIVE_TRIANGLE_STRIP, 4, 0);

			_video->UnbindTexture(_tex0);
			_video->SetRenderState(RENDERSATE_BLEND, false);
			_video->UnbindBuffer(_vbuf, gVertDecl, 3);
		}
	}

	void MyApp::UpdateBuffer(const Vector2& pos, const Vector2& size)
	{
		if (_vbuf && (_vbuf->GetSize() > 0))
		{
			const float hw = size._x / 2.0f;
			const float hh = size._y / 2.0f;

			const float x1 = pos._x - hw;
			const float y1 = pos._y - hh;
			const float x2 = pos._x + hw;
			const float y2 = pos._y + hh;

			const float tx1 = 0.0f, ty1 = 0.0f;
			const float tx2 = 1.0f, ty2 = 1.0f;

			const SVertex pVert[] =
			{
				{ x1, y1, tx1, ty1, 0xFFFFFFFF },
				{ x2, y1, tx2, ty1, 0xFFFFFFFF },
				{ x1, y2, tx1, ty2, 0xFFFFFFFF },
				{ x2, y2, tx2, ty2, 0xFFFFFFFF }
			};

			_vbuf->UpdateData(0, _vbuf->GetSize(), pVert);
		}
	}
}