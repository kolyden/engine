#pragma once
#include "core/uutModule.h"

namespace uut
{
	class UUT_API Filesystem : public Module
	{
		OBJECT(Filesystem)
	public:
		Filesystem(Context* context);
	};
}