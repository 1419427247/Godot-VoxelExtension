#ifndef MESH_PERSET_H
#define MESH_PERSET_H

#include "perset.h"


class MeshPerset : public Perset
{
	GDCLASS(MeshPerset, Perset);
protected:
	static void _bind_methods();
private:
	Ref<Mesh> mesh;
	Array materials;
public:
	MeshPerset();
	~MeshPerset();

	void set_mesh(const Ref<Mesh>& value);
	Ref<Mesh> get_mesh() const;

	void set_material(const int& index, const int& id);
	int get_material(const int& index) const;
	Array get_materials() const; 

	static Ref<MeshPerset> instantiate(const String& uuid, const String& name, const Ref<Mesh>& mesh, Array materials);
};

#endif // !MESH_PERSET_H
