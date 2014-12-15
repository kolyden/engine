#include "container/uutString.h"

namespace uut
{
	String::String()
	{
	}

	String::String(const char* str)
		: List<char>(str, strlen(str))
	{
	}

	bool String::Equals(const String& str, bool ignoreCase) const
	{
		return List<char>::Equals(str);
	}
}