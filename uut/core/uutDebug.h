#pragma once
#include "core/uutDefine.h"

namespace uut
{
	class Debug
	{
	public:
		static void LogDebug(const char* str, ...);
		static void LogInfo(const char* str, ...);
		static void LogWarning(const char* str, ...);
		static void LogError(const char* str, ...);

		static void LogMessage(SDL_LogPriority priority, const char* str, ...);
		static void LogMessageV(SDL_LogPriority priority, const char* str, va_list ap);
	};
}