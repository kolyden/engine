#include "uutPath.h"
#include "math/uutMath.h"

namespace uut
{
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

	bool Path::HasExtension(const String& path)
	{
		const int count = path.Count();
		for (int i = count - 1; i > 0; i--)
		{
			const char c = path[i];
			if (c == '/' || c == '\\')
				break;

			if (c == '.')
				return true;
		}

		return false;
	}

	//////////////////////////////////////////////////////////////////////////
	uut::String Path::PreparePath(const String& path)
	{
		return path;
	}
}