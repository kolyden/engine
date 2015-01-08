#pragma once
#include "core/uutModule.h"

namespace uut
{
	class Level;

	class World : public Module
	{
		OBJECT(World)
	public:
		World(Context* context);

		bool LoadLevel(const String& path);

		void SetLevel(Level* level);
		Level* GetLevel() const;

	protected:
		SharedPtr<Level> _current;

		virtual void OnRegister() override;
		virtual void OnInit() override;
	};
}