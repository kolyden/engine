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
#include "math/uutVector4.h"

RUNAPP(uut::MyApp);

namespace uut
{
	static void LookAt(Matrix4f& mat, const Vector3f &eye, const Vector3f &target, const Vector3f &up)
	{
		Vector3f zAxis = eye - target;
		Vector3f::normalize(zAxis);

// 		Vector3f viewDir = -zAxis;

		Vector3f xAxis = Vector3f::cross(up, zAxis);
		Vector3f::normalize(xAxis);

		Vector3f yAxis = Vector3f::cross(zAxis, xAxis);
		Vector3f::normalize(yAxis);

		mat._11 = xAxis.x;
		mat._21 = xAxis.y;
		mat._31 = xAxis.z;
		mat._41 = -Vector3f::dot(xAxis, eye);

		mat._12 = yAxis.x;
		mat._22 = yAxis.y;
		mat._32 = yAxis.z;
		mat._42 = -Vector3f::dot(yAxis, eye);

		mat._13 = zAxis.x;
		mat._23 = zAxis.y;
		mat._33 = zAxis.z;
		mat._43 = -Vector3f::dot(zAxis, eye);
	}

	static void Perspective(Matrix4f& mat, float fovx, float aspect, float znear, float zfar)
	{
		// Construct a projection matrix based on the horizontal field of view
		// 'fovx' rather than the more traditional vertical field of view 'fovy'.

		float e = 1.0f / tanf(Math::ToRad(fovx) / 2.0f);
		float aspectInv = 1.0f / aspect;
		float fovy = 2.0f * atanf(aspectInv / e);
		float xScale = 1.0f / tanf(0.5f * fovy);
		float yScale = xScale / aspectInv;

		mat._11 = e / aspect;
		mat._12 = 0.0f;
		mat._13 = 0.0f;
		mat._14 = 0.0f;

		mat._21 = 0.0f;
		mat._22 = e;
		mat._23 = 0.0f;
		mat._24 = 0.0f;

		mat._31 = 0.0f;
		mat._32 = 0.0f;
		mat._33 = (zfar + znear) / (znear - zfar);
		mat._34 = -1.0f;

		mat._41 = 0.0f;
		mat._42 = 0.0f;
		mat._43 = (2.0f * zfar * znear) / (znear - zfar);
		mat._44 = 0.0f;
	}

	//////////////////////////////////////////////////////////////////////////
	MyApp::MyApp()
		: _color(0, 0, 0)
		, _pos(100, 100)
		, _paused(false)
		, _size(800, 600)
		, _cameraPos(0, 0, 50)
		, _cameraEye(0, 0, 1)
		, _cameraRot(0, 0, 0, 1)
	{
	}

	void MyApp::OnInit()
	{
		const Recti rect(Vector2i::ZERO, _size);
		const float aspect = (1.0f * _size.x) / _size.y;

		Matrix4f::perspectivex(_matProj, Math::ToRad(50.0f), aspect, 0.1f, 100.0f);
// 		Perspective(_matProj, Math::ToRad(60.0f), aspect, 0.0f, 100.0f);
		Matrix4f::lookAt(_matView, _cameraPos + _cameraEye, _cameraPos, Vector3f(0, 1, 0));

		_video->SetMode(_size.x, _size.y);
		_video->SetViewPort(rect);
		_video->SetRenderState(RENDERSTATE_LIGHTNING, false);
		_video->SetRenderState(RENDERSTATE_DEPTH_TEST, false);

		_video->SetTransform(TRANSFORM_PROJECTION, _matProj);
		_video->SetTransform(TRANSFORM_VIEW, _matView);
	}

	void MyApp::OnStart()
	{
		_tex0 = _cache->Load<Texture>("Data/zazaka.png");
		_model0 = _cache->Load<Model>("Data/stairs.obj");
	}

	static float g_angle = 0.0f;

	void MyApp::OnUpdate()
	{
		_paused = _input->IsKey(KEYCODE_SPACE);
		if (_paused)
			return;

		const Vector2i newPos = _input->GetMousePos();
		if (_input->IsKey(KEYCODE_ESCAPE)) 
			Stop();

		const float moveSpeed = 100;
		const float rotSpeed = 1;

		if (_input->IsKey(KEYCODE_W)) _cameraPos.y += moveSpeed * _time->GetDelta();
		if (_input->IsKey(KEYCODE_S)) _cameraPos.y -= moveSpeed * _time->GetDelta();
		if (_input->IsKey(KEYCODE_A)) _cameraPos.x -= moveSpeed * _time->GetDelta();
		if (_input->IsKey(KEYCODE_D)) _cameraPos.x += moveSpeed * _time->GetDelta();
		if (_input->IsKey(KEYCODE_Q)) _cameraPos.z += moveSpeed * _time->GetDelta();
		if (_input->IsKey(KEYCODE_Z)) _cameraPos.z -= moveSpeed * _time->GetDelta();

		if (_input->IsKey(KEYCODE_R)) _cameraRot.x += rotSpeed * _time->GetDelta();
		if (_input->IsKey(KEYCODE_F)) _cameraRot.x -= rotSpeed * _time->GetDelta();

		if (_input->IsKey(KEYCODE_T)) _cameraRot.y += rotSpeed * _time->GetDelta();
		if (_input->IsKey(KEYCODE_G)) _cameraRot.y -= rotSpeed * _time->GetDelta();

		if (_input->IsKey(KEYCODE_Y)) _cameraRot.z += rotSpeed * _time->GetDelta();
		if (_input->IsKey(KEYCODE_H)) _cameraRot.z -= rotSpeed * _time->GetDelta();


		if (_input->IsKey(KEYCODE_C)) g_angle += rotSpeed * _time->GetDelta();
		if (_input->IsKey(KEYCODE_V)) g_angle -= rotSpeed * _time->GetDelta();


// 		if (delta != Vector3f::ZERO)
		{
			Matrix4f rot;
			auto dir = rot * Vector4f(_cameraEye, 1);

			Matrix4f::lookAt(_matView, _cameraPos + Vector3f(dir.x, dir.y, dir.z), _cameraPos, Vector3f(0, 1, 0));

			_video->SetTransform(TRANSFORM_VIEW, _matView);
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

// 		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0, 0, -50);
		glRotatef(g_angle, 1, 0, 0);

		const int count = 100;
		const float side = 1;

		_graphics->ResetStates();
		_graphics->SetColor(Color::WHITE);

		_graphics->DrawLine(Vector3f::ZERO, Vector3f(100, 0, 0));
		_graphics->DrawLine(Vector3f::ZERO, Vector3f(0, 100, 0));
		_graphics->DrawLine(Vector3f::ZERO, Vector3f(0, 0, 100));

		for (int i = 0; i <= count; i++)
		{
			// XY PLANE
// 			_graphics->DrawLine(
// 				Vector3f(side * i, 0, 0),
// 				Vector3f(side * i, side * count, 0));
// 			_graphics->DrawLine(
// 				Vector3f(0, side * i, 0),
// 				Vector3f(side * count, side * i, 0));
// 
			// XZ PLANE
// 			_graphics->DrawLine(
// 				Vector3f(side * i, 0, 0),
// 				Vector3f(side * i, 0, side * count));
// 			_graphics->DrawLine(
// 				Vector3f(0, side * i, 0),
// 				Vector3f(side * count, 0, side * i));

			// YZ PLANE
// 			_graphics->DrawLine(
// 				offset + Vector3f(0, side * i, 0),
// 				offset + Vector3f(0, side * i, side * count));
// 			_graphics->DrawLine(
// 				offset + Vector3f(0, 0, side * i),
// 				offset + Vector3f(0, side * count, side * i));
		}
		_graphics->Flush();

		if (_model0)
		{
			_video->SetColor(COLOR_DRAW, Color::WHITE);
			_model0->Draw();
		}
 
// 		_graphics->ResetStates();
// 		_graphics->SetColor(Color::WHITE);
// 		_graphics->DrawTriangle(0,
// 			Vertex3(Vector3f(0, 0, 0), 0xFFFFFFFF),
// 			Vertex3(Vector3f(100, 0, 0), 0xFFFFFFFF),
// 			Vertex3(Vector3f(100, 100, 0), 0xFFFFFFFF));
	}
}