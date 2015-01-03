#pragma once
#include "core/uutDefine.h"
#include "core/uutPtr.h"

namespace uut
{
	class Video;

	class UUT_API VideoObject
	{
	public:
		VideoObject(Video* video);

	protected:
		SharedPtr<Video> _video;

		bool CheckGLError(const char* message) const;
	};
}