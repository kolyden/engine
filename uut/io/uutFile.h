#pragma once
#include "uutFileStream.h"

struct SDL_RWops;

namespace uut
{
	class File
	{
	public:
		static bool Exist(const String& path);

		static SharedPtr<FileStream> Open(const String& path, FileMode mode);
		static SharedPtr<FileStream> Open(const String& path, FileMode mode, FileAccess access);
		static SharedPtr<FileStream> Open(const String& path, FileMode mode, FileAccess access, FileShare share);
	};
}