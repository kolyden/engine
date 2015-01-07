#include "Level.h"
#include "LevelData.h"
#include "LevelChunk.h"
#include "core/uutContext.h"
#include "video/uutModel.h"

namespace uut
{
	Level::Level(Context* context)
		: Object(context)
	{
	}

	bool Level::Create(LevelData* data)
	{
		if (data == 0)
			return false;

		const auto& size = data->GetSize();
		if (size.x <= 0 || size.y <= 0)
			return false;

		Clear();

		for (int y = 0; y < size.y; y++)
		for (int x = 0; x < size.x; x++)
		{
			const Vector2i index(x / LevelChunk::SIDE, y / LevelChunk::SIDE);
			const Vector2i pos(x - index.x * LevelChunk::SIDE, y - index.y * LevelChunk::SIDE);
			auto chunk = GetChunk(index);
			chunk->GetCell(pos) = data->GetCell(Vector2i(x, y));
		}

		_prefabs = data->GetPrefabs();

		return true;
	}

	void Level::Clear()
	{
		_chunks.Clear();
		_prefabs.Clear();
	}

	void Level::Draw() const
	{
		for (int i = 0; i < _chunks.Count(); i++)
			_chunks[i]->Draw();
	}

	LevelChunk* Level::FindChunk(const Vector2i& index)
	{
		for (int i = 0; i < _chunks.Count(); i++)
		{
			if (_chunks[i]->GetIndex() == index)
				return _chunks[i];
		}

		return 0;
	}

	LevelChunk* Level::GetChunk(const Vector2i& index)
	{
		SharedPtr<LevelChunk> chunk(FindChunk(index));
		if (chunk) return chunk;

		chunk = new LevelChunk(_context);
		chunk->Init(this, index);
		_chunks.Add(chunk);

		return chunk;
	}

	const List<SharedPtr<Model>>& Level::GetPrefabs() const
	{
		return _prefabs;
	}


}