#include "LevelCell.h"

namespace uut
{
	const float LevelCell::SIZE = 2.0f;

	void LevelCell::SetFloor(CellPrefabIndex index)
	{
		_floor = index;
	}

	void LevelCell::SetWall(Direction dir, CellPrefabIndex index)
	{
		_wall[dir] = index;
	}

	void LevelCell::SetObject(CellPrefabIndex index)
	{
		_object = index;
	}

	void LevelCell::Clear()
	{
		_floor = -1;
		_object = -1;
		for (int i = 0; i < 4; i++)
			_wall[i] = -1;
	}

	bool LevelCell::IsEmpty() const
	{
		return ((_floor < 0) && (_object < 0) &&
			(_wall[0] < 0) && (_wall[1] < 0) && (_wall[2] < 0) && (_wall[3] < 0));
	}
}