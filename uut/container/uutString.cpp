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


	float String::ToFloat() const
	{
		return std::stof(GetData());
	}

	int String::ToInt() const
	{
		return std::stoi(GetData());
	}

	String String::Copy(int start, int count /*= -1*/) const
	{
		return String(_data.substr(start, count ? count : (int)_data.size() - start));
	}

	List<String> String::Split(char c, bool keepEmpty /*= false*/)
	{
		List<String> arr;
		int cur = 0, prev = 0;
		while ((cur = Find(c, prev)) >= 0)
		{
			const int count = cur - prev;
			if (count == 0)
			{
				if (keepEmpty)
					arr.Add(String::EMPTY);
			}
			else arr.Add(Copy(prev, count));
			prev = cur + 1;
		}

		arr.Add(Copy(prev));

		return arr;
	}
}