#include "uutFontFaceBitmap.h"
#include "uutTexture.h"
#include "math/uutRect.h"

namespace uut
{
	FontFaceBitmap::FontFaceBitmap(uint16_t size)
		: _size(size)
	{
	}

	uint16_t FontFaceBitmap::GetSize() const
	{
		return _size;
	}

	const FontGlyph* FontFaceBitmap::GetGlyph(uint32_t id) const
	{
		uint16_t index;
		if (!_glyphMap.TryGetValue(id, &index))
			return 0;

		return &_glyphs[index];
	}

	int16_t FontFaceBitmap::GetKerning(uint32_t a, uint32_t b) const
	{
		for (int i = 0; i < _kerningPairs.Count(); i++)
		{
			if (_kerningPairs[i].first == a &&
				_kerningPairs[i].second == b)
				return _kerningPairs[i].amount;
		}

		return 0;
	}

	Texture* FontFaceBitmap::GetTexture(int index) const
	{
		return _textures[index];
	}

	void FontFaceBitmap::GenerateLine(List<Vertex2>& verts, const String& line) const
	{
		const uint32_t color = 0xFFFFFFFF;
		const int count = line.Count();
		Vector2f pos(0, 0);
		for (int i = 0; i < count; i++)
		{
			auto glyph = GetGlyph(line[i]);
			if (glyph == 0)
				continue;

			auto tex = GetTexture(glyph->page);

			const float x1 = pos.x + glyph->yoffset;
			const float y1 = pos.y + glyph->yoffset;
			const float x2 = x1 + glyph->width;
			const float y2 = y1 + glyph->height;

			const float invTexW = 1.0f / tex->GetSize().x;
			const float invTexH = 1.0f / tex->GetSize().y;

			const float tx1 = invTexW * glyph->x;
			const float ty1 = invTexH * glyph->y;
			const float tx2 = invTexW * (glyph->x + glyph->width);
			const float ty2 = invTexH * (glyph->y + glyph->height);

			const Vertex2 v0(Vector2f(x1, y1), Vector2f(tx1, ty1), color);
			const Vertex2 v1(Vector2f(x2, y1), Vector2f(tx2, ty1), color);
			const Vertex2 v2(Vector2f(x2, y2), Vector2f(tx2, ty2), color);
			const Vertex2 v3(Vector2f(x1, y2), Vector2f(tx1, ty2), color);

			verts.Add(v0);
			verts.Add(v1);
			verts.Add(v2);

			verts.Add(v0);
			verts.Add(v2);
			verts.Add(v3);

			pos.x += glyph->xadvance;
			if (i + 1 < line.Count())
				pos.x += GetKerning(line[i], line[i + 1]);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void FontFaceBitmap::UpdateGlyphsMap()
	{
		_glyphMap.Clear();
		for (int i = 0; i < _glyphs.Count(); i++)
			_glyphMap.Add(_glyphs[i].id, i);
	}

	void FontFaceBitmap::UpdateKerningMap()
	{
// 		_kerningMap.Clear();
// 		for (int i = 0; i < _kerningPairs.Count(); i++)
// 			_kerningMap[_kerningPairs[i].first][_kerningPairs[i].second] = i;
	}
}