#include "World.h"
#include "core/uutContext.h"
#include "resource/uutResourceCache.h"
#include "Level.h"
#include "LevelChunk.h"
#include "LevelLoader.h"

namespace uut
{
	World::World(Context* context)
		: Module(context)
	{
	}

	bool World::LoadLevel(const String& path)
	{
		auto cache = _context->GetModule<ResourceCache>();
		auto level = cache->Load<Level>(path);
		if (level == 0)
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
	}

	void World::OnInit()
	{
		auto cache = _context->GetModule<ResourceCache>();
		cache->AddLoader(new LevelLoader(_context));
	}

}