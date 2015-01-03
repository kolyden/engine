#include "container/uutString.h"
#include "math/uutMath.h"
#include <algorithm>

namespace uut
{
	const String String::EMPTY;

	String::String()
	{
	}

	String::String(const std::string& str)
		: _data(str)
	{
	}

	String::String(const char* str)
		: _data(str)
	{
	}

	bool String::Equals(const String& str, bool ignoreCase) const
	{
		return Compare(str) == 0;
	}

	int String::Compare(const String& str) const
	{
		return _data.compare(str._data);
	}

	String String::Copy(int start, int count /*= -1*/) const
	{
		return String(_data.substr(start, count ? count : (int)_data.size() - start));
	}

}