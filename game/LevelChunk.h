#pragma once
#include "core/uutObject.h"
#include "math/uutVector2.h"
#include "math/uutVector3.h"
#include "LevelCell.h"

namespace uut
{
	class Level;

	class LevelChunk : public Object
	{
		OBJECT(LevelChunk)
	public:
		static const int SIDE = 16;

		LevelChunk(Context* context);
		~LevelChunk();

		void Init(Level* level, const Vector2i& index);
		void Draw() const;

		const Vector2i& GetIndex() const { return _index; }

		LevelCell& GetCell(const Vector2i& pos);
		const LevelCell& GetCell(const Vector2i& pos) const;

	protected:
		static const int MAX_COUNT = SIDE * SIDE;

		WeakPtr<Level> _level;
		Vector2i _index;
		LevelCell* _cells;
		Vector3f _position;
	};
}