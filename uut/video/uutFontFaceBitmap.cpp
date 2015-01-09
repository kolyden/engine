#include "uutFontFaceBitmap.h"
#include "uutTexture.h"

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