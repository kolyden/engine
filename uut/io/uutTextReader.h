#pragma once
#include "core/uutPtr.h"
#include "container/uutString.h"

namespace uut
{
	class Stream;

	class TextReader : public RefCounted
	{
	public:
		TextReader(Stream* source);

		String ReadLine();

	protected:
		SharedPtr<Stream> _source;
	};
}