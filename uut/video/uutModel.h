#pragma once
#include "resource/uutResource.h"
#include "uutVideoDefs.h"
#include "math/uutMatrix4.h"

namespace uut
{
	class Geometry;
	class VideoBuffer;
	class Texture;

	class UUT_API Model : public Resource
	{
		OBJECT(Model)
	public:
		Model(Context* context);

		bool Create(Geometry* geometry);
		void Clear();

		void SetTexture(Texture* texture);
		Texture* GetTexture() const;

		void Draw(const Matrix4f& transform) const;

	protected:
		EPrimitiveType _topology;
		SharedPtr<VideoBuffer> _vbuffer;
		SharedPtr<VideoBuffer> _ibuffer;
		SharedPtr<Texture> _texture;
		uint32_t _vcount;
		uint32_t _icount;
	};
}