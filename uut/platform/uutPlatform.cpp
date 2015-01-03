#include "uutPlatform.h"
#include "core/uutContext.h"
#include "core/uutDebug.h"
#include "io/uutFilesystem.h"
#include "io/uutInput.h"
#include "uutTime.h"

namespace uut
{
	Platform::Platform(Context* context)
		: Module(context)
	{
		char *base_path = SDL_GetBasePath();
		if (base_path)
		{
			_basePath = Path(base_path);
			SDL_free(base_path);
		}
	}

	String Platform::GetPlatformName() const
	{
		return SDL_GetPlatform();
	}

	const Path& Platform::GetBasePath() const
	{
		return _basePath;
	}

	//////////////////////////////////////////////////////////////////////////
	void Platform::OnRegister()
	{
		SDL_Init(SDL_INIT_EVERYTHING);

		_context->AddModule(new Time(_context));
		_context->AddModule(new Filesystem(_context));
		_context->AddModule(new Input(_context));
	}

	void Platform::OnUnregister()
	{
		SDL_Quit();
	}
}