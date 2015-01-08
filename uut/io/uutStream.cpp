#include "uutStream.h"

namespace uut
{
	static Sint64 SDLCALL funcRWopsSize(struct SDL_RWops * context)
	{
		auto stream = (Stream*)context->hidden.unknown.data1;
		return stream->GetLength();
	}

	static Sint64 SDLCALL funcRWopsSeek(struct SDL_RWops * context,
		Sint64 offset, int whence)
	{
		auto stream = (Stream*)context->hidden.unknown.data1;
		switch (whence)
		{
		case RW_SEEK_SET:
			return stream->Seek(offset, SeekOrigin::Begin);
			break;

		case RW_SEEK_CUR:
			return stream->Seek(offset, SeekOrigin::Current);
			break;

		case RW_SEEK_END:
			return stream->Seek(offset, SeekOrigin::End);
			break;
		}

		return -1;
	}

	static size_t SDLCALL funcRWopsRead(struct SDL_RWops * context,
		void *ptr, size_t size, size_t maxnum)
	{
		auto stream = (Stream*)context->hidden.unknown.data1;
		size_t count = 0;
		for (size_t i = 0; i < maxnum; i++)
		{
			void* buffer = ((char*)ptr) + count * size;
			if (stream->Read(buffer, size) != size)
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
// 		auto stream = (Stream*)context->hidden.unknown.data1;
// 		stream->Close();
		return 0;
	}

	SDL_RWops* UUT_API Stream::CreatReadRWops(Stream* source)
	{
		SDL_RWops* ops = SDL_AllocRW();

		ops->hidden.unknown.data1 = source;
		ops->size = &funcRWopsSize;
		ops->seek = &funcRWopsSeek;
		ops->read = &funcRWopsRead;
		ops->write = &funcRWopsWrite;
		ops->close = &funcRWopsClose;

		return ops;
	}
}