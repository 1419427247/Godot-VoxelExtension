#include "mesh_preset.h"

void MeshPreset::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_mesh", "value"), &MeshPreset::set_mesh);
	ClassDB::bind_method(D_METHOD("get_mesh"), &MeshPreset::get_mesh);

	ClassDB::bind_method(D_METHOD("set_materials", "value"), &MeshPreset::set_materials);
	ClassDB::bind_method(D_METHOD("get_materials"), &MeshPreset::get_materials);

	ClassDB::bind_static_method("MeshPreset", D_METHOD("instantiate", "uuid", "name", "mesh"), &MeshPreset::instantiate);

	ClassDB::add_property("MeshPreset", PropertyInfo(Variant::OBJECT, "mesh", PROPERTY_HINT_RESOURCE_TYPE, "Mesh"), "set_mesh", "get_mesh");
	ClassDB::add_property("MeshPreset", PropertyInfo(Variant::ARRAY, "material", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::INT) + "/" + String::num_int64(PROPERTY_HINT_NONE) + ":"), "set_materials", "get_materials");
}

MeshPreset::MeshPreset() {

}
MeshPreset::~MeshPreset() {

}

void MeshPreset::set_mesh(const Ref<Mesh>& value) {
	mesh = value;
}

Ref<Mesh> MeshPreset::get_mesh() const
{
	return mesh;
}

void MeshPreset::set_materials(const TypedArray<int>& value) {
	materials = value;
}

TypedArray<int> MeshPreset::get_materials() const {
	return materials;
}

void MeshPreset::build_mesh(const Array& arrays, const int surface_index, const Vector3& position, const Vector3& rotation)
{
	Array mesh_arrays = mesh->surface_get_arrays(surface_index);

	Array array_vertex = arrays[Mesh::ARRAY_VERTEX];
	Array array_normal = arrays[Mesh::ARRAY_NORMAL];
	Array array_tex_uv = arrays[Mesh::ARRAY_TEX_UV];

	PackedVector3Array packed_array_vertex = mesh_arrays[Mesh::ARRAY_VERTEX];
	PackedVector2Array packed_array_tex_uv = mesh_arrays[Mesh::ARRAY_TEX_UV];

	for (size_t i = 0; i < packed_array_vertex.size(); i++)
	{
		packed_array_vertex[i] = rotate_vertex(packed_array_vertex[i], rotation) + position;
	}

	if (mesh_arrays[Mesh::ARRAY_INDEX].get_type() == Variant::Type::PACKED_INT32_ARRAY)
	{
		PackedInt32Array packed_array_index = mesh_arrays[Mesh::ARRAY_INDEX];
		for (size_t i = 0; i < packed_array_index.size(); i += 3)
		{
			Vector3 vertex_a = packed_array_vertex[packed_array_index[i]];
			Vector3 vertex_b = packed_array_vertex[packed_array_index[i + 1]];
			Vector3 vertex_c = packed_array_vertex[packed_array_index[i + 2]];

			array_vertex.push_back(vertex_a);
			array_vertex.push_back(vertex_b);
			array_vertex.push_back(vertex_c);

			Vector3 normal = get_triangle_normal(vertex_a, vertex_b, vertex_c);

			array_normal.push_back(normal);
			array_normal.push_back(normal);
			array_normal.push_back(normal);
		}
		for (size_t i = 0; i < packed_array_index.size(); i++)
		{
			array_tex_uv.push_back(packed_array_tex_uv[packed_array_index[i]]);
		}
	}
	else {
		for (size_t i = 0; i < packed_array_vertex.size(); i += 3)
		{
			Vector3 vertex_a = packed_array_vertex[i];
			Vector3 vertex_b = packed_array_vertex[i + 1];
			Vector3 vertex_c = packed_array_vertex[i + 2];

			array_vertex.push_back(vertex_a);
			array_vertex.push_back(vertex_b);
			array_vertex.push_back(vertex_c);

			Vector3 normal = get_triangle_normal(vertex_a, vertex_b, vertex_c);

			array_normal.push_back(normal);
			array_normal.push_back(normal);
			array_normal.push_back(normal);
		}
		for (size_t i = 0; i < packed_array_tex_uv.size(); i++)
		{
			array_tex_uv.push_back(packed_array_tex_uv[i]);
		}
	}
}

Ref<MeshPreset> MeshPreset::instantiate(const String& uuid, const String& name, const Ref<Mesh>& mesh, Array materials) {
	Ref<MeshPreset> mesh_preset;
	mesh_preset.instantiate();
	mesh_preset->uuid = uuid;
	mesh_preset->name = name;
	mesh_preset->mesh = mesh;
	mesh_preset->materials = materials;
	return mesh_preset;
}

Vector3 MeshPreset::rotate_vertex(const Vector3& vertex, const Vector3i& rotation)
{
	Vector3 result = vertex;
	result = result.rotated(Vector3(1, 0, 0), UtilityFunctions::deg_to_rad(rotation.x));
	result = result.rotated(Vector3(0, 1, 0), UtilityFunctions::deg_to_rad(rotation.y));
	result = result.rotated(Vector3(0, 0, 1), UtilityFunctions::deg_to_rad(rotation.z));
	return result;
}

Vector3 MeshPreset::get_triangle_normal(const Vector3& a, const Vector3& b, const Vector3& c)
{
	return (c - a).cross(b - a);
}