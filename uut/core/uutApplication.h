#pragma once
#include "core/uutContext.h"

namespace uut
{
	class Filesystem;
	class Input;
	class Video;
	class ResourceCache;
	class Graphics;
	class Time;

	class Application
	{
	public:
		Application();

		int Run();
		void Stop();

	protected:
		Context* _context;
		WeakPtr<Time> _time;
		WeakPtr<Filesystem> _filesystem;
		WeakPtr<Input> _input;
		WeakPtr<Video> _video;
		WeakPtr<ResourceCache> _cache;
		WeakPtr<Graphics> _graphics;

		virtual void OnInit() {}
		virtual void OnStart() {}
		virtual void OnStop() {}
		virtual void OnUpdate() {}
		virtual void OnRender() {}

	private:
		bool _quit;
	};
}

#define RUNAPP(type)\
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)\
	{type app;\
	return app.Run();}