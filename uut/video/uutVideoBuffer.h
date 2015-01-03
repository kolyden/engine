#pragma once
#include "uutVideoDefs.h"
#include "core/uutObject.h"
#include "uutVideoObject.h"

namespace uut
{
    class UUT_API VideoBuffer : public Object, public VideoObject
	{
        OBJECT(VideoBuffer);
	public:
        VideoBuffer(Context* context);
        virtual ~VideoBuffer();

        bool Create(EBufferType type, unsigned size, unsigned flags = 0, const void* data = 0);
        void Clear();

		EBufferType GetDataType() const { return _dataType; }
		unsigned GetFlags() const { return _flags; }
		unsigned GetSize() const { return _size; }

		void* LockData();
		void UnlockData();
		bool UpdateData(unsigned offset, unsigned size, const void* data);

    protected:
        EBufferType _dataType;
        unsigned _size;
        unsigned _buffer;
        unsigned _target;
        unsigned _flags;

        bool Bind();
        void Unbind();

        friend class Video;
	};
}
