#pragma once
#include "core/uutPtr.h"
#include "container/uutList.h"
#include "container/uutString.h"

namespace uut
{
	class Stream;

	class BinaryReader : public RefCounted
	{
	public:
		BinaryReader(Stream* source);

		unsigned ReadBytes(unsigned count, void* buffer);

		unsigned ReadBytes(unsigned count, List<uint8_t>& bytes);
		unsigned ReadChars(unsigned count, List<char>& chars);

		bool ReadBoolean();
		String ReadStringNT();

		int8_t  ReadInt8();
		int16_t ReadInt16();
		int32_t ReadInt32();
		int64_t ReadInt64();

		uint8_t  ReadUint8();
		uint16_t ReadUint16();
		uint32_t ReadUint32();
		uint64_t ReadUint64();

		bool IsEOF() const;

	protected:
		SharedPtr<Stream> _source;
	};
}