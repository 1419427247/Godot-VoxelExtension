#include "mesh_perset.h"

MeshPerset::MeshPerset() {

}
MeshPerset::~MeshPerset() {

}

void MeshPerset::set_id(const int& value) {
}
void MeshPerset::set_name(const String& value) {
}
void MeshPerset::set_mesh(const Ref<Mesh>& value) {
}

int MeshPerset::get_id() const
{
	return id;
}
String MeshPerset::get_name() const
{
	return name;
}
Ref<Mesh> MeshPerset::get_mesh() const
{
	return mesh;
}

Ref<MeshPerset> MeshPerset::instantiate(const int& id, const String& name, const Ref<Mesh>& mesh) {
	Ref<MeshPerset> mesh_perset;
	mesh_perset.instantiate();
	mesh_perset->id = id;
	mesh_perset->name = name;
	mesh_perset->mesh = (Mesh*)mesh.ptr();
	return mesh;
}

void MeshPerset::_bind_methods() {
	ClassDB::bind_static_method("MeshPerset", D_METHOD("instantiate", "id", "name", "mesh"), &MeshPerset::instantiate);
}
