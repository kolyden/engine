#pragma once
#include "core/uutObject.h"
#include "container/uutList.h"
#include "math/uutVector2.h"

namespace uut
{
	class LevelData;
	class LevelChunk;
	class Model;

	class Level : public Object
	{
		OBJECT(Level)
	public:
		Level(Context* context);

		bool Create(LevelData* data);
		void Clear();

		void Draw() const;

		LevelChunk* FindChunk(const Vector2i& index);
		LevelChunk* GetChunk(const Vector2i& index);

		const List<SharedPtr<Model>>& GetPrefabs() const;

	protected:
		List<SharedPtr<LevelChunk>> _chunks;
		List<SharedPtr<Model>> _prefabs;
	};
}