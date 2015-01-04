#include "uutModel.h"
#include "core/uutContext.h"
#include "uutVideo.h"
#include "uutGeometry.h"
#include "uutVideoBuffer.h"
#include "uutVertex3.h"

namespace uut
{
	Model::Model(Context* context)
		: Resource(context)
		, _topology(PRIMITIVE_TRIANGLES)
		, _count(0)
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

		_count = verts.Count();
		auto data = new Vertex3[_count];
		for (int i = 0; i < _count; i++)
		{
			data[i].pos = verts[i];
			data[i].tex = uv[i];
			data[i].color = colors[i];
		}
		_vbuffer = new VideoBuffer(_context);
		_vbuffer->Create(BUFFER_VERTEX, Vertex3::SIZE * _count, BUFFERFLAG_STATIC, data);
		delete[] data;

		if (!indexes.Empty())
		{
			_ibuffer = new VideoBuffer(_context);
			_ibuffer->Create(BUFFER_INDEX,
				sizeof(uint16_t)* indexes.Count(),
				BUFFERFLAG_STATIC, indexes.GetData());
		}

		_topology = geometry->GetTopology();

		return true;
	}

	void Model::Clear()
	{
		_vbuffer = 0;
		_ibuffer = 0;
	}

	void Model::Draw() const
	{
		if (_vbuffer == 0)
			return;

		auto video = _context->GetModule<Video>();

		if (!video->BindBuffer(_vbuffer, Vertex3::SIZE, Vertex3::DECLARE, Vertex3::DECLARE_COUNT))
			return;

		if (_ibuffer)
		{
			video->BindBuffer(_ibuffer, 0, 0, 0);
			video->DrawIndexedPrimitives(PRIMITIVE_TRIANGLES, 6, VALUE_UBYTE);
			video->UnbindBuffer(_ibuffer, 0, 0);
		}
		else video->DrawPrimitives(_topology, _count, 0);

		video->UnbindBuffer(_vbuffer, Vertex3::DECLARE, Vertex3::DECLARE_COUNT);
	}

}