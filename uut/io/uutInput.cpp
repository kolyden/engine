#include "uutInput.h"
#include "core/uutContext.h"
#include "core/uutApplication.h"

namespace uut
{
    Input::Input(Context* context)
        : Module(context)
    {
        for (int i = 0; i < MAX_KEYCODE; i++)
            _keycode[i] = false;

        UpdateState();
    }

    void Input::PullEvents()
    {
        SDL_Event evt;
        while(SDL_PollEvent(&evt))
        {
            SDL_PumpEvents();
            HandleSDLEvent(evt);
        }
    }

    void Input::HandleSDLEvent(const SDL_Event& evt)
    {
        switch (evt.type)
        {
        case SDL_MOUSEMOTION:
            _mousePos.x = evt.motion.x;
            _mousePos.y = evt.motion.y;
            break;

        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            break;

        case SDL_KEYDOWN:
        case SDL_KEYUP:
            _keycode[evt.key.keysym.scancode] = (evt.key.state == SDL_PRESSED);
            break;
        }
    }

    //////////////////////////////////////////////////////////////////////////
    void Input::UpdateState()
    {
        int count;
        const Uint8* keys = SDL_GetKeyboardState(&count);
        count = Math::Min(MAX_KEYCODE, count);
        for (int i = 0; i < count; i++)
            _keycode[i] = (keys[i] ? true : false);
    }

}