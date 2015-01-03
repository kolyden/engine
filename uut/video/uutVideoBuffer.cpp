#include "uutVideoBuffer.h"
#include "core/uutContext.h"
#include "uutVideo.h"

namespace uut
{
    VideoBuffer::VideoBuffer(Context* context)
        : Object(context)
        , VideoObject(_context->GetModule<Video>())
        , _dataType(BUFFER_VERTEX)
        , _flags()
        , _size(0)
        , _buffer(0)
        , _target(0)
    {
    }

    VideoBuffer::~VideoBuffer()
    {
        Clear();
    }

    bool VideoBuffer::Create(EBufferType type, unsigned size, unsigned flags, const void* data)
    {
        if ((_dataType == type) && (_flags == flags) && (_size == size))
            return true;

        if (size == 0)
            return false;

        switch (type)
        {
        case BUFFER_VERTEX: _target = GL_ARRAY_BUFFER; break;
        case BUFFER_INDEX: _target = GL_ELEMENT_ARRAY_BUFFER; break;
        }

        _size = size;

        glGenBuffers(1, &_buffer);
        if (!CheckGLError("RenderBuffer glGenBuffers"))
            return false;

        if (!Bind())
            return false;

        unsigned usage = GL_STATIC_DRAW;
        if (flags & BUFFERFLAG_DYNAMIC)
            usage = GL_DYNAMIC_DRAW;

        glBufferData(_target, _size, data, usage);
        CheckGLError("RenderBuffer glBufferData");

        Unbind();
        return true;
    }

    void VideoBuffer::Clear()
    {
        if (_buffer == 0)
            return;

        _size = 0;
        ::glDeleteBuffers(1, &_buffer);
        _buffer = 0;
    }

    void* VideoBuffer::LockData()
    {
        if (_buffer == 0)
            return 0;

		// glMapBufferOES can be unsupported on some platform, check glGetString GL_OES_mapbuffer extension

		/*if (_render->checkExtension(CRenderGLES::EXTENSION_MAPBUFFER))
		{
		glBindBuffer(GL_ARRAY_BUFFER, _buffer);
		return glMapBufferOES(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);
		}*/

		return 0;
    }

    void VideoBuffer::UnlockData()
    {
        //glUnmapBufferOES(target);
        //glBindBuffer(target, 0);
    }

    bool VideoBuffer::UpdateData(unsigned offset, unsigned size, const void* data)
    {
        if (!Bind())
            return false;

        glBufferSubData(_target, offset, size, data);
        CheckGLError("RenderBuffer updateData");

        Unbind();

        return true;
    }

    //////////////////////////////////////////////////////////////////////////
    bool VideoBuffer::Bind()
    {
        if (_buffer == 0)
            return false;

        ::glBindBuffer(_target, _buffer);            
        if (!CheckGLError("VideoBuffer Bind"))
            return false;

        return true;
    }

    void VideoBuffer::Unbind()
    {
        ::glBindBuffer(_target, 0);
    }
}