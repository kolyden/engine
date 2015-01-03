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

		void SetVideoBuffer(VideoBuffer* buffer);
		VideoBuffer* GetVideoBuffer() const;

		void SetIndexBuffer(VideoBuffer* buffer);
		VideoBuffer* GetIndexBuffer() const;

	protected:
		SharedPtr<VideoBuffer> _vbuffer;
		SharedPtr<VideoBuffer> _ibuffer;
	};
}