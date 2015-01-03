#include "uutModelLoaderOBJ.h"
#include "video/uutModel.h"
#include "video/uutGeometry.h"
#include "io/uutDeserializer.h"

namespace uut
{
	ModelLoaderOBJ::ModelLoaderOBJ(Context* context)
		: ResourceLoader(context)
	{
	}

	const HashString& ModelLoaderOBJ::GetResourceType() const
	{
		return Model::GetTypeStatic();
	}

	bool ModelLoaderOBJ::CanLoad(const Path& path) const
	{
		return path.IsExtension("obj");
	}

	static String ReadLine(Deserializer& source)
	{
		String ret;
		char c;
		while (source.Read(&c, 1) == 1 && c != '\n')
			ret += c;

		return ret;
	}

	static String ReadWord(Deserializer& source)
	{
		String ret;
		char c;
		while (source.Read(&c, 1) == 1 && c != ' ')
			ret += c;

		return ret;
	}

	SharedPtr<Resource> ModelLoaderOBJ::Load(Deserializer& source)
	{
		List<String> arr;

		auto geometry = SharedPtr<Geometry>(new Geometry(_context));
		auto model = SharedPtr<Model>(new Model(_context));
		model->SetGeometry(geometry);

		while (1)
		{
			String word = ReadWord(source);

			if (source.IsEof())
				break;

			if (word.Equals("v", true))
			{
				String line = ReadLine(source);
				arr = line.Split(' ');
				if (arr.Count() == 3)
				{
				}
			}
			else if (word.Equals("vt", true))
			{
			}
			else if (word.Equals("vn", true))
			{
			}
		}

		return DynamicCast<Resource>(model);
	}
}