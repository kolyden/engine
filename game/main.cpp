#include "main.h"
#include "video/uutVideo.h"
#include "resource/uutResourceCache.h"
#include "video/uutTexture.h"
#include "video/uutVideoBuffer.h"
#include "video/uutGraphics.h"
#include "platform/uutTime.h"
#include "io/uutInput.h"
#include "video/uutVertex2.h"
#include "math/uutMatrix.h"
#include "video/uutModel.h"

RUNAPP(uut::MyApp);

namespace uut
{
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
		const Recti rect(Vector2i::ZERO, _size);
		const float aspect = (1.0f * _size.x) / _size.y;

		Matrix4f::ortho2D(_matOrtho, 0.0f, (float)_size.x, (float)_size.y, 0.0f);
		Matrix4f::perspective2(_matPersp, Math::ToRad(60.0f), aspect, 0.0f, 100.0f);

		_video->SetMode(_size.x, _size.y);
		_video->SetViewPort(rect);
		_video->SetRenderState(RENDERSTATE_DEPTH_TEST, false);
		_video->SetRenderState(RENDERSTATE_LIGHTNING, false);
	}

	void MyApp::OnStart()
	{
		_camera = new Camera(_context);

		_tex0 = _cache->Load<Texture>("Data/zazaka.png");
		_model0 = _cache->Load<Model>("Data/stairs.obj");

		_vbuf = SharedPtr<VideoBuffer>(new VideoBuffer(_context));
		_vbuf->Create(BUFFER_VERTEX, Vertex2::SIZE* 4, BUFFERFLAG_DYNAMIC);

		UpdateBuffer(_pos, Vector2f(200.0f));
	}

	void MyApp::OnUpdate()
	{
		_paused = _input->IsKey(KEYCODE_SPACE);
		if (_paused)
			return;

		const Vector2i newPos = _input->GetMousePos();
		if (_input->IsKey(KEYCODE_ESCAPE)) 
			Stop();

		const float speed = 100;

		if (_input->IsKey(KEYCODE_W))
		{
			auto vec = _camera->GetPosition();
			vec.y -= speed * _time->GetDelta();
			_camera->SetPosition(vec);
		}

		if (_input->IsKey(KEYCODE_S))
		{
			auto vec = _camera->GetPosition();
			vec.y += speed * _time->GetDelta();
			_camera->SetPosition(vec);
		}

		if (_input->IsKey(KEYCODE_A))
		{
			auto vec = _camera->GetPosition();
			vec.x -= speed * _time->GetDelta();
			_camera->SetPosition(vec);
		}

		if (_input->IsKey(KEYCODE_D))
		{
			auto vec = _camera->GetPosition();
			vec.x += speed * _time->GetDelta();
			_camera->SetPosition(vec);
		}

		if (_input->IsKey(KEYCODE_Q))
		{
			auto vec = _camera->GetPosition();
			vec.z -= speed * _time->GetDelta();
			_camera->SetPosition(vec);
		}

		if (_input->IsKey(KEYCODE_Z))
		{
			auto vec = _camera->GetPosition();
			vec.z += speed * _time->GetDelta();
			_camera->SetPosition(vec);
		}

		if (_pos != newPos)
		{
			_pos = newPos;
			UpdateBuffer(_pos, Vector2f(200.0f));//IntVector2(_pos._x, 600 - _pos._y));
		}

		_color._g += _time->GetDelta();
		while (_color._g > 1)
			_color._g -= 1.0f;

// 		_camera->UpdatePosition();
	}

	void MyApp::OnRender()
	{
		_video->SetColor(COLOR_CLEAR, Color::BLACK);
		_video->Clear(true, false, false);

		_video->SetTransform(TRANSFORM_PROJECTION, _matPersp);
		_camera->UpdatePosition();
		if (_model0)
		{
			_video->SetColor(COLOR_DRAW, Color::WHITE);
			_model0->Draw();
		}

		_video->SetTransform(TRANSFORM_PROJECTION, _matOrtho);
// 		_video->SetTransform(TRANSFORM_VIEW, Matrix4f::IDENTITY);

		_graphics->SetColor(_color);
		_graphics->DrawLine(Vector2f(0, 0), Vector2f(_pos));
		_graphics->Flush();

		if (_vbuf && _video->BindBuffer(_vbuf, Vertex2::SIZE, Vertex2::DECLARE, Vertex2::DECLARE_COUNT))
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
			_video->UnbindBuffer(_vbuf, Vertex2::DECLARE, Vertex2::DECLARE_COUNT);
		}
	}

	void MyApp::UpdateBuffer(const Vector2i& pos, const Vector2f& size)
	{
		if (_vbuf && (_vbuf->GetSize() > 0))
		{
			const float hw = size.x / 2.0f;
			const float hh = size.y / 2.0f;

			const float x1 = pos.x - hw;
			const float y1 = pos.y - hh;
			const float x2 = pos.x + hw;
			const float y2 = pos.y + hh;

			const float tx1 = 0.0f, ty1 = 0.0f;
			const float tx2 = 1.0f, ty2 = 1.0f;

			const Vertex2 pVert[] =
			{
				Vertex2(Vector2f(x1, y1), Vector2f(tx1, ty1), 0xFFFFFFFF),
				Vertex2(Vector2f(x2, y1), Vector2f(tx2, ty1), 0xFFFFFFFF),
				Vertex2(Vector2f(x1, y2), Vector2f(tx1, ty2), 0xFFFFFFFF),
				Vertex2(Vector2f(x2, y2), Vector2f(tx2, ty2), 0xFFFFFFFF),
			};

			_vbuf->UpdateData(0, _vbuf->GetSize(), pVert);
		}
	}
}