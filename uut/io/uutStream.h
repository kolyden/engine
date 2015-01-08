#pragma once
#include "core/uutPtr.h"
#include "container/uutString.h"

namespace uut
{
	enum class SeekOrigin
	{
		Begin,
		Current,
		End,
	};

	class UUT_API Stream : public RefCounted
	{
	public:
		virtual ~Stream() {}

		virtual uint32_t Read(void* buffer, uint32_t size) = 0;
		virtual uint32_t Write(const void* buffer, uint32_t size) = 0;
		virtual int64_t Seek(int64_t offset, SeekOrigin origin) = 0;
		virtual void Close() = 0;

		virtual int64_t GetPosition() const = 0;
		virtual void SetLength(int64_t length) = 0;
		virtual int64_t GetLength() const = 0;

		virtual const String& GetName() const = 0;

		virtual bool CanRead() const = 0;
		virtual bool CanWrite() const = 0;
		virtual bool CanSeek() const = 0;
		virtual bool IsOpened() const = 0;

		static SDL_RWops* CreatReadRWops(Stream* source);
	};
}