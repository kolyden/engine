#pragma once
#include "core/uutModule.h"

namespace uut
{
	class UUT_API Time : public Module
	{
		OBJECT(Time)
	public:
		Time(Context* context);

		float GetDelta() const;
		float GetElapsed() const;

	protected:
		unsigned int _startTime;
		unsigned int _lastTime;
		unsigned int _frameNumber;

		float _delta;
		float _elapsed;

		virtual void OnInit() override;
		void NextFrame();

		friend class Application;
	};
}