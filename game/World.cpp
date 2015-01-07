#include "World.h"
#include "core/uutContext.h"
#include "resource/uutResourceCache.h"
#include "Level.h"
#include "LevelChunk.h"
#include "LevelData.h"
#include "LevelDataLoader.h"

namespace uut
{
	World::World(Context* context)
		: Module(context)
	{
	}

	bool World::LoadLevel(const Path& path)
	{
		auto cache = _context->GetModule<ResourceCache>();
		auto levelData = cache->Load<LevelData>(path);
		if (levelData == 0)
			return false;

		auto level = _context->NewObject<Level>();
		if (!level->Create(levelData))
			return false;

		SetLevel(level);
		return true;
	}

	void World::SetLevel(Level* level)
	{
		_current = level;
	}

	Level* World::GetLevel() const
	{
		return _current;
	}

	//////////////////////////////////////////////////////////////////////////
	void World::OnRegister()
	{
		_context->RegisterFactory<Level>();
		_context->RegisterFactory<LevelChunk>();
		_context->RegisterFactory<LevelData>();
	}

	void World::OnInit()
	{
		auto cache = _context->GetModule<ResourceCache>();
		cache->AddLoader(new LevelDataLoader(_context));
	}

}