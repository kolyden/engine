#include "uutModelLoaderOBJ.h"
#include "core/uutDebug.h"
#include "video/uutModel.h"
#include "video/uutGeometry.h"
#include "io/uutDeserializer.h"
#include "tiny_obj_loader.h"

namespace uut
{
	ModelLoaderOBJ::ModelLoaderOBJ(Context* context)
		: ResourceLoader(context)
	{
	}

	const HashString& ModelLoaderOBJ::GetResourceType() const
	{
		return Model::GetTypeStatic();
	}

	bool ModelLoaderOBJ::CanLoad(const Path& path) const
	{
		return path.IsExtension("obj");
	}

	static String ReadLine(Deserializer& source)
	{
		String ret;
		char c;
		while (source.Read(&c, 1) == 1 && c != '\n')
		{
			if (c != '\r')
				ret += c;
		}

		return ret;
	}

	static String ReadWord(Deserializer& source)
	{
		String ret;
		char c;
		while (source.Read(&c, 1) == 1 && c != ' ')
			ret += c;

		return ret;
	}

	SharedPtr<Resource> ModelLoaderOBJ::Load(Deserializer& source)
	{
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;

		auto err = tinyobj::LoadObj(shapes, materials, source.GetPath().ToString().GetData());
		if (!err.empty())
		{
			Debug::LogError("OBJ load error - %s", err.c_str());
			return SharedPtr<Resource>::EMPTY;
		}

		const tinyobj::mesh_t& mesh = shapes[0].mesh;
		const auto count = mesh.positions.size() / 3;

		const uint32_t color = Color::WHITE.ToUint();

		List<Vector3f> verts;
		List<uint32_t> colors;
		for (auto i = 0; i < count; i++)
		{
			const int index = i * 3;
			verts.Add(Vector3f(
				mesh.positions[index + 0],
				mesh.positions[index + 1],
				mesh.positions[index + 2]));
			colors.Add(color);
		}

		List<Vector3f> normals;
		for (auto i = 0; i < count; i++)
		{
			const int index = i * 3;
			normals.Add(Vector3f(
				mesh.normals[index + 0],
				mesh.normals[index + 1],
				mesh.normals[index + 2]));
		}

		List<Vector2f> tex;
		for (auto i = 0; i < count; i++)
		{
			const int index = i * 2;
			tex.Add(Vector2f(
				mesh.texcoords[index + 0],
				mesh.texcoords[index + 1]));
		}

		List<uint16_t> indexes;
		for (auto i = 0; i < mesh.indices.size(); i++)
			indexes.Add(mesh.indices[i]);

		auto geometry = SharedPtr<Geometry>(new Geometry(_context));

		geometry->SetVertices(verts);
		geometry->SetNormals(normals);
		geometry->SetUV(tex);
		geometry->SetColors32(colors);
		geometry->SetIndexes(indexes);

		auto model = SharedPtr<Model>(new Model(_context));
		if (model->Create(geometry))
			return DynamicCast<Resource>(model);

		return SharedPtr<Resource>::EMPTY;
	}
}