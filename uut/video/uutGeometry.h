#pragma once
#include "core/uutObject.h"
#include "container/uutList.h"
#include "math/uutVector2.h"
#include "math/uutVector3.h"
#include "uutColor.h"
#include "uutVideoDefs.h"

namespace uut
{
	class VideoBuffer;

	class UUT_API Geometry : public Object
	{
		OBJECT(Geometry)
	public:
		Geometry(Context* context);

		void Clear();

		void SetTopology(EPrimitiveType type);
		EPrimitiveType GetTopology() const;

		void SetVertices(const List<Vector3f>& vertices);
		const List<Vector3f>& GetVertices() const;

		void SetNormals(const List<Vector3f>& normals);
		const List<Vector3f>& GetNormals() const;

		void SetUV(const List<Vector2f>& uv);
		const List<Vector2f>& GetUV() const;

		void SetColors(const List<Color>& colors);
		List<Color> GetColors() const;

		void SetColors32(const List<uint32_t>& colors);
		const List<uint32_t>& GetColors32() const;

		void SetIndexes(const List<uint16_t>& indexes);
		const List<uint16_t>& GetIndexes() const;

	protected:
		EPrimitiveType _topology;
		List<Vector3f> _vertices;
		List<Vector3f> _normals;
		List<Vector2f> _uv;
		List<uint32_t> _colors;
		List<uint16_t> _indexes;
	};
}