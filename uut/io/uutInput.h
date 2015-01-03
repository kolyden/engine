#pragma once
#include "core/uutModule.h"
#include "math/uutVector2.h"
#include "uutKeycode.h"
#include "uutInputEvent.h"

namespace uut
{
    class UUT_API Input : public Module
    {
        OBJECT(Input);
    public:
        Input(Context* context);

        void PullEvents();

        const Vector2i& GetMousePos() const { return _mousePos; }

        inline bool IsKey(EKeycode key) const { return _keycode[key]; }
        inline bool IsKeys(EKeycode key1, EKeycode key2) const { return (IsKey(key1) && IsKey(key2)); }

    protected:
		Vector2i _mousePos;
        bool _keycode[MAX_KEYCODE];

		void HandleSDLEvent(const SDL_Event& evt);
        void UpdateState();

		friend class Application;
    };
}