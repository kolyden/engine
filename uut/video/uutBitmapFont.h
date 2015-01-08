#pragma once
#include "uutFont.h"

namespace uut
{
	class UUT_API BitmapFont : public Font
	{
		OBJECT(BitmapFont)
	public:
		BitmapFont(Context* context);
	};
}