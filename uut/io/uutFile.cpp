#include "uutFile.h"
#include <Shlwapi.h>

namespace uut
{
	bool File::Exist(const String& path)
	{
		return PathFileExistsA(path.GetData()) ? true : false;
	}

	SharedPtr<FileStream> File::Open(const String& path, FileMode mode)
	{
		switch (mode)
		{
		case uut::FileMode::Append:
			return Open(path, mode, FileAccess::Write, FileShare::Write);

		case uut::FileMode::Create:
			return Open(path, mode, FileAccess::Write, FileShare::Write);

		case uut::FileMode::CreateNew:
			return Open(path, mode, FileAccess::Write, FileShare::Write);

		case uut::FileMode::Open:
			return Open(path, mode, FileAccess::Read, FileShare::Read);

		case uut::FileMode::OpenOrCreate:
			return Open(path, mode, FileAccess::Read, FileShare::Read);

		case uut::FileMode::Truncate:
			return Open(path, mode, FileAccess::Write, FileShare::Write);
			break;
		}

		return SharedPtr<FileStream>::EMPTY;
	}

	SharedPtr<FileStream> File::Open(const String& path, FileMode mode, FileAccess access)
	{
		switch (access)
		{
		case uut::FileAccess::Read:
			return Open(path, mode, access, FileShare::Read);

		case uut::FileAccess::ReadWrite:
			return Open(path, mode, access, FileShare::ReadWrite);

		case uut::FileAccess::Write:
			return Open(path, mode, access, FileShare::Write);
			break;
		}

		return SharedPtr<FileStream>::EMPTY;
	}

	SharedPtr<FileStream> File::Open(const String& path, FileMode mode, FileAccess access, FileShare share)
	{
		return SharedPtr<FileStream>(new FileStream(path, mode, access, share));
	}

}