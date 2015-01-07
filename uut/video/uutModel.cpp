#include "uutModel.h"
#include "core/uutContext.h"
#include "uutVideo.h"
#include "uutGeometry.h"
#include "uutVideoBuffer.h"
#include "uutVertex3.h"
#include "uutTexture.h"

namespace uut
{
	Model::Model(Context* context)
		: Resource(context)
		, _topology(PRIMITIVE_TRIANGLES)
		, _vcount(0)
		, _icount(0)
	{
	}

	bool Model::Create(Geometry* geometry)
	{
		if (geometry == 0)
			return false;

		const auto& verts = geometry->GetVertices();
		if (verts.Empty())
			return false;

		Clear();

		const auto& normals = geometry->GetNormals();
		const auto& uv = geometry->GetUV();
		const auto& colors = geometry->GetColors32();
		const auto& indexes = geometry->GetIndexes();

		_vcount = verts.Count();
		auto data = new Vertex3[_vcount];
		for (uint32_t i = 0; i < _vcount; i++)
		{
			data[i].pos = verts[i];
			data[i].tex = uv[i];
			data[i].color = colors[i];
		}
		_vbuffer = new VideoBuffer(_context);
		_vbuffer->Create(BUFFER_VERTEX, Vertex3::DECLARE.size * _vcount, BUFFERFLAG_STATIC, data);
		delete[] data;

		if (!indexes.Empty())
		{
			_icount = indexes.Count();
			_ibuffer = new VideoBuffer(_context);
			_ibuffer->Create(BUFFER_INDEX,
				sizeof(uint16_t) * _icount,
				BUFFERFLAG_STATIC, indexes.GetData());
		}

		_topology = geometry->GetTopology();

		return true;
	}

	void Model::Clear()
	{
		_vbuffer = 0;
		_ibuffer = 0;
		_vcount = 0;
		_icount = 0;
	}

	void Model::SetTexture(Texture* texture)
	{
		_texture = texture;
	}

	Texture* Model::GetTexture() const
	{
		return _texture;
	}

	void Model::Draw(const Matrix4f& transform) const
	{
		if (_vbuffer == 0)
			return;

		auto video = _context->GetModule<Video>();

		if (!video->BindBuffer(_vbuffer, Vertex3::DECLARE.size, Vertex3::DECLARE.types, Vertex3::DECLARE.count))
			return;

		glPushMatrix();
		glMultMatrixf(transform.GetData());

		video->BindTexture(_texture);
		if (_ibuffer && video->BindBuffer(_ibuffer, 0, 0, 0))
		{
			video->DrawIndexedPrimitives(_topology, _icount, VALUE_USHORT);
			video->UnbindBuffer(_ibuffer, 0, 0);
		}
		else video->DrawPrimitives(_topology, _vcount, 0);
		glPopMatrix();

		video->UnbindBuffer(_vbuffer, Vertex3::DECLARE.types, Vertex3::DECLARE.count);
	}

}