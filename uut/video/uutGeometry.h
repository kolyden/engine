#pragma once
#include "core/uutObject.h"
#include "video/uutVertex2.h"
#include "container/uutList.h"

namespace uut
{
	class VideoBuffer;

	class UUT_API Geometry : public Object
	{
		OBJECT(Geometry)
	public:
		Geometry(Context* context);

	protected:
		SharedPtr<VideoBuffer> _vbuffer;
		SharedPtr<VideoBuffer> _ibuffer;
	};
}