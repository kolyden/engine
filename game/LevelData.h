#pragma once
#include "resource/uutResource.h"
#include "math/uutVector2.h"
#include "LevelCell.h"

namespace uut
{
	class Model;

	class LevelData : public Resource
	{
		OBJECT(LevelData)
	public:
		LevelData(Context* context);
		~LevelData();

		bool Create(const Vector2i& size);
		void Clear();

		const Vector2i& GetSize() const { return _size; }

		LevelCell& GetCell(const Vector2i& index);
		const LevelCell& GetCell(const Vector2i& index) const;

		void SetPrefabs(const List<SharedPtr<Model>>& prefabs);
		const List<SharedPtr<Model>>& GetPrefabs() const;

	protected:
		Vector2i _size;
		int _count;
		LevelCell* _cells;
		List<SharedPtr<Model>> _prefabs;
	};
}