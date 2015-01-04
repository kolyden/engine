#include "uutFile.h"

namespace uut
{
    File::File(Context* context)
        : Object(context)
        , _handle(0)
    {
    }

    File::~File()
    {
		Close();
    }

	bool File::Open(const Path& path, FileMode mode /* = FileMode::Read */)
    {
        Close();

		const String fileName = path.ToString();
        switch (mode)
        {
		case FileMode::Read:_handle = SDL_RWFromFile(fileName.GetData(), "r"); break;
		case FileMode::Write:_handle = SDL_RWFromFile(fileName.GetData(), "w"); break;
		case FileMode::ReadWrite:_handle = SDL_RWFromFile(fileName.GetData(), "a"); break;
        }
        
        if (_handle == 0)
            return false;

        _path = path;
		_position = 0;
		const auto size = SDL_RWsize(_handle);
		if (size > 0)
			_size = size;
        return true;
    }

    void File::Close()
    {
		if (_handle == 0)
			return;

		SDL_RWclose(_handle);
		SDL_FreeRW(_handle);
		_handle = 0;
		_position = 0;
		_size = 0;
    }

    unsigned File::Write(const void* data, unsigned size)
    {
        if (!_handle)
            return 0;

        return SDL_RWwrite(_handle, data, size, 1);
    }

    unsigned File::Read(void* data, unsigned size)
    {
        if (!_handle)
            return 0;

        const auto ret = SDL_RWread(_handle, data, 1, size);
		_position += ret;
		return ret;
    }

    unsigned File::Seek(unsigned position)
    {
        if (!_handle)
            return 0;

        const Sint64 ret = SDL_RWseek(_handle, position, RW_SEEK_SET);
        return 0;
    }

	const Path& File::GetPath() const
	{
		return _path;
	}

}