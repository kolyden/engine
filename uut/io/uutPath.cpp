#include "uutPath.h"
#include "math/uutMath.h"

namespace uut
{
	Path::Path()
	{
	}

	Path::Path(const char* str)
		: _data(str)
		, _hash(Calculate())
	{
	}

	Path::Path(const String& str)
		: _data(str)
		, _hash(Calculate())
	{
	}

	HashString Path::GetExtension() const
	{
		const int pos = _data.FindR('.');
		if (pos < 0)
			return HashString::EMPTY;

		return HashString(_data.Copy(pos + 1));
	}

	bool Path::IsExtension(const HashString& ext) const
	{
		return GetExtension() == ext;
	}

	String Path::GetDirectory() const
	{
		const int pos = _data.FindR('/');
		if (pos < 0)
			return String::EMPTY;

		return _data.Copy(0, pos + 1);
	}

	//////////////////////////////////////////////////////////////////////////
	unsigned Path::Calculate() const
	{
		unsigned hash = 0;
		
		for (int i = 0; i < _data.Count(); i++)
		{
			const char c = _data[i];
			hash = Math::SDBMHash(hash, tolower(c));
		}

		return hash;
	}
}