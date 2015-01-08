#pragma once
#include "resource/uutResource.h"
#include "container/uutList.h"
#include "math/uutVector2.h"

namespace uut
{
	class LevelChunk;
	class Model;

	class Level : public Resource
	{
		OBJECT(Level)
	public:
		Level(Context* context);

		void Clear();

		void Draw() const;

		LevelChunk* FindChunk(const Vector2i& index);
		LevelChunk* GetChunk(const Vector2i& index);

		void SetPrefabs(const List<SharedPtr<Model>>& prefabs);
		const List<SharedPtr<Model>>& GetPrefabs() const;

	protected:
		List<SharedPtr<LevelChunk>> _chunks;
		List<SharedPtr<Model>> _prefabs;
	};
}