#include "mesh_preset.h"
#include "basics_preset.h"

void MeshPreset::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_mesh", "value"), &MeshPreset::set_mesh);
	ClassDB::bind_method(D_METHOD("get_mesh"), &MeshPreset::get_mesh);

	ClassDB::bind_method(D_METHOD("set_materials", "value"), &MeshPreset::set_materials);
	ClassDB::bind_method(D_METHOD("get_materials"), &MeshPreset::get_materials);

	ClassDB::bind_static_method("MeshPreset", D_METHOD("instantiate", "name", "mesh"), &MeshPreset::instantiate);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "mesh", PROPERTY_HINT_RESOURCE_TYPE, "Mesh"), "set_mesh", "get_mesh");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "material", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::INT) + "/" + String::num_int64(PROPERTY_HINT_NONE) + ":"), "set_materials", "get_materials");
}

MeshPreset::MeshPreset() {

}
MeshPreset::~MeshPreset() {

}

void MeshPreset::set_mesh(const Ref<Mesh>& value) {
	mesh = value;
	if (value.is_null())
	{
		return;
	}
	mesh_arrays.resize(mesh->get_surface_count());
	for (size_t i = 0; i < mesh->get_surface_count(); i++)
	{
		Array mesh_surface_arrays = mesh->surface_get_arrays(i);

		PackedVector3Array packed_array_vertex = mesh_surface_arrays[Mesh::ARRAY_VERTEX];
		PackedVector2Array packed_array_tex_uv = mesh_surface_arrays[Mesh::ARRAY_TEX_UV];
		PackedInt32Array packed_array_index = mesh_surface_arrays[Mesh::ARRAY_INDEX];

		Array surface;
		surface.resize(Mesh::ARRAY_MAX);

		Array surface_vertex_array;
		Array surface_normal_array;
		Array surface_tex_uv_array;

		for (size_t i = 0; i < packed_array_index.size(); i += 3)
		{
			Vector3 vertex_a = packed_array_vertex[packed_array_index[i]];
			Vector3 vertex_b = packed_array_vertex[packed_array_index[i + 1]];
			Vector3 vertex_c = packed_array_vertex[packed_array_index[i + 2]];

			surface_vertex_array.push_back(vertex_a);
			surface_vertex_array.push_back(vertex_b);
			surface_vertex_array.push_back(vertex_c);

			Vector3 normal = Plane(vertex_a, vertex_b, vertex_c).get_normal();

			surface_normal_array.push_back(normal);
			surface_normal_array.push_back(normal);
			surface_normal_array.push_back(normal);

			surface_tex_uv_array.push_back(packed_array_tex_uv[packed_array_index[i]]);
			surface_tex_uv_array.push_back(packed_array_tex_uv[packed_array_index[i + 1]]);
			surface_tex_uv_array.push_back(packed_array_tex_uv[packed_array_index[i + 2]]);
		}
		surface[Mesh::ARRAY_VERTEX] = surface_vertex_array;
		surface[Mesh::ARRAY_NORMAL] = surface_normal_array;
		surface[Mesh::ARRAY_TEX_UV] = surface_tex_uv_array;

		mesh_arrays[i] = surface;
	}
	materials.resize(mesh_arrays.size());
}

Ref<Mesh> MeshPreset::get_mesh() const
{
	return mesh;
}

void MeshPreset::set_materials(const TypedArray<int>& value) {
	materials = value;
	materials.resize(mesh_arrays.size());
}

TypedArray<int> MeshPreset::get_materials() {
	return materials;
}

void MeshPreset::build_mesh(const Array& arrays, const int& surface_index, const Vector3& position, const Vector3& rotation)
{
	Array array_vertex = arrays[Mesh::ARRAY_VERTEX];
	Array array_normal = arrays[Mesh::ARRAY_NORMAL];
	Array array_tex_uv = arrays[Mesh::ARRAY_TEX_UV];

	Array surface = mesh_arrays[surface_index];

	Array surface_vertex_array = surface[Mesh::ARRAY_VERTEX];
	Array surface_normal_array = surface[Mesh::ARRAY_NORMAL];
	Array surface_tex_uv_array = surface[Mesh::ARRAY_TEX_UV];
	for (size_t i = 0; i < surface_vertex_array.size(); i++)
	{
		array_vertex.push_back(BasicsPreset::rotate_vertex(surface_vertex_array[i], rotation) + position);
	}
	array_normal.append_array(surface_normal_array);
	array_tex_uv.append_array(surface_tex_uv_array);
}

Ref<MeshPreset> MeshPreset::instantiate(const String& name, const Ref<Mesh>& mesh, Array materials) {
	Ref<MeshPreset> mesh_preset;
	mesh_preset.instantiate();
	mesh_preset->name = name;
	mesh_preset->mesh = mesh;
	mesh_preset->materials = materials;
	return mesh_preset;
}