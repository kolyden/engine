#pragma once
#include "resource/uutResource.h"

namespace uut
{
	class UUT_API Font : public Resource
	{
		OBJECT(Font)
	public:
		Font(Context* context);
	};
}