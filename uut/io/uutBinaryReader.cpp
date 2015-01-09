#include "uutBinaryReader.h"
#include "uutStream.h"

namespace uut
{
	template<class T>
	static bool ReadType(Stream* source, T* data)
	{
		if (source == 0)
			return false;

		return source->Read(data, sizeof(T)) == sizeof(T);
	}

	//////////////////////////////////////////////////////////////////////////
	BinaryReader::BinaryReader(Stream* source)
		: _source(source)
	{
	}

	unsigned BinaryReader::ReadBytes(unsigned count, void* buffer)
	{
		if (_source == 0)
			return 0;

		return _source->Read(buffer, count);
	}

	unsigned BinaryReader::ReadBytes(unsigned count, List<uint8_t>& bytes)
	{
		if (_source == 0)
			return 0;

		unsigned i = 0;
		while (i < count)
		{
			uint8_t b;
			if (_source->Read(&b, 1) != 1)
				return i;

			bytes.Add(b);
			i++;
		}
		
		return count;
	}

	unsigned BinaryReader::ReadChars(unsigned count, List<char>& chars)
	{
		if (_source == 0)
			return 0;

		unsigned i = 0;
		while (i < count)
		{
			char b;
			if (_source->Read(&b, 1) != 1)
				return i;

			chars.Add(b);
			i++;
		}

		return count;
	}

	bool BinaryReader::ReadBoolean()
	{
		bool data;
		return ReadType(_source, &data) ? data : false;
	}

	String BinaryReader::ReadStringNT()
	{
		if (_source == 0)
			return String::EMPTY;

		String ret;
		char c;
		while (_source->Read(&c, 1) == 1)
		{
			if (c == 0)
				break;

			ret += c;
		}

		return ret;
	}

	int8_t BinaryReader::ReadInt8()
	{
		int8_t data;
		return ReadType(_source, &data) ? data : 0;
	}

	int16_t BinaryReader::ReadInt16()
	{
		int16_t data;
		return ReadType(_source, &data) ? data : 0;
	}

	int32_t BinaryReader::ReadInt32()
	{
		int32_t data;
		return ReadType(_source, &data) ? data : 0;
	}

	int64_t BinaryReader::ReadInt64()
	{
		int64_t data;
		return ReadType(_source, &data) ? data : 0;
	}

	uint8_t  BinaryReader::ReadUint8()
	{
		uint8_t data;
		return ReadType(_source, &data) ? data : 0;
	}

	uint16_t BinaryReader::ReadUint16()
	{
		uint16_t data;
		return ReadType(_source, &data) ? data : 0;
	}

	uint32_t BinaryReader::ReadUint32()
	{
		uint32_t data;
		return ReadType(_source, &data) ? data : 0;
	}

	uint64_t BinaryReader::ReadUint64()
	{
		uint64_t data;
		return ReadType(_source, &data) ? data : 0;
	}

	bool BinaryReader::IsEOF() const
	{
		if (_source == 0)
			return true;

		return _source->IsEOF();
	}

}