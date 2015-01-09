#pragma once
#include "core/uutPtr.h"
#include "container/uutList.h"
#include "container/uutDictionary.h"
#include "video/uutVertex2.h"

namespace uut
{
	struct UUT_API FontGlyph
	{
		uint32_t id;
		uint16_t x;
		uint16_t y;
		uint16_t width;
		uint16_t height;
		int16_t xoffset;
		int16_t yoffset;
		int16_t xadvance;
		uint8_t page;
		uint8_t chnl;
	};

	class Texture;

	class FontFace : public RefCounted
	{
	public:
		virtual uint16_t GetSize() const = 0;
		virtual const FontGlyph* GetGlyph(uint32_t id) const = 0;
		virtual int16_t GetKerning(uint32_t a, uint32_t b) const = 0;
		virtual Texture* GetTexture(int index) const = 0;

		virtual void GenerateLine(List<Vertex2>& verts, const String& line) const = 0;
	};
}