#include "core/uutApplication.h"
#include "io/uutFilesystem.h"
#include "io/uutInput.h"
#include "video/uutVideo.h"
#include "resource/uutResourceCache.h"
#include "platform/uutPlatform.h"
#include "video/uutGraphics.h"
#include "platform/uutTime.h"

namespace uut
{
	Application::Application()
		: _context(new Context())
		, _quit(false)
	{
		_context->AddModule(new Platform(_context));

		_context->AddModule(new ResourceCache(_context));
		_context->AddModule(new Video(_context));
		_context->AddModule(new Graphics(_context));

		_time = _context->GetModule<Time>();
		_filesystem = _context->GetModule<Filesystem>();
		_input = _context->GetModule<Input>();
		_video = _context->GetModule<Video>();
		_cache = _context->GetModule<ResourceCache>();
		_graphics = _context->GetModule<Graphics>();
	}

	int Application::Run()
	{
		_context->Init();

		OnInit();
		OnStart();

		SDL_Event e;
		while (!_quit)
		{
			while (SDL_PollEvent(&e))
			{
				switch (e.type)
				{
				case SDL_QUIT:
				case SDL_APP_TERMINATING:
					Stop();
					break;

				default:
					_input->HandleSDLEvent(e);
				}
			}

			_time->NextFrame();
			OnUpdate();

			if (_video && _video->BeginFrame())
			{
				OnRender();
				_video->EndFrame();
			}
		}

		return 0;
	}

	void Application::Stop()
	{
		if (_quit)
			return;

		OnStop();
		_quit = true;
	}

}