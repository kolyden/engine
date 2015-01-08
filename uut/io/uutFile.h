#pragma once
#include "core/uutDefine.h"
#include "container/uutString.h"

struct SDL_RWops;

namespace uut
{
	class File
	{
	public:
		static bool Exist(const String& path);
	};
}