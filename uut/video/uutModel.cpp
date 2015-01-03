#include "uutModel.h"
#include "video/uutGeometry.h"

namespace uut
{
	Model::Model(Context* context)
		: Resource(context)
	{
	}

	void Model::SetGeometry(Geometry* geometry)
	{
		_geometry = geometry;
	}

	Geometry* Model::GetGeometry() const
	{
		return _geometry;
	}

}