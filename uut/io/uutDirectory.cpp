#include "uutDirectory.h"

namespace uut
{
	List<String> Directory::GetDirectories(const String& path)
	{
		WIN32_FIND_DATAA ffd;
		HANDLE handle = FindFirstFileA(path.GetData(), &ffd);
		if (handle == INVALID_HANDLE_VALUE)
			return List<String>::EMPTY;

		List<String> ret;
		do
		{
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				ret.Add(ffd.cFileName);
			}
		} while (FindNextFileA(handle, &ffd) != 0);

		return ret;
	}

	List<String> Directory::GetFiles(const String& path)
	{
		WIN32_FIND_DATAA ffd;
		HANDLE handle = FindFirstFileA(path.GetData(), &ffd);
		if (handle == INVALID_HANDLE_VALUE)
			return List<String>::EMPTY;

		List<String> ret;
		do
		{
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
			}
			else
			{
				ret.Add(ffd.cFileName);
			}
		} while (FindNextFileA(handle, &ffd) != 0);

		return ret;
	}

	//////////////////////////////////////////////////////////////////////////

}