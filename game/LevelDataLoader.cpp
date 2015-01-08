#include "LevelDataLoader.h"
#include "core/uutContext.h"
#include "resource/uutResourceCache.h"
#include "LevelData.h"
#include "io/uutTextReader.h"
#include "video/uutModel.h"

namespace uut
{
	LevelDataLoader::LevelDataLoader(Context* context)
		: ResourceLoader(context)
	{
	}

	const HashString& LevelDataLoader::GetResourceType() const
	{
		return LevelData::GetTypeStatic();
	}

	bool LevelDataLoader::CanLoad(const Path& path) const
	{
		return path.IsExtension("txt");
	}

	SharedPtr<Resource> LevelDataLoader::Load(Deserializer& source)
	{
		String line;
		List<String> list;

		SharedPtr<TextReader> reader(new TextReader(&source));

		line = reader->ReadLine();
		list = line.Split(' ');
		if (list.Count() < 2)
			return SharedPtr<Resource>::EMPTY;

		const Vector2i size(list[0].ToInt(), list[1].ToInt());
		auto data = _context->NewObject<LevelData>();
		if (!data->Create(size))
			return SharedPtr<Resource>::EMPTY;

		auto cache = _context->GetModule<ResourceCache>();
		List<SharedPtr<Model>> prefabs;
		prefabs.Add(SharedPtr<Model>(cache->Load<Model>("Data/Models/floor.obj")));
		prefabs.Add(SharedPtr<Model>(cache->Load<Model>("Data/Models/wall.obj")));

		bool** map = new bool*[size.x];
		for (int x = 0; x < size.x; x++)
			map[x] = new bool[size.y];

		for (int y = 0; y < size.y; y++)
		{
			line = reader->ReadLine();
			if (line.Count() != size.x)
			{
				for (int x = 0; x < size.x; x++)
					map[x][y] = false;

				continue;
			}

			for (int x = 0; x < size.x; x++)
				map[x][y] = line[x] == '#';
		}

		for (int x = 0; x < size.x; x++)
		for (int y = 0; y < size.y; y++)
		{
			auto& cell = data->GetCell(Vector2i(x, y));
			cell.Clear();

			if (map[x][y])
				continue;

			cell.SetFloor(0);

			if (x > 0 && map[x - 1][y])
				cell.SetWall(DIR_WEST, 1);
			if (x + 1 < size.x && map[x + 1][y])
				cell.SetWall(DIR_EAST, 1);
			if (y > 0 && map[x][y - 1])
				cell.SetWall(DIR_NORTH, 1);
			if (y + 1 < size.y && map[x][y + 1])
				cell.SetWall(DIR_SOUTH, 1);
		}

		data->SetPrefabs(prefabs);
		return DynamicCast<Resource>(data);
	}

}