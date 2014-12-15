#pragma once
#include "container/uutString.h"

namespace uut
{
	class UUT_API HashString
	{
	public:
		HashString();
		HashString(const char* str);
		HashString(const String& str);

		const char* GetData() const { return _data.data(); }
		unsigned GetHash() const { return _hash; }

		bool operator == (const HashString& str) const { return _hash == str._hash; }
		bool operator != (const HashString& str) const { return _hash != str._hash; }
		bool operator < (const HashString& str) const { return _hash < str._hash; }
		bool operator > (const HashString& str) const { return _hash > str._hash; }

		static unsigned Calculate(const char* str);

	protected:
		unsigned _hash;
		std::vector<char> _data;
	};
}