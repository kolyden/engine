#include "uutBitmapFont.h"
#include "uutFontFaceBitmap.h"

namespace uut
{
	BitmapFont::BitmapFont(Context* context)
		: Font(context)
	{
	}

	FontFace* BitmapFont::GetFace(uint16_t size)
	{
		return _face;
	}

}