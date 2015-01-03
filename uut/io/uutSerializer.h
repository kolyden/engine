#pragma once
#include "core/uutDefine.h"

namespace uut
{
    class Serializer
    {
    public:
        virtual ~Serializer();

        virtual unsigned Write(const void* data, unsigned size) = 0;
    };
}
