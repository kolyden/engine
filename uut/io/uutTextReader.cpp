#include "uutTextReader.h"
#include "uutStream.h"

namespace uut
{
	TextReader::TextReader(Stream* source)
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