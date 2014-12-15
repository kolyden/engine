#include "container/uutHashString.h"
#include "math/uutMath.h"

namespace uut
{
	HashString::HashString()
		: _hash(0)
	{
	}

	HashString::HashString(const char* str)
		: _data(str, str + strlen(str))
		, _hash(Calculate(str))
	{
	}

	HashString::HashString(const String& str)
		: _data(str.GetData(), str.GetData() + str.Count())
		, _hash(Calculate(str.GetData()))
	{
	}

	unsigned HashString::Calculate(const char* str)
	{
		unsigned hash = 0;

		if (!str)
			return hash;

		while (*str)
		{
			// Perform the actual hashing as case-insensitive
			char c = *str;
			hash = Math::SDBMHash(hash, tolower(c));
			++str;
		}

		return hash;
	}
}