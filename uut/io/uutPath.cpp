#include "uutPath.h"
#include "math/uutMath.h"

namespace uut
{

	/*
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
	}*/

	uut::String Path::Combine(const String& path1, const String& path2)
	{
		return path1 + "/" + path2;
	}

	uut::String Path::GetDirectoryName(const String& path)
	{
		const int count = path.Count();
		for (int i = count - 1; i > 0; i--)
		{
			const char c = path[i];
			if (c == '/' || c == '\\')
				return path.Copy(0, i + 1);
		}

		return String::EMPTY;
	}

	uut::String Path::GetExtension(const String& path)
	{
		const int count = path.Count();
		for (int i = count - 1; i > 0; i--)
		{
			const char c = path[i];
			if (c == '/' || c == '\\')
				break;

			if (c == '.')
				return path.Copy(i + 1);
		}

		return String::EMPTY;
	}

	uut::String Path::GetFileName(const String& path)
	{
		const int count = path.Count();
		for (int i = count - 1; i > 0; i--)
		{
			const char c = path[i];
			if (c == '/' || c == '\\')
				return path.Copy(i + 1);
		}

		return path;
	}

	uut::String Path::GetFileNameWithoutExtension(const String& path)
	{
		auto str = GetFileName(path);
		const int count = path.Count();
		for (int i = count - 1; i > 0; i--)
		{
			const char c = path[i];
			if (c == '/' || c == '\\')
				break;

			if (c == '.')
				return path.Copy(0, i);
		}

		return str;
	}

	//////////////////////////////////////////////////////////////////////////
	uut::String Path::PreparePath(const String& path)
	{
		return path;
	}

}