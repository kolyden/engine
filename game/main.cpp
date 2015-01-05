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

	void MyApp::OnInit()
	{
		const Recti rect(Vector2i::ZERO, _size);
		const float aspect = (1.0f * _size.x) / _size.y;

		Matrix4f::ortho2D(_matOrtho, 0.0f, (float)_size.x, (float)_size.y, 0.0f);
		Matrix4f::perspective2(_matPersp, Math::ToRad(60.0f), aspect, 0.0f, 100.0f);

		_video->SetMode(_size.x, _size.y);
		_video->SetViewPort(rect);
		_video->SetRenderState(RENDERSTATE_LIGHTNING, false);
		_video->SetRenderState(RENDERSTATE_DEPTH_TEST, false);
	}

	void MyApp::OnStart()
	{
		_camera = new Camera(_context);

		_tex0 = _cache->Load<Texture>("Data/zazaka.png");
		_model0 = _cache->Load<Model>("Data/stairs.obj");
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
			_pos = newPos;

		_color._g += _time->GetDelta();
		while (_color._g > 1)
			_color._g -= 1.0f;
	}

	void MyApp::OnRender()
	{
		_video->SetColor(COLOR_CLEAR, Color::BLACK);
		_video->Clear(true, true, false);

		//////////////////////////////////////////////////////////////////////////
		_video->SetTransform(TRANSFORM_PROJECTION, _matOrtho);
// 		_camera->UpdatePosition();

		const int count = 200;
		const float side = 10;

		_graphics->ResetStates();
		_graphics->SetColor(Color::WHITE);
		for (int i = 0; i < count; i++)
		{
			_graphics->DrawLine(
				Vector3f(side * i, 0, 0),
				Vector3f(side * i, side * count, 0));
			_graphics->DrawLine(
				Vector3f(0, side * i, 0),
				Vector3f(side * count, side * i, 0));
		}
		_graphics->Flush();

// 		if (_model0)
// 		{
// 			_video->SetColor(COLOR_DRAW, Color::WHITE);
// 			_model0->Draw();
// 		}
// 
// 		_graphics->ResetStates();
// 		_graphics->SetColor(Color::WHITE);
// 		_graphics->DrawTriangle(0,
// 			Vertex3(Vector3f(0, 0, 0), 0xFFFFFFFF),
// 			Vertex3(Vector3f(100, 0, 0), 0xFFFFFFFF),
// 			Vertex3(Vector3f(100, 100, 0), 0xFFFFFFFF));
	}
}