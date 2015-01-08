#include "uutBinaryReader.h"
#include "uutDeserializer.h"

namespace uut
{
	BinaryReader::BinaryReader(Deserializer* source)
		: _source(source)
	{
	}

}