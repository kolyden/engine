#include "uutGeometry.h"
#include "uutVideoBuffer.h"

namespace uut
{
	Geometry::Geometry(Context* context)
		: Object(context)
	{
	}

	void Geometry::SetVideoBuffer(VideoBuffer* buffer)
	{
		_vbuffer = buffer;
	}

	VideoBuffer* Geometry::GetVideoBuffer() const
	{
		return _vbuffer;
	}

	void Geometry::SetIndexBuffer(VideoBuffer* buffer)
	{
		_ibuffer = buffer;
	}

	VideoBuffer* Geometry::GetIndexBuffer() const
	{
		return _ibuffer;
	}

}