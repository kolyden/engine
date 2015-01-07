#include "LevelData.h"
#include "video/uutModel.h"

namespace uut
{
	LevelData::LevelData(Context* context)
		: Resource(context)
		, _size(0, 0)
		, _cells(0)
		, _count(0)
	{
	}

	LevelData::~LevelData()
	{
		delete[] _cells;
	}

	bool LevelData::Create(const Vector2i& size)
	{
		if ((size.x <= 0) || (size.y <= 0))
			return false;
		if (_size == size)
			return true;

		Clear();
		_size = size;
		_count = _size.x * _size.y;
		_cells = new LevelCell[_count];
		for (int i = 0; i < _count; i++)
			_cells[i].Clear();

		return true;
	}

	void LevelData::Clear()
	{
		_size = Vector2i::ZERO;
		delete[] _cells;
		_cells = 0;
		_count = 0;
	}

	LevelCell& LevelData::GetCell(const Vector2i& index)
	{
		return _cells[index.x + index.y * _size.x];
	}

	const LevelCell& LevelData::GetCell(const Vector2i& index) const
	{
		return _cells[index.x + index.y * _size.x];
	}

	void LevelData::SetPrefabs(const List<SharedPtr<Model>>& prefabs)
	{
		_prefabs = prefabs;
	}

	const List<SharedPtr<Model>>& LevelData::GetPrefabs() const
	{
		return _prefabs;
	}

}