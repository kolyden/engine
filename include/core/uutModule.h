#pragma once
#include "uutObject.h"

namespace uut
{
	class Module : public Object
	{
		BASEOBJECT(Module)
	public:
		Module(Context* context);

	protected:
		virtual void OnRegister() {}
		virtual void OnUnregister() {}

		friend class Context;
	};
}