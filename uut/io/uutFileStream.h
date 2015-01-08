#pragma once
#include "uutStream.h"
#include "container/uutString.h"

namespace uut
{
	enum class FileMode
	{
		Append,
		Create,
		CreateNew,
		Open,
		OpenOrCreate,
		Truncate,
	};

	enum class FileAccess
	{
		Read,
		ReadWrite,
		Write,
	};

	enum class FileShare
	{
		None,
		Read,
		Write,
		ReadWrite,
		Delete,
	};

	class UUT_API FileStream : public Stream
	{
	public:
		FileStream();
		FileStream(const String& path, FileMode mode, FileAccess access, FileShare share);
		virtual ~FileStream();

		bool Open(const String& path, FileMode mode, FileAccess access, FileShare share);

		virtual uint32_t Read(void* buffer, uint32_t size) override;
		virtual uint32_t Write(const void* buffer, uint32_t size) override;
		virtual int64_t Seek(int64_t offset, SeekOrigin origin) override;
		virtual void Close() override;

		virtual int64_t GetPosition() const override;
		virtual void SetLength(int64_t length) override;
		virtual int64_t GetLength() const override;

		virtual const String& GetName() const override;

		virtual bool CanRead() const override;
		virtual bool CanWrite() const override;
		virtual bool CanSeek() const override;
		virtual bool IsOpened() const override;

	protected:
		FileMode _mode;
		FileAccess _access;
		FileShare _share;
		HANDLE _handle;
		String _path;
	};
}