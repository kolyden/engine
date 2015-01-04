#pragma once
#include "resource/uutResource.h"
#include "uutVideoDefs.h"

namespace uut
{
	class Geometry;
	class VideoBuffer;

	class UUT_API Model : public Resource
	{
		OBJECT(Model)
	public:
		Model(Context* context);

		bool Create(Geometry* geometry);
		void Clear();

		void Draw() const;

	protected:
		EPrimitiveType _topology;
		SharedPtr<VideoBuffer> _vbuffer;
		SharedPtr<VideoBuffer> _ibuffer;
		uint32_t _vcount;
		uint32_t _icount;
	};
}