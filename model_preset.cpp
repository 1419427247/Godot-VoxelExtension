#include "model_preset.h"

void ModelPreset::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_mesh", "value"), &ModelPreset::set_mesh);
	ClassDB::bind_method(D_METHOD("get_mesh"), &ModelPreset::get_mesh);

	ClassDB::bind_method(D_METHOD("set_materials", "value"), &ModelPreset::set_materials);
	ClassDB::bind_method(D_METHOD("get_materials"), &ModelPreset::get_materials);

	ClassDB::bind_static_method("ModelPreset", D_METHOD("instantiate", "name", "mesh"), &ModelPreset::instantiate);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "mesh", PROPERTY_HINT_RESOURCE_TYPE, "Mesh"), "set_mesh", "get_mesh");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "material", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::INT) + "/" + String::num_int64(PROPERTY_HINT_NONE) + ":"), "set_materials", "get_materials");
}

ModelPreset::ModelPreset() {
	filter = 0b10;
}
ModelPreset::~ModelPreset() {

}

void ModelPreset::set_mesh(const Ref<Mesh>& value) {
	mesh = value;
	if (mesh.is_null())
	{
		materials.clear();
		return;
	}

	mesh_data_memorandum.clear();
	mesh_data_memorandum.resize(24 * 24 * 24);

	Array surfaces = Array();
	surfaces.resize(mesh->get_surface_count());
	materials.resize(surfaces.size());
	for (int i = 0; i < surfaces.size(); i++)
	{
		Array mesh_surface_arrays = mesh->surface_get_arrays(i);

		PackedVector3Array packed_array_vertex = mesh_surface_arrays[Mesh::ARRAY_VERTEX];
		PackedVector2Array packed_array_tex_uv = mesh_surface_arrays[Mesh::ARRAY_TEX_UV];
		PackedInt32Array packed_array_index = mesh_surface_arrays[Mesh::ARRAY_INDEX];

		Array surface = Array();
		surface.resize(Mesh::ARRAY_MAX);

		Array surface_vertex_array;
		Array surface_normal_array;
		Array surface_tex_uv_array;

		if (packed_array_index.size() == 0)
		{
			for (size_t i = 0; i < packed_array_vertex.size(); i += 3)
			{
				Vector3 vertex_a = packed_array_vertex[i];
				Vector3 vertex_b = packed_array_vertex[i + 1];
				Vector3 vertex_c = packed_array_vertex[i + 2];
				surface_vertex_array.push_back(vertex_a);
				surface_vertex_array.push_back(vertex_b);
				surface_vertex_array.push_back(vertex_c);

				Vector3 normal = Plane(vertex_a, vertex_b, vertex_c).get_normal();

				surface_normal_array.push_back(normal);
				surface_normal_array.push_back(normal);
				surface_normal_array.push_back(normal);

				surface_tex_uv_array.push_back(packed_array_tex_uv[i]);
				surface_tex_uv_array.push_back(packed_array_tex_uv[i + 1]);
				surface_tex_uv_array.push_back(packed_array_tex_uv[i + 2]);
			}
		}
		else {
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
		}
		surface[Mesh::ARRAY_VERTEX] = surface_vertex_array;
		surface[Mesh::ARRAY_NORMAL] = surface_normal_array;
		surface[Mesh::ARRAY_TEX_UV] = surface_tex_uv_array;

		surfaces[i] = surface;
	}
	mesh_data_memorandum[0] = surfaces;
}

Ref<Mesh> ModelPreset::get_mesh() const
{
	return mesh;
}

void ModelPreset::set_materials(const TypedArray<int>& value) {
	materials = value;
	if (mesh.is_null())
	{
		materials.clear();
		return;
	}
	materials.resize(((Array)mesh_data_memorandum[0]).size());
}

TypedArray<int> ModelPreset::get_materials() {
	return materials;
}

void ModelPreset::build_mesh(const Array& arrays, const int& surface_index, const Vector3& position, const Vector3& rotation)
{
	int index = (rotation.x / 15 * 24 * 24 + rotation.y / 15 * 24 + rotation.z / 15);

	if (mesh_data_memorandum[index].get_type() == Variant::NIL) {
		Array surfaces = mesh_data_memorandum[0];
		mesh_data_memorandum[index] = Array();
		for (int i = 0; i < surfaces.size(); i++)
		{
			Array surface_vertex_array = ((Array)surfaces[i])[Mesh::ARRAY_VERTEX];
			Array surface_normal_array = ((Array)surfaces[i])[Mesh::ARRAY_NORMAL];
			Array surface_tex_uv_array = ((Array)surfaces[i])[Mesh::ARRAY_TEX_UV];

			Array surface = Array();
			surface.resize(Mesh::ARRAY_MAX);
			Array array_vertex = Array();
			Array array_normal = Array();
			Array array_tex_uv = Array();

			for (int i = 0; i < surface_vertex_array.size(); i++)
			{
				array_vertex.push_back(rotate_vertex(surface_vertex_array[i], rotation));
			}
			for (int i = 0; i < surface_normal_array.size(); i++)
			{
				array_normal.push_back(rotate_vertex(surface_normal_array[i], rotation));
			}
			array_tex_uv.append_array(surface_tex_uv_array);

			surface[Mesh::ARRAY_VERTEX] = array_vertex;
			surface[Mesh::ARRAY_NORMAL] = array_normal;
			surface[Mesh::ARRAY_TEX_UV] = array_tex_uv;

			((Array)mesh_data_memorandum[index]).push_back(surface);
		}
	}

	Array surfaces = mesh_data_memorandum[index];
	for (int i = 0; i < surfaces.size(); i++)
	{
		Array array_vertex = arrays[Mesh::ARRAY_VERTEX];
		Array array_normal = arrays[Mesh::ARRAY_NORMAL];
		Array array_tex_uv = arrays[Mesh::ARRAY_TEX_UV];

		Array surface = surfaces[surface_index];

		Array surface_vertex_array = surface[Mesh::ARRAY_VERTEX];
		Array surface_normal_array = surface[Mesh::ARRAY_NORMAL];
		Array surface_tex_uv_array = surface[Mesh::ARRAY_TEX_UV];

		for (size_t i = 0; i < surface_vertex_array.size(); i++)
		{
			array_vertex.push_back(((Vector3)surface_vertex_array[i]) + position);
		}
		array_normal.append_array(surface_normal_array);
		array_tex_uv.append_array(surface_tex_uv_array);
	}
}

Ref<ModelPreset> ModelPreset::instantiate(const String& name, const Ref<Mesh>& mesh, Array materials) {
	Ref<ModelPreset> mesh_preset;
	mesh_preset.instantiate();
	mesh_preset->name = name;
	mesh_preset->mesh = mesh;
	mesh_preset->materials = materials;
	return mesh_preset;
}