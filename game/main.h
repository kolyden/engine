#pragma once
#include "core/uutApplication.h"
#include <windows.h>
#include "video/uutColor.h"
#include "math/uutVector2.h"
#include "math/uutVector3.h"
#include "math/uutMatrix.h"
#include "math/uutQuaternion.h"
#include "math/uutRect.h"

namespace uut
{
	class Camera;
	class Texture;
	class VideoBuffer;
	class Model;

	class MyApp : public Application
	{
	public:
		MyApp();

	protected:
		SharedPtr<Texture> _tex0;
		SharedPtr<Model> _model0;

		Matrix4f _matProj;
		Matrix4f _matView;
		Vector3f _cameraPos;
		Vector3f _cameraEye;
		Quaternionf _cameraRot;

		Color _color;
		Vector2i _pos;
		Vector2i _size;
		bool _paused;

		virtual void OnInit() override;
		virtual void OnStart() override;
		virtual void OnUpdate() override;
		virtual void OnRender() override;
	};
}