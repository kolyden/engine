#include "LevelChunk.h"
#include "Level.h"
#include "video/uutModel.h"

namespace uut
{
	LevelChunk::LevelChunk(Context* context)
		: Object(context)
		, _index(0, 0)
		, _cells(0)
		, _position(0,0,0)
	{
	}

	LevelChunk::~LevelChunk()
	{
		delete[] _cells;
	}

	void LevelChunk::Init(Level* level, const Vector2i& index)
	{
		_level = level;
		_index = index;
		_cells = new LevelCell[MAX_COUNT];
		_position = Vector3f(
			SIDE * LevelCell::SIZE * index.x,
			0,
			SIDE * LevelCell::SIZE * index.y);
	}

	void LevelChunk::Draw() const
	{
		for (int y = 0; y < SIDE; y++)
		{
			for (int x = 0; x < SIDE; x++)
			{
				const auto& cell = GetCell(Vector2i(x, y));
				if (cell._floor < 0)
					continue;

				const Vector3f offset = _position + Vector3f(x * LevelCell::SIZE, 0, y * LevelCell::SIZE);
				glPushMatrix();
				glTranslatef(offset.x, offset.y, offset.z);
				_level->GetPrefabs()[cell._floor]->Draw();

				if (cell._wall[DIR_WEST] >= 0)
				{
					glPushMatrix();
					glTranslatef(-0.5f * LevelCell::SIZE, 0, 0);
					_level->GetPrefabs()[cell._wall[DIR_WEST]]->Draw();
					glPopMatrix();
				}

				if (cell._wall[DIR_EAST] >= 0)
				{
					glPushMatrix();
					glTranslatef(+0.5f * LevelCell::SIZE, 0, 0);
					_level->GetPrefabs()[cell._wall[DIR_EAST]]->Draw();
					glPopMatrix();
				}

				if (cell._wall[DIR_NORTH] >= 0)
				{
					glPushMatrix();
					glRotatef(90, 0, 1, 0);
					glTranslatef(+0.5f * LevelCell::SIZE, 0, 0);
					_level->GetPrefabs()[cell._wall[DIR_NORTH]]->Draw();
					glPopMatrix();
				}

				if (cell._wall[DIR_SOUTH] >= 0)
				{
					glPushMatrix();
					glRotatef(90, 0, 1, 0);
					glTranslatef(-0.5f * LevelCell::SIZE, 0, 0);
					_level->GetPrefabs()[cell._wall[DIR_SOUTH]]->Draw();
					glPopMatrix();
				}
				glPopMatrix();
			}
		}
	}

	LevelCell& LevelChunk::GetCell(const Vector2i& pos)
	{
		return _cells[pos.x + pos.y * SIDE];
	}

	const LevelCell& LevelChunk::GetCell(const Vector2i& pos) const
	{
		return _cells[pos.x + pos.y * SIDE];
	}
}