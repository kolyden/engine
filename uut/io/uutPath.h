#pragma once
#include "container/uutString.h"
#include "container/uutHashString.h"

namespace uut
{
	class UUT_API Path
	{
	public:
		Path();
		Path(const char* str);

		HashString GetExtension() const;
		bool IsExtension(const HashString& ext) const;

		String ToString() const { return _data; }

		bool operator < (const Path& path) const { return _hash < path._hash; }
		bool operator > (const Path& path) const { return _hash > path._hash; }

	protected:
		String _data;
		unsigned _hash;

		unsigned Calculate() const;
	};
}