#ifndef MESH_PERSET_H
#define MESH_PERSET_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;


class MeshPerset : public RefCounted
{
	GDCLASS(MeshPerset, RefCounted);
private:
	int id;
	String name;
	Mesh* mesh;

public:
	MeshPerset();
	~MeshPerset();

	void set_id(const int& value);
	void set_name(const String& value);
	void set_mesh(const Ref<Mesh>& value);

	int get_id() const;
	String get_name() const;
	Ref<Mesh> get_mesh() const;

	static Ref<MeshPerset> instantiate(const int& id, const String& name, const Ref<Mesh>& mesh);
protected:
	static void _bind_methods();
};

#endif // !MESH_PERSET_H
