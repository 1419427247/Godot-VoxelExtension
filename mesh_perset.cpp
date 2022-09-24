#include "mesh_perset.h"

MeshPerset::MeshPerset() {

}
MeshPerset::~MeshPerset() {

}

void MeshPerset::set_mesh(const Ref<Mesh>& value) {
	mesh = value;
}

Ref<Mesh> MeshPerset::get_mesh() const
{
	return mesh;
}

void MeshPerset::draw_mesh(const Array& arrays, const Vector3& position, const Vector3& rotation) const
{
	for (size_t i = 0; i < mesh->get_surface_count(); i++)
	{
		Array mesh_arrays = mesh->surface_get_arrays(i);
		Array array_vertex = mesh_arrays[Mesh::ARRAY_VERTEX];
		Array array_normal = mesh_arrays[Mesh::ARRAY_NORMAL];
		Array array_tex_uv = mesh_arrays[Mesh::ARRAY_TEX_UV];
		array_vertex.append_array(mesh_arrays[Mesh::ARRAY_VERTEX]);
		array_normal.append_array(mesh_arrays[Mesh::ARRAY_NORMAL]);
		array_tex_uv.append_array(mesh_arrays[Mesh::ARRAY_TEX_UV]);
	}
}

Ref<MeshPerset> MeshPerset::instantiate(const String& uuid, const String& name, const Ref<Mesh>& mesh) {
	Ref<MeshPerset> mesh_perset;
	mesh_perset.instantiate();
	mesh_perset->uuid = uuid;
	mesh_perset->name = name;
	mesh_perset->mesh = mesh;
	return mesh_perset;
}

void MeshPerset::_bind_methods() {
	ClassDB::bind_static_method("MeshPerset", D_METHOD("instantiate", "uuid", "name", "mesh"), &MeshPerset::instantiate);
}
