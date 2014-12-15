#pragma once
#include "container/uutList.h"
#include <cctype>

namespace uut
{
	class UUT_API String : public List<char>
	{
	public:
		String();
		String(const char* str);

		bool Equals(const String& str, bool ignoreCase) const;
	};
}