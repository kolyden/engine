#pragma once
#include "uutKeycode.h"

namespace uut
{
    struct KeyEvent
    {
        EKeycode _key;
        bool _pressed;
    };
}