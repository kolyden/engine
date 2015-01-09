#include "uutBitmapFontLoader.h"
#include "core/uutContext.h"
#include "resource/uutResourceCache.h"
#include "video/uutBitmapFont.h"
#include "video/uutFontFaceBitmap.h"
#include "video/uutTexture.h"
#include "core/uutDebug.h"
#include "io/uutPath.h"
#include "io/uutStream.h"
#include "io/uutBinaryReader.h"

namespace uut
{
	static const int STRING_BUFFER = 64;

	struct BlockType1
	{
		int16_t fontSize;
		uint8_t bitField;
		uint8_t charSize;
		uint16_t stretchH;
		uint8_t aa;
		uint8_t paddingUp;
		uint8_t paddingRight;
		uint8_t paddingDown;
		uint8_t paddingLeft;
		uint8_t spacingHoriz;
		uint8_t spacingVert;
		uint8_t outline;
		char fontName[STRING_BUFFER];
	};

	struct BlockType2
	{
		uint16_t lineHeight;
		uint16_t base;
		uint16_t scaleW;
		uint16_t scaleH;
		uint16_t pages;
		uint8_t bitField;
		uint8_t alphaChnl;
		uint8_t redChnl;
		uint8_t greenChnl;
		uint8_t blueChnl;
	};

	struct BlockType3
	{
		List<String> pageNames;
	};

	struct BlockType4
	{
		List<FontGlyph> chars;
	};

	struct BlockType5
	{
		List<FontKerningPair> pairs;
	};

	//////////////////////////////////////////////////////////////////////////
	BitmapFontLoader::BitmapFontLoader(Context* context)
		: ResourceLoader(context)
	{
	}

	const HashString& BitmapFontLoader::GetResourceType() const
	{
		return BitmapFont::GetTypeStatic();
	}

	bool BitmapFontLoader::CanLoad(const String& path) const
	{
		return Path::GetExtension(path).Equals("fnt", true);
	}

	SharedPtr<Resource> BitmapFontLoader::Load(Stream& source)
	{
		SharedPtr<BinaryReader> reader(new BinaryReader(&source));

		List<uint8_t> magic;
		reader->ReadBytes(3, magic);

		if (magic.Count() != 3 ||
			magic[0] != 'B' ||
			magic[1] != 'M' ||
			magic[2] != 'F')
			return SharedPtr<Resource>::EMPTY;

		const auto version = reader->ReadUint8();
		if (version != 3)
			return SharedPtr<Resource>::EMPTY;

		BlockType1 block1;
		BlockType2 block2;
		BlockType3 block3;
		BlockType4 block4;
		BlockType5 block5;

		while (!reader->IsEOF())
		{
			const auto type = reader->ReadUint8();
			const auto size = reader->ReadInt32();
			if (type == 1)
			{
				reader->ReadBytes(size, &block1);
			}
			else if (type == 2)
			{
				reader->ReadBytes(size, &block2);
			}
			else if (type == 3)
			{
				String str = reader->ReadStringNT();
				const int count = size / (str.Count() + 1);
				block3.pageNames.Add(str);
				for (int i = 1; i < count; i++)
				{
					str = reader->ReadStringNT();
					block3.pageNames.Add(str);
				}
			}
			else if (type == 4)
			{
				const int count = size / 20;
				for (int i = 0; i < count; i++)
				{
					FontGlyph data;
					reader->ReadBytes(20, &data);
					block4.chars.Add(data);
				}
			}
			else if (type == 5)
			{
				const int count = size / 10;
				for (int i = 0; i < count; i++)
				{
					FontKerningPair data;
					reader->ReadBytes(10, &data);
					block5.pairs.Add(data);
				}
			}
			else
			{
				Debug::LogError("Error fnt format");
				return SharedPtr<Resource>::EMPTY;
			}
		}

		SharedPtr<BitmapFont> font(new BitmapFont(_context));
		auto face = new FontFaceBitmap(block1.fontSize);
		font->_face = face;
		face->_glyphs = block4.chars;
		face->_kerningPairs = block5.pairs;
		face->UpdateGlyphsMap();
		face->UpdateKerningMap();

		auto cache = _context->GetModule<ResourceCache>();
		const String basedir = Path::GetDirectoryName(source.GetName());
		for (int i = 0; i < block3.pageNames.Count(); i++)
		{
			auto tex = cache->Load<Texture>(basedir + block3.pageNames[i]);
			face->_textures.Add(SharedPtr<Texture>(tex));
		}

		return DynamicCast<Resource>(font);
	}

}