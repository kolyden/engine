#pragma once
#include "core/uutDefine.h"

namespace uut
{
	enum Direction
	{
		DIR_NORTH,
		DIR_EAST,
		DIR_SOUTH,
		DIR_WEST,
	};

	typedef int CellPrefabIndex;

	struct LevelCell
	{
		static const float SIZE;

		void SetFloor(CellPrefabIndex index);
		void SetWall(Direction dir, CellPrefabIndex index);
		void SetObject(CellPrefabIndex index);

		void Clear();
		bool IsEmpty() const;

		CellPrefabIndex _floor;
		CellPrefabIndex _wall[4];
		CellPrefabIndex _object;
	};
}