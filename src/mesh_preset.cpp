#include "mesh_preset.h"

void MeshPreset::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_mesh", "value"), &MeshPreset::set_mesh);
	ClassDB::bind_method(D_METHOD("get_mesh"), &MeshPreset::get_mesh);

	ClassDB::bind_method(D_METHOD("set_materials", "value"), &MeshPreset::set_materials);
	ClassDB::bind_method(D_METHOD("get_materials"), &MeshPreset::get_materials);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "mesh", PROPERTY_HINT_RESOURCE_TYPE, "Mesh"), "set_mesh", "get_mesh");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "material", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::INT) + "/" + String::num_int64(PROPERTY_HINT_NONE) + ":"), "set_materials", "get_materials");
}

MeshPreset::MeshPreset() {

}

MeshPreset::~MeshPreset() {

}

void MeshPreset::set_mesh(const Ref<Mesh>& value) {
	mesh = value;
	if (mesh.is_null())
	{
		materials.clear();
		prototype.clear();
	}
	else {
		materials.resize(mesh->get_surface_count());
		memorandum.clear();
		memorandum.resize(24 * 24 * 24);

		prototype = Array();
		prototype.resize(mesh->get_surface_count());
		for (int i = 0; i < prototype.size(); i++)
		{
			Array mesh_surface_arrays = mesh->surface_get_arrays(i);

			ERR_FAIL_COND(mesh_surface_arrays[Mesh::ARRAY_VERTEX].get_type() == Variant::NIL);
			ERR_FAIL_COND(mesh_surface_arrays[Mesh::ARRAY_TEX_UV].get_type() == Variant::NIL);
			ERR_FAIL_COND(mesh_surface_arrays[Mesh::ARRAY_INDEX].get_type() == Variant::NIL);

			PackedVector3Array packed_array_vertex = mesh_surface_arrays[Mesh::ARRAY_VERTEX];
			PackedVector2Array packed_array_tex_uv = mesh_surface_arrays[Mesh::ARRAY_TEX_UV];
			PackedInt32Array packed_array_index = mesh_surface_arrays[Mesh::ARRAY_INDEX];

			Array surface = Array();
			surface.resize(Mesh::ARRAY_MAX);

			Array surface_vertex_array;
			Array surface_tex_uv_array;

			for (size_t i = 0; i < packed_array_index.size(); i++)
			{
				surface_vertex_array.push_back(packed_array_vertex[packed_array_index[i]]);
				surface_tex_uv_array.push_back(packed_array_tex_uv[packed_array_index[i]]);
			}

			surface[Mesh::ARRAY_VERTEX] = surface_vertex_array;
			surface[Mesh::ARRAY_TEX_UV] = surface_tex_uv_array;

			prototype[i] = surface;
		}
	}
	notify_property_list_changed();
}

Ref<Mesh> MeshPreset::get_mesh() const {
	return mesh;
}

void MeshPreset::set_materials(const TypedArray<int>& value) {
	materials = value;
	if (mesh.is_null())
	{
		materials.clear();
	}
	else {
		materials.resize(prototype.size());
	}
	notify_property_list_changed();
}

TypedArray<int> MeshPreset::get_materials() const {
	return materials;
}


void MeshPreset::build_mesh(const Array& arrays, const int& surface_index, const Vector3& position, const Vector3& rotation) const
{
	int index = (rotation.x / 15 * 24 * 24 + rotation.y / 15 * 24 + rotation.z / 15);

	if (memorandum[index].get_type() == Variant::NIL) {
		memorandum[index] = Array();
		for (int i = 0; i < prototype.size(); i++)
		{
			Array surface_vertex_array = ((Array)prototype[i])[Mesh::ARRAY_VERTEX];
			Array surface_tex_uv_array = ((Array)prototype[i])[Mesh::ARRAY_TEX_UV];

			Array surface = Array();
			surface.resize(Mesh::ARRAY_MAX);

			Array array_vertex = Array();
			Array array_normal = Array();
			Array array_tangent = Array();
			Array array_tex_uv = Array();

			for (int i = 0; i < surface_vertex_array.size(); i += 3)
			{
				Vector3 vertexs[3] = {
					MeshPreset::rotate_vertex(surface_vertex_array[i + 0], rotation),
					MeshPreset::rotate_vertex(surface_vertex_array[i + 1], rotation),
					MeshPreset::rotate_vertex(surface_vertex_array[i + 2], rotation),
				};
				Vector2 uvs[3] = {
					surface_tex_uv_array[i + 0],
					surface_tex_uv_array[i + 1],
					surface_tex_uv_array[i + 2],
				};
				Vector3 tangent;
				Vector3 binormal;
				Vector3 normal;
				MeshPreset::get_tbn(vertexs, uvs, &tangent, &binormal, &normal);
				for (int i = 0; i < 3; i++)
				{
					array_vertex.push_back(vertexs[i]);
				}
				for (int i = 0; i < 3; i++)
				{
					array_normal.push_back(normal);
				}
				for (int i = 0; i < 3; i++)
				{
					array_tangent.push_back(tangent.x);
					array_tangent.push_back(tangent.y);
					array_tangent.push_back(tangent.z);
					array_tangent.push_back(binormal.dot(normal.cross(tangent)) < 0 ? -1 : 1);
				}
			}
			array_tex_uv.append_array(surface_tex_uv_array);

			surface[Mesh::ARRAY_VERTEX] = array_vertex;
			surface[Mesh::ARRAY_NORMAL] = array_normal;
			surface[Mesh::ARRAY_TANGENT] = array_tangent;
			surface[Mesh::ARRAY_TEX_UV] = array_tex_uv;

			((Array)memorandum[index]).push_back(surface);
		}
	}

	Array surface = ((Array)memorandum[index])[surface_index];

	Array array_vertex = arrays[Mesh::ARRAY_VERTEX];
	Array array_normal = arrays[Mesh::ARRAY_NORMAL];
	Array array_tangent = arrays[Mesh::ARRAY_TANGENT];
	Array array_tex_uv = arrays[Mesh::ARRAY_TEX_UV];

	Array surface_vertex_array = surface[Mesh::ARRAY_VERTEX];
	Array surface_normal_array = surface[Mesh::ARRAY_NORMAL];
	Array surface_tangent_array = surface[Mesh::ARRAY_TANGENT];
	Array surface_tex_uv_array = surface[Mesh::ARRAY_TEX_UV];

	for (size_t i = 0; i < surface_vertex_array.size(); i++)
	{
		array_vertex.push_back(((Vector3)surface_vertex_array[i]) + position);
	}
	array_normal.append_array(surface_normal_array);
	array_tangent.append_array(surface_tangent_array);
	array_tex_uv.append_array(surface_tex_uv_array);
}

Vector3 MeshPreset::rotate_vertex(const Vector3& vertex, const Vector3i& rotation)
{
	Vector3 result = vertex;
	result.rotate(Vector3(0, 1, 0), UtilityFunctions::deg_to_rad(rotation.y));
	result.rotate(Vector3(1, 0, 0), UtilityFunctions::deg_to_rad(rotation.x));
	result.rotate(Vector3(0, 0, 1), UtilityFunctions::deg_to_rad(rotation.z));
	return result;
}

void MeshPreset::get_tbn(Vector3 vertexs[3], Vector2 uvs[3],Vector3* tangent, Vector3* binormal, Vector3* normal) {

	Vector3 vector_0 = vertexs[2] - vertexs[0];
	Vector3 vector_1 = vertexs[1] - vertexs[0];
	Vector2 uv_0 = uvs[2] - uvs[0];
	Vector2 uv_1 = uvs[1] - uvs[0];

	float f = 1.0f / (uv_0.x * uv_1.y - uv_1.x * uv_0.y);
	
	tangent->x = f * (uv_1.y * vector_0.x - uv_0.y * vector_1.x);
	tangent->y = f * (uv_1.y * vector_0.y - uv_0.y * vector_1.y);
	tangent->z = f * (uv_1.y * vector_0.z - uv_0.y * vector_1.z);

	binormal->x = f * (-uv_1.x * vector_0.x + uv_0.x * vector_1.x);
	binormal->y = f * (-uv_1.x * vector_0.y + uv_0.x * vector_1.y);
	binormal->z = f * (-uv_1.x * vector_0.z + uv_0.x * vector_1.z);

	*normal = Plane(vertexs[0], vertexs[1], vertexs[2]).get_normal();

	tangent->normalize();
	binormal->normalize();
	normal->normalize();
}
