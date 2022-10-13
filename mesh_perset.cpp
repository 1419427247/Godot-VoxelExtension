#include "mesh_perset.h"

void MeshPerset::_bind_methods() {
	ClassDB::bind_static_method("MeshPerset", D_METHOD("instantiate", "uuid", "name", "mesh"), &MeshPerset::instantiate);
}

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

void MeshPerset::set_material(const int& index, const int& id)
{
	materials[index] = id;
}

int MeshPerset::get_material(const int& index) const
{
	return materials[index];
}

Array MeshPerset::get_materials() const
{
	return materials;
}

Ref<MeshPerset> MeshPerset::instantiate(const String& uuid, const String& name, const Ref<Mesh>& mesh, Array materials) {
	Ref<MeshPerset> mesh_perset;
	mesh_perset.instantiate();
	mesh_perset->uuid = uuid;
	mesh_perset->name = name;
	mesh_perset->mesh = mesh;
	mesh_perset->materials = materials;
	return mesh_perset;
}