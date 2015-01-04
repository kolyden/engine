#pragma once
#include "core/uutObject.h"
#include "uutSerializer.h"
#include "uutDeserializer.h"

struct SDL_RWops;

namespace uut
{
    enum class FileMode
    {
        Read = 0,
        Write,
        ReadWrite
    };

    class UUT_API File : public Object, public Serializer, public Deserializer
    {
        OBJECT(File);
    public:
        File(Context* context);
        virtual ~File();

        bool Open(const Path& path, FileMode mode = FileMode::Read);
        void Close();

        virtual unsigned Write(const void* data, unsigned size) override;
        virtual unsigned Read(void* data, unsigned size) override;
		virtual Sint64 Seek(Sint64 position) override;

		virtual Sint64 GetPosition() const override;
		virtual Sint64 GetSize() const override;
		virtual bool IsEof() const override;

		virtual const Path& GetPath() const override;

    protected:
        SDL_RWops* _handle;
        Path _path;
		Sint64 _size;
    };
}