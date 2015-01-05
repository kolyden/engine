#include "uutVertexDeclare.h"

namespace uut
{
	VertexDeclaration::VertexDeclaration(const char* _name, uint16_t _size,
		std::initializer_list<SDeclareType> _types)
		: name(_name)
		, size(_size)
		, count(_types.size())
	{
		types = new SDeclareType[count];
		int i = 0;
		for each (auto& it in _types)
			types[i++] = it;
	}
}