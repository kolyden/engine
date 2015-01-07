#include "uutDeserializer.h"

namespace uut
{
    Deserializer::Deserializer()
    {
    }

    Deserializer::~Deserializer()
    {
    }

	uut::String Deserializer::ReadLine()
	{
		String ret;
		char c;
		while (Read(&c, 1) == 1 && c != '\n')
		{
			if (c != '\r')
				ret += c;
		}

		return ret;
	}

    //////////////////////////////////////////////////////////////////////////
    static Sint64 SDLCALL funcRWopsSize(struct SDL_RWops * context)
    {
        Deserializer* file = (Deserializer*)context->hidden.unknown.data1;
        return file->GetSize();
    }

    static Sint64 SDLCALL funcRWopsSeek(struct SDL_RWops * context,
        Sint64 offset,int whence)
    {
        auto file = (Deserializer*)context->hidden.unknown.data1;
        switch (whence)
        {
        case RW_SEEK_SET:
            return file->Seek(offset);
            break;

        case RW_SEEK_CUR:
            return file->Seek(file->GetPosition() + offset);
            break;

        case RW_SEEK_END:
            return file->Seek(file->GetSize() - offset);
            break;
        }

        return -1;
    }

    static size_t SDLCALL funcRWopsRead(struct SDL_RWops * context,
        void *ptr, size_t size, size_t maxnum)
    {
        auto file = (Deserializer*)context->hidden.unknown.data1;
        size_t count = 0;
        for (size_t i = 0; i < maxnum; i++)
        {
            void* buffer = &(((char*)ptr)[count * size]);
            if (file->Read(buffer , size) != size)
                break;

            count++;
        }

        return count;
    }

    static size_t SDLCALL funcRWopsWrite(struct SDL_RWops * context,
        const void *ptr, size_t size, size_t num)
    {
        //         Deserializer* file = (Deserializer*)context->hidden.unknown.data1;
        return 0;
    }

    static int SDLCALL funcRWopsClose(struct SDL_RWops * context)
    {
        //         Deserializer* file = (Deserializer*)context->hidden.unknown.data1;
        return 0;
    }
	
    SDL_RWops* UUT_API CreatReadRWops(Deserializer& deserializer)
    {
        SDL_RWops* ops = SDL_AllocRW();

        ops->hidden.unknown.data1 = (void*)&deserializer;
        ops->size = &funcRWopsSize;
        ops->seek = &funcRWopsSeek;
        ops->read = &funcRWopsRead;
        ops->write = &funcRWopsWrite;
        ops->close = &funcRWopsClose;

        return ops;
    }
}
