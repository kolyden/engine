#pragma once
#include "resource/uutResource.h"
#include "uutVertexDeclare.h"

namespace uut
{
	class FontFace;

	class UUT_API Font : public Resource
	{
		OBJECT(Font)
	public:
		Font(Context* context);

		virtual FontFace* GetFace(uint16_t size) = 0;
	};
}