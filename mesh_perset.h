#ifndef MESH_PERSET_H
#define MESH_PERSET_H

#include "perset.h"


class MeshPerset : public Perset
{
	GDCLASS(MeshPerset, Perset);
private:
	Ref<Mesh> mesh;
public:
	MeshPerset();
	~MeshPerset();

	void set_mesh(const Ref<Mesh>& value);
	Ref<Mesh> get_mesh() const;

	void draw_mesh(const Array& arrays, const Vector3& position, const Vector3& rotation) const;

	static Ref<MeshPerset> instantiate(const String& uuid, const String& name, const Ref<Mesh>& mesh);
protected:
	static void _bind_methods();
};

#endif // !MESH_PERSET_H
