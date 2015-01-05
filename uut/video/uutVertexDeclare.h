#pragma once
#include "container/uutHashString.h"
#include "uutVideoDefs.h"

namespace uut
{
	struct VertexDeclaration
	{
		HashString name;
		uint16_t size;
		uint8_t count;
		SDeclareType* types;

		VertexDeclaration(const char* name, uint16_t size, std::initializer_list<SDeclareType> types);
	};

#define BRACED_INIT_LIST(...) {__VA_ARGS__}
#define DECLARE_VERTEX static const VertexDeclaration DECLARE;
#define IMPLEMENT_VERTEX(type, list)\
	const VertexDeclaration type::DECLARE(#type, sizeof(type), BRACED_INIT_LIST list);
}