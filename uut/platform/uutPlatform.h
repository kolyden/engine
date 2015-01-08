#pragma once
#include "core/uutModule.h"
#include "io/uutPath.h"

namespace uut
{
	class UUT_API Platform : public Module
	{
		OBJECT(Platform)
	public:
		Platform(Context* context);

		String GetPlatformName() const;
		const String& GetBasePath() const;

	protected:
		String _basePath;

		virtual void OnRegister() override;
		virtual void OnUnregister() override;
	};
}