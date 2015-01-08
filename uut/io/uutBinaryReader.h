#pragma once
#include "core/uutPtr.h"

namespace uut
{
	class Stream;

	class BinaryReader : public RefCounted
	{
	public:
		BinaryReader(Stream* source);

	protected:
		SharedPtr<Stream> _source;
	};
}