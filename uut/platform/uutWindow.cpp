#include "platform/uutWindow.h"

namespace uut
{
	Window::Window(Context* context)
		: Object(context)
		, _window(0)
		, _title("Title")
		, _size(320, 200)
	{}

	void Window::SetTitle(const String& title)
	{
		if (_title == title)
			return;

		_title = title;
		if (_window)
			SDL_SetWindowTitle(_window, _title.GetData());
	}

	const String& Window::GetTitle() const
	{
		return _title;
	}

	void Window::SetSize(const Vector2i& size)
	{
		if (_size == size)
			return;

		_size = size;
		if (_window)
			SDL_SetWindowSize(_window, _size._x, _size._y);
	}

	const Vector2i& Window::GetSize() const
	{
		return _size;
	}

	bool Window::Create()
	{
		if (_window)
			return true;

		_window = SDL_CreateWindow(
			_title.GetData(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			_size._x, _size._y,
			SDL_WINDOW_OPENGL);

		return _window != 0;
	}

	void Window::Destroy()
	{
		if (_window == 0)
			return;

		SDL_DestroyWindow(_window);
		_window = 0;
	}

}