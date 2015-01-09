#include "uutFileStream.h"

namespace uut
{
	FileStream::FileStream()
		: _handle(INVALID_HANDLE_VALUE)
	{
	}

	FileStream::FileStream(const String& path, FileMode mode, FileAccess access, FileShare share)
		: _handle(INVALID_HANDLE_VALUE)
	{
		Open(path, mode, access, share);
	}

	FileStream::~FileStream()
	{
		Close();
	}

	bool FileStream::Open(const String& path, FileMode mode, FileAccess access, FileShare share)
	{
		Close();

		DWORD dwAccess = 0;
		switch (access)
		{
		case uut::FileAccess::Read: dwAccess = GENERIC_READ; break;
		case uut::FileAccess::Write: dwAccess = GENERIC_WRITE; break;
		case uut::FileAccess::ReadWrite:
			dwAccess = GENERIC_READ | GENERIC_WRITE;
			break;
		}

		DWORD dwCreate = 0;
		switch (mode)
		{
		case uut::FileMode::Append:
			dwCreate = OPEN_ALWAYS;
			break;

		case uut::FileMode::Create:
			dwCreate = CREATE_ALWAYS;
			break;

		case uut::FileMode::CreateNew:
			dwCreate = CREATE_NEW;
			break;

		case uut::FileMode::Open:
			dwCreate = OPEN_EXISTING;
			break;

		case uut::FileMode::OpenOrCreate:
			dwCreate = OPEN_ALWAYS;
			break;

		case uut::FileMode::Truncate:
			dwCreate = TRUNCATE_EXISTING;
			break;
		}

		DWORD dwShare = 0;
		switch (share)
		{
		case uut::FileShare::Read: dwShare = FILE_SHARE_READ; break;
		case uut::FileShare::Write: dwShare = FILE_SHARE_WRITE; break;
		case uut::FileShare::Delete: dwShare = FILE_SHARE_DELETE; break;
		case uut::FileShare::ReadWrite:
			dwShare = FILE_SHARE_READ | FILE_SHARE_WRITE;
			break;
		}

		_handle = CreateFileA(path.GetData(), dwAccess, dwShare, NULL, dwCreate, 0, NULL);
		if (_handle == INVALID_HANDLE_VALUE)
			return false;

		_path = path;
		_access = access;
		_mode = mode;
		_share = share;
		return true;
	}

	uint32_t FileStream::Read(void* buffer, uint32_t size)
	{
		if (_handle == INVALID_HANDLE_VALUE)
			return 0;

		DWORD readed;
		if (!ReadFile(_handle, buffer, size, &readed, NULL))
			return readed;

		return readed;
	}

	uint32_t FileStream::Write(const void* buffer, uint32_t size)
	{
		if (_handle == INVALID_HANDLE_VALUE)
			return 0;

		DWORD writed;
		if (!WriteFile(_handle, buffer, size, &writed, NULL))
			return writed;

		return writed;
	}

	int64_t FileStream::Seek(int64_t offset, SeekOrigin origin)
	{
		if (_handle == INVALID_HANDLE_VALUE)
			return false;

		DWORD dwMethod = 0;
		switch (origin)
		{
		case uut::SeekOrigin::Begin: dwMethod = FILE_BEGIN; break;
		case uut::SeekOrigin::Current: dwMethod = FILE_CURRENT; break;
		case uut::SeekOrigin::End: dwMethod = FILE_END; break;
		}

		LARGE_INTEGER liOfs, liNew;

		liOfs.QuadPart = offset;
		SetFilePointerEx(_handle, liOfs, &liNew, dwMethod);
		return liNew.QuadPart;
	}

	void FileStream::Close()
	{
		if (_handle == INVALID_HANDLE_VALUE)
			return;

		CloseHandle(_handle);
		_handle = 0;
		_path = String::EMPTY;
	}

	int64_t FileStream::GetPosition() const
	{
		if (_handle == INVALID_HANDLE_VALUE)
			return 0;

		LARGE_INTEGER liOfs = { 0 };
		LARGE_INTEGER liNew = { 0 };
		SetFilePointerEx(_handle, liOfs, &liNew, FILE_CURRENT);
		return liNew.QuadPart;
	}

	void FileStream::SetLength(int64_t length)
	{
		if (_handle == INVALID_HANDLE_VALUE)
			return;

		LARGE_INTEGER li;
		li.QuadPart = length;
		SetFilePointerEx(_handle, li, NULL, FILE_BEGIN);
		SetEndOfFile(_handle);
	}

	int64_t FileStream::GetLength() const
	{
		if (_handle == INVALID_HANDLE_VALUE)
			return 0;

		LARGE_INTEGER li;
		GetFileSizeEx(_handle, &li);
		return li.QuadPart;
	}

	const String& FileStream::GetName() const
	{
		return _path;
	}

	bool FileStream::CanRead() const
	{
		return _access != FileAccess::Write;
	}

	bool FileStream::CanWrite() const
	{
		return _access != FileAccess::Read;
	}

	bool FileStream::CanSeek() const
	{
		return true;
	}

	bool FileStream::IsOpened() const
	{
		return _handle != INVALID_HANDLE_VALUE;
	}

	bool FileStream::IsEOF() const
	{
		return GetPosition() == GetLength();
	}

}