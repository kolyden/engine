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

		List<Vector3> verts;
		List<uint32_t> colors;
		for (auto i = 0; i < count; i++)
		{
			const int index = i * 3;
			verts.Add(Vector3(
				mesh.positions[index + 0],
				mesh.positions[index + 1],
				mesh.positions[index + 2]));
			colors.Add(color);
		}

		List<Vector3> normals;
		for (auto i = 0; i < count; i++)
		{
			const int index = i * 3;
			normals.Add(Vector3(
				mesh.normals[index + 0],
				mesh.normals[index + 1],
				mesh.normals[index + 2]));
		}

		List<Vector2> tex;
		for (auto i = 0; i < count; i++)
		{
			const int index = i * 2;
			tex.Add(Vector2(
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

		/*
		List<String> arr, arr2;

		List<Vector3> temp_verts;
		List<Vector3> temp_normals;
		List<Vector2> temp_uv;
		List<unsigned int> vIndex, uvIndex, nIndex;

		String word, line;

		while (1)
		{
			word = ReadWord(source);

			if (source.IsEof())
				break;

			line = ReadLine(source);
			if (word.Equals("#", true))
			{
				continue;
			}
			else if (word.Equals("v", true))
			{
				arr = line.Split(' ');
				if (arr.Count() == 3)
				{
					temp_verts.Add(Vector3(
						arr[0].ToFloat(),
						arr[1].ToFloat(),
						arr[2].ToFloat()));
				}
			}
			else if (word.Equals("vt", true))
			{
				arr = line.Split(' ');
				if (arr.Count() == 2)
				{
					temp_uv.Add(Vector2(
						arr[0].ToFloat(),
						arr[1].ToFloat()));
				}
			}
			else if (word.Equals("vn", true))
			{
				arr = line.Split(' ');
				if (arr.Count() == 3)
				{
					temp_normals.Add(Vector3(
						arr[0].ToFloat(),
						arr[1].ToFloat(),
						arr[2].ToFloat()));
				}
			}
			else if (word.Equals("f", true))
			{
				arr = line.Split(' ');
				if (arr.Count() == 3)
				{
					arr2 = arr[0].Split('/');
					if (arr2.Count() == 3)
					{
						vIndex[0] = arr2[0].ToInt();
						vIndex[1] = arr2[1].ToInt();
						vIndex[2] = arr2[2].ToInt();
					}

					arr2 = arr[1].Split('/');
					if (arr2.Count() == 3)
					{
						uvIndex[0] = arr2[0].ToInt();
						uvIndex[1] = arr2[1].ToInt();
						uvIndex[2] = arr2[2].ToInt();
					}

					arr2 = arr[2].Split('/');
					if (arr2.Count() == 3)
					{
						nIndex[0] = arr2[0].ToInt();
						nIndex[1] = arr2[1].ToInt();
						nIndex[2] = arr2[2].ToInt();
					}
				}
			}
		}

		auto geometry = SharedPtr<Geometry>(new Geometry(_context));

		List<Vector3> verts;
		for (int i = 0; i < vIndex.Count(); i++)
			verts.Add(temp_verts[vIndex[i] - 1]);

		List<Vector3> normals;
		for (int i = 0; i < nIndex.Count(); i++)
			normals.Add(temp_normals[nIndex[i] - 1]);

		List<Vector2> uv;
		for (int i = 0; i < uvIndex.Count(); i++)
			uv.Add(temp_uv[uvIndex[i] - 1]);

		geometry->SetVertices(verts);
		geometry->SetNormals(normals);
		geometry->SetUV(uv);

		auto model = SharedPtr<Model>(new Model(_context));
		if (model->Create(geometry))
			return DynamicCast<Resource>(model);

		return SharedPtr<Resource>::EMPTY;
		*/
	}
}