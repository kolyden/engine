#pragma once
#include "resource/uutResource.h"

namespace uut
{
	class Geometry;

	class UUT_API Model : public Resource
	{
		OBJECT(Model)
	public:
		Model(Context* context);

		void SetGeometry(Geometry* geometry);
		Geometry* GetGeometry() const;

	protected:
		SharedPtr<Geometry> _geometry;
	};
}