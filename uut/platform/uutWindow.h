#pragma once
#include "core/uutObject.h"
#include "math/uutVector2.h"

namespace uut
{
	class Window : public Object
	{
		OBJECT(Window)
	public:
		Window(Context* context);

		void SetTitle(const String& title);
		const String& GetTitle() const;

		void SetSize(const Vector2i& size);
		const Vector2i& GetSize() const;

		bool Create();
		void Destroy();

	protected:
		SDL_Window* _window;
		String _title;
		Vector2i _size;

		friend class Video;
	};
}