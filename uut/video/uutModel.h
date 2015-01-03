#pragma once
#include "resource/uutResource.h"

namespace uut
{
	class UUT_API Model : public Resource
	{
		OBJECT(Model)
	public:
		Model(Context* context);
	};
}