#include "uutTime.h"

namespace uut
{
	Time::Time(Context* context)
		: Module(context)
		, _frameNumber(0)
		, _startTime(0)
		, _lastTime(0)
		, _delta(0)
		, _elapsed(0)
	{
	}

	float Time::GetDelta() const
	{
		return _delta;
	}

	float Time::GetElapsed() const
	{
		return _elapsed;
	}

	//////////////////////////////////////////////////////////////////////////
	void Time::OnInit()
	{
		_startTime = SDL_GetTicks();
		_lastTime = _startTime;
	}

	void Time::NextFrame()
	{
		_frameNumber++;
		const unsigned int curTime = SDL_GetTicks();
		_delta = 0.001f * (curTime - _lastTime);
		_elapsed += _delta;
		_lastTime = curTime;
	}
}