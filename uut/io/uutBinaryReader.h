#pragma once
#include "core/uutRefCounted.h"

namespace uut
{
	class Deserializer;

	class BinaryReader : public RefCounted
	{
	public:
		BinaryReader(Deserializer* source);

	protected:
		Deserializer* _source;
	};
}