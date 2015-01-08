#pragma once
#include "core/uutRefCounted.h"
#include "container/uutString.h"

namespace uut
{
	class Deserializer;

	class TextReader : public RefCounted
	{
	public:
		TextReader(Deserializer* source);

		String ReadLine();

	protected:
		Deserializer* _source;
	};
}