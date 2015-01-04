#pragma once
#include "core/uutDefine.h"
#include "container/uutList.h"
#include <cctype>
#include <string>

namespace uut
{
	class UUT_API String
	{
	public:
		String();
		String(const std::string& str);
		String(const char* str);

		int Count() const { return (int)_data.size(); }
		bool Empty() const { return _data.empty(); }

		bool operator == (const String& str) const { return Equals(str, false); }
		bool operator != (const String& str) const { return !Equals(str, false); }

		char& operator[] (int index) { return _data[index]; }
		const char& operator[] (int index) const { return _data[index]; }

		bool Equals(const String& str, bool ignoreCase) const;
		int Compare(const String& str) const;
		
		String Copy(int start, int count = -1) const;

		float ToFloat() const;
		int ToInt() const;

		const char* GetData() const { return _data.c_str(); }

		int Find(char c, int start = 0) const				{ return (int)_data.find(c, start); }
		int Find(const String& str, int start = 0) const	{ return (int)_data.find(str.GetData(), start); }
		int FindR(char c) const								{ return (int)_data.rfind(c); }
		int FindR(const String& str) const					{ return (int)_data.rfind(str.GetData()); }

		void operator += (char c) { _data += c; }

		List<String> Split(char c, bool keepEmpty = false);

		static const String EMPTY;

	protected:
		std::string _data;
	};
}