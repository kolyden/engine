#pragma once
#include "uutFont.h"

namespace uut
{
	class FontFaceBitmap;

	class UUT_API BitmapFont : public Font
	{
	public:
		BitmapFont(Context* context);

		virtual FontFace* GetFace(uint16_t size) override;

	protected:
		SharedPtr<FontFaceBitmap> _face;

		friend class BitmapFontLoader;
	};
}