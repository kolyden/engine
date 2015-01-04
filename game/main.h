#pragma once
#include "core/uutApplication.h"
#include <windows.h>
#include "video/uutColor.h"
#include "math/uutVector2.h"
#include "math/uutVector3.h"
#include "Camera.h"

namespace uut
{

	class Texture;
	class VideoBuffer;
	class Model;

	class MyApp : public Application
	{
	public:
		MyApp();

	protected:
		SharedPtr<Texture> _tex0;
		SharedPtr<VideoBuffer> _vbuf;
		SharedPtr<VideoBuffer> _ibuf;
		SharedPtr<Model> _model0;
		SharedPtr<Camera> _camera;

		Color _color;
		Vector2i _pos;
		Vector2i _size;
		bool _paused;

		virtual void OnInit() override;
		virtual void OnStart() override;
		virtual void OnUpdate() override;
		virtual void OnRender() override;

		void UpdateBuffer(const Vector2i& pos, const Vector2f& size);
	};
}