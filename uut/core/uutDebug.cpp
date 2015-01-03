#include "core/uutDebug.h"

namespace uut
{

	void Debug::LogDebug(const char* str, ...)
	{
		va_list ap;
		va_start(ap, str);
		LogMessageV(SDL_LOG_PRIORITY_DEBUG, str, ap);
		va_end(ap);
	}

	void Debug::LogInfo(const char* str, ...)
	{
		va_list ap;
		va_start(ap, str);
		LogMessageV(SDL_LOG_PRIORITY_DEBUG, str, ap);
		va_end(ap);
	}

	void Debug::LogWarning(const char* str, ...)
	{
		va_list ap;
		va_start(ap, str);
		LogMessageV(SDL_LOG_PRIORITY_DEBUG, str, ap);
		va_end(ap);
	}

	void Debug::LogError(const char* str, ...)
	{
		va_list ap;
		va_start(ap, str);
		LogMessageV(SDL_LOG_PRIORITY_DEBUG, str, ap);
		va_end(ap);
	}

	void Debug::LogMessage(SDL_LogPriority priority, const char* str, ...)
	{
		va_list ap;
		va_start(ap, str);
		SDL_LogMessageV(SDL_LOG_CATEGORY_CUSTOM, priority, str, ap);
		va_end(ap);
	}

	void Debug::LogMessageV(SDL_LogPriority priority, const char* str, va_list ap)
	{
		SDL_LogMessageV(SDL_LOG_CATEGORY_CUSTOM, priority, str, ap);
	}

}