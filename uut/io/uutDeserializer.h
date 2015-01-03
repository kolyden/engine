#pragma once
#include "container/uutString.h"
#include "io/uutPath.h"

namespace uut
{
    class UUT_API Deserializer
    {
    public:
        Deserializer();
        Deserializer(unsigned size);
        virtual ~Deserializer();

        virtual unsigned Read(void* data, unsigned size) = 0;
        virtual unsigned Seek(unsigned position) = 0;
        virtual const Path& GetPath() const = 0;

        unsigned GetPosition() const;
        unsigned GetSize() const;
        bool IsEof() const;

    protected:
        unsigned _position;
        unsigned _size;
    };

    SDL_RWops* UUT_API CreatReadRWops(Deserializer& deserializer);
}
