#include "uutGeometry.h"
#include "uutVideoBuffer.h"

namespace uut
{
	Geometry::Geometry(Context* context)
		: Object(context)
		, _topology(PRIMITIVE_TRIANGLES)
	{
	}

	void Geometry::Clear()
	{
		_vertices.Clear();
		_normals.Clear();
		_uv.Clear();
		_colors.Clear();
		_indexes.Clear();
	}

	void Geometry::SetTopology(EPrimitiveType type)
	{
		_topology = type;
	}

	uut::EPrimitiveType Geometry::GetTopology() const
	{
		return _topology;
	}

	void Geometry::SetVertices(const List<Vector3f>& vertices)
	{
		_vertices = vertices;
	}

	const List<Vector3f>& Geometry::GetVertices() const
	{
		return _vertices;
	}

	void Geometry::SetNormals(const List<Vector3f>& normals)
	{
		_normals = normals;
	}

	const List<Vector3f>& Geometry::GetNormals() const
	{
		return _normals;
	}

	void Geometry::SetUV(const List<Vector2f>& uv)
	{
		_uv = uv;
	}

	const List<Vector2f>& Geometry::GetUV() const
	{
		return _uv;
	}

	void Geometry::SetColors(const List<Color>& colors)
	{
		_colors.Clear();
		for (int i = 0; i < colors.Count(); i++)
			_colors.Add(colors[i].ToUint());
	}

	List<Color> Geometry::GetColors() const
	{
		List<Color> ret;
		for (int i = 0; i < _colors.Count(); i++)
			ret.Add(Color(_colors[i]));

		return ret;
	}

	void Geometry::SetColors32(const List<uint32_t>& colors)
	{
		_colors = colors;
	}

	const List<uint32_t>& Geometry::GetColors32() const
	{
		return _colors;
	}

	void Geometry::SetIndexes(const List<uint16_t>& indexes)
	{
		_indexes = indexes;
	}

	const List<uint16_t>& Geometry::GetIndexes() const
	{
		return _indexes;
	}

}