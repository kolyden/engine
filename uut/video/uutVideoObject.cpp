#include "uutVideoObject.h"
#include "core/uutDebug.h"
#include "uutVideo.h"

namespace uut
{
	VideoObject::VideoObject(Video* video)
		: _video(video)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	bool VideoObject::CheckGLError(const char* message) const
	{
		const GLenum error = ::glGetError();
		switch (error)
		{
		case GL_NO_ERROR:
			return true;
			break;

		case GL_INVALID_ENUM: Debug::LogError("%s - Invalid Enum", message); break;
		case GL_INVALID_VALUE: Debug::LogError("%s - Invalid Value", message); break;
		case GL_INVALID_OPERATION: Debug::LogError("%s - Invalid Operation", message); break;
		case GL_OUT_OF_MEMORY: Debug::LogError("%s - Out Of Memory", message); break;

		default:
			break;
		}

		return false;

	}

}