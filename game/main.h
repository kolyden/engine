#pragma once
#include "core/uutApplication.h"
#include <windows.h>
#include "video/uutColor.h"
#include "math/uutVector2.h"

namespace uut
{
	class World;
	class Camera;
	class Texture;
	class VideoBuffer;
	class Model;
	class Font;

	class MyApp : public Application
	{
	public:
		MyApp();

	protected:
		WeakPtr<World> _world;

		SharedPtr<Texture> _tex0;
		SharedPtr<Texture> _tex1;
		SharedPtr<Model> _model0;
		SharedPtr<Camera> _camera;
		SharedPtr<Font> _font;

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