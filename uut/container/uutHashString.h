#pragma once
#include "uutString.h"
#include <string>

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
		bool Empty() const { return _data.empty(); }

		bool operator == (const HashString& str) const { return _hash == str._hash; }
		bool operator != (const HashString& str) const { return _hash != str._hash; }
		bool operator < (const HashString& str) const { return _hash < str._hash; }
		bool operator > (const HashString& str) const { return _hash > str._hash; }

		static unsigned Calculate(const char* str);

		static const HashString EMPTY;

	protected:
		unsigned _hash;
		std::string _data;
	};
}