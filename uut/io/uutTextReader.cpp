#include "uutTextReader.h"
#include "io/uutDeserializer.h"

namespace uut
{
	TextReader::TextReader(Deserializer* source)
		: _source(source)
	{
	}

	uut::String TextReader::ReadLine()
	{
		String ret;
		char c;
		while (_source->Read(&c, 1) == 1 && c != '\n')
		{
			if (c != '\r')
				ret += c;
		}

		return ret;
	}

}