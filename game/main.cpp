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
	static Matrix4f& perspective2(Matrix4f & M, const float fov, const float aspect, const float znear, const float zfar)
	{
		const float h = (1.0f / tanf(fov * 0.5f));// * zoom_;
		const float w = h / aspect;
		const float q = (zfar + znear) / (zfar - znear);
		const float r = -2.0f * zfar * znear / (zfar - znear);

		M._array[0] = w;
		M._array[1] = 0.0f;
		M._array[2] = 0.0f; //projectionOffset_.x_ * 2.0f;
		M._array[3] = 0.0f;

		M._array[4] = 0.0f;
		M._array[5] = h;
		M._array[6] = 0.0f; //projectionOffset_.y_ * 2.0f;
		M._array[7] = 0.0f;

		M._array[8] = 0.0f;
		M._array[9] = 0.0f;
		M._array[10] = q;
		M._array[11] = r;

		M._array[12] = 0.0f;
		M._array[13] = 0.0f;
		M._array[14] = 1.0f;
		M._array[15] = 0.0f;

		return M;
	}

	//////////////////////////////////////////////////////////////////////////
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

		Matrix4f::perspectivex(_matProj, Math::ToRad(60.0f), aspect, 0.0f, 100.0f);

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
			vec.y += speed * _time->GetDelta();
			_camera->SetPosition(vec);
		}

		if (_input->IsKey(KEYCODE_S))
		{
			auto vec = _camera->GetPosition();
			vec.y -= speed * _time->GetDelta();
			_camera->SetPosition(vec);
		}

		if (_input->IsKey(KEYCODE_A))
		{
			auto vec = _camera->GetPosition();
			vec.x += speed * _time->GetDelta();
			_camera->SetPosition(vec);
		}

		if (_input->IsKey(KEYCODE_D))
		{
			auto vec = _camera->GetPosition();
			vec.x -= speed * _time->GetDelta();
			_camera->SetPosition(vec);
		}

		if (_input->IsKey(KEYCODE_Q))
		{
			auto vec = _camera->GetPosition();
			vec.z += speed * _time->GetDelta();
			_camera->SetPosition(vec);
		}

		if (_input->IsKey(KEYCODE_Z))
		{
			auto vec = _camera->GetPosition();
			vec.z -= speed * _time->GetDelta();
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
		_video->SetTransform(TRANSFORM_PROJECTION, _matProj);
		_camera->UpdatePosition();

		const int count = 200;
		const float side = 1;

		_graphics->ResetStates();
		_graphics->SetColor(Color::WHITE);
		const Vector3f offset(0, 0, 10);
		for (int i = 0; i < count; i++)
		{
			// XY PLANE
			_graphics->DrawLine(
				offset + Vector3f(side * i, 0, 0),
				offset + Vector3f(side * i, side * count, 0));
			_graphics->DrawLine(
				offset + Vector3f(0, side * i, 0),
				offset + Vector3f(side * count, side * i, 0));

			// XZ PLANE
// 			_graphics->DrawLine(
// 				offset + Vector3f(side * i, 0, 0),
// 				offset + Vector3f(side * i, 0, side * count));
// 			_graphics->DrawLine(
// 				offset + Vector3f(0, side * i, 0),
// 				offset + Vector3f(side * count, 0, side * i));

			// YZ PLANE
// 			_graphics->DrawLine(
// 				offset + Vector3f(0, side * i, 0),
// 				offset + Vector3f(0, side * i, side * count));
// 			_graphics->DrawLine(
// 				offset + Vector3f(0, 0, side * i),
// 				offset + Vector3f(0, side * count, side * i));
		}
		_graphics->Flush();

// 		if (_model0)
// 		{
// 			_video->SetColor(COLOR_DRAW, Color::WHITE);
// 			_model0->Draw();
// 		}
 
// 		_graphics->ResetStates();
// 		_graphics->SetColor(Color::WHITE);
// 		_graphics->DrawTriangle(0,
// 			Vertex3(Vector3f(0, 0, 0), 0xFFFFFFFF),
// 			Vertex3(Vector3f(100, 0, 0), 0xFFFFFFFF),
// 			Vertex3(Vector3f(100, 100, 0), 0xFFFFFFFF));
	}
}