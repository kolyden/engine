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
#include "Camera.h"

RUNAPP(uut::MyApp);

namespace uut
{
	const Vector3f CAMERA_ACCELERATION(0.1f, 0.1f, 0.1f);
	const float    CAMERA_FOVX = 90.0f;
	const Vector3f CAMERA_POS(0.0f, 0.0f, 0.0f);
	const float    CAMERA_SPEED_ROTATION = 0.2f;
	const float    CAMERA_SPEED_FLIGHT_YAW = 100.0f;
	const Vector3f CAMERA_VELOCITY(2.0f, 2.0f, 2.0f);
	const float    CAMERA_ZFAR = 100.0f;
	const float    CAMERA_ZNEAR = 0.1f;

	const float    FLOOR_WIDTH = 16.0f;
	const float    FLOOR_HEIGHT = 16.0f;
	const float    FLOOR_TILE_S = 8.0f;
	const float    FLOOR_TILE_T = 8.0f;

	float g_cameraRotationSpeed = 0.00001f * CAMERA_SPEED_ROTATION;

	static void GetMovementDirection(Camera* camera, Input* input, Vector3f &direction)
	{
		Vector3f velocity = camera->getCurrentVelocity();
		direction = Vector3f(0.0f, 0.0f, 0.0f);

		if (input->IsKey(KEYCODE_W))
		{
			camera->setCurrentVelocity(velocity.x, velocity.y, 0.0f);
			direction.z += 1.0f;
		}

		if (input->IsKey(KEYCODE_S))
		{
			camera->setCurrentVelocity(velocity.x, velocity.y, 0.0f);
			direction.z -= 1.0f;
		}

		if (input->IsKey(KEYCODE_D))
		{
			camera->setCurrentVelocity(0.0f, velocity.y, velocity.z);
			direction.x += 1.0f;
		}

		if (input->IsKey(KEYCODE_A))
		{
			camera->setCurrentVelocity(0.0f, velocity.y, velocity.z);
			direction.x -= 1.0f;
		}

		if (input->IsKey(KEYCODE_E))
		{
			camera->setCurrentVelocity(velocity.x, 0.0f, velocity.z);
			direction.y += 1.0f;
		}

		if (input->IsKey(KEYCODE_Q))
		{
			camera->setCurrentVelocity(velocity.x, 0.0f, velocity.z);
			direction.y -= 1.0f;
		}
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
		if (_camera)
		{
			_camera->perspective(CAMERA_FOVX,
				static_cast<float>(_size.x) / static_cast<float>(_size.y),
				CAMERA_ZNEAR, CAMERA_ZFAR);

			_camera->setBehavior(Camera::CAMERA_BEHAVIOR_FIRST_PERSON);
			_camera->setPosition(CAMERA_POS);
			_camera->setAcceleration(CAMERA_ACCELERATION);
			_camera->setVelocity(CAMERA_VELOCITY);
		}

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

// 		if (_input->IsKey(KEYCODE_W))
// 		{
// 			auto vec = _camera->getPosition();
// 			vec.y += speed * _time->GetDelta();
// 			_camera->setPosition(vec);
// 		}
// 
// 		if (_input->IsKey(KEYCODE_S))
// 		{
// 			auto vec = _camera->getPosition();
// 			vec.y -= speed * _time->GetDelta();
// 			_camera->setPosition(vec);
// 		}
// 
// 		if (_input->IsKey(KEYCODE_A))
// 		{
// 			auto vec = _camera->getPosition();
// 			vec.x += speed * _time->GetDelta();
// 			_camera->setPosition(vec);
// 		}
// 
// 		if (_input->IsKey(KEYCODE_D))
// 		{
// 			auto vec = _camera->getPosition();
// 			vec.x -= speed * _time->GetDelta();
// 			_camera->setPosition(vec);
// 		}
// 
// 		if (_input->IsKey(KEYCODE_Q))
// 		{
// 			auto vec = _camera->getPosition();
// 			vec.z += speed * _time->GetDelta();
// 			_camera->setPosition(vec);
// 		}
// 
// 		if (_input->IsKey(KEYCODE_Z))
// 		{
// 			auto vec = _camera->getPosition();
// 			vec.z -= speed * _time->GetDelta();
// 			_camera->setPosition(vec);
// 		}

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
		if (_camera)
		{
			float heading = 0.0f;
			float pitch = 0.0f;
			float roll = 0.0f;
			Vector3f direction;

			const Vector3f center(0.5f * _size.x, 0.5f * _size.y);

			GetMovementDirection(_camera, _input, direction);

			switch (_camera->getBehavior())
			{
			case Camera::CAMERA_BEHAVIOR_FIRST_PERSON:
				pitch = (center.y - _input->GetMousePos().y) * g_cameraRotationSpeed;
				heading = -(_input->GetMousePos().x - center.x) * g_cameraRotationSpeed;

				_camera->rotate(heading, pitch, 0.0f);
				break;

			case Camera::CAMERA_BEHAVIOR_FLIGHT:
				heading = -direction.x * CAMERA_SPEED_FLIGHT_YAW * _time->GetElapsed();
				pitch = -(center.y - _input->GetMousePos().y) * g_cameraRotationSpeed;
				roll = -(_input->GetMousePos().x - center.x) * g_cameraRotationSpeed;

				_camera->rotate(heading, pitch, roll);
				direction.x = 0.0f; // ignore yaw motion when updating camera velocity
				break;
			}

			_camera->updatePosition(direction, _time->GetElapsed());

			_video->SetTransform(TRANSFORM_PROJECTION, _camera->getProjectionMatrix());
			_video->SetTransform(TRANSFORM_VIEW, _camera->getViewMatrix());
		}

		const int count = 100;
		const float side = 1;

		_graphics->ResetStates();
		_graphics->SetColor(Color::WHITE);
		const Vector3f offset(0, 0, 10);
		for (int i = 0; i <= count; i++)
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