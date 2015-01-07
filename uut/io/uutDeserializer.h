#pragma once
#include "container/uutString.h"
#include "io/uutPath.h"

namespace uut
{
    class UUT_API Deserializer
    {
    public:
        Deserializer();
        virtual ~Deserializer();

        virtual unsigned Read(void* data, unsigned size) = 0;
		virtual Sint64 Seek(Sint64 position) = 0;
        virtual const Path& GetPath() const = 0;

		virtual Sint64 GetPosition() const = 0;
		virtual Sint64 GetSize() const = 0;
		virtual bool IsEof() const = 0;

		virtual String ReadLine();
    };

    SDL_RWops* UUT_API CreatReadRWops(Deserializer& deserializer);
}
