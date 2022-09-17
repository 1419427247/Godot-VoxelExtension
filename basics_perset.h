#ifndef BASIC_PERSET_H
#define BASIC_PERSET_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class BasicsPerset : public RefCounted
{
	GDCLASS(BasicsPerset, RefCounted);
public:

	enum MeshKey {
		UP = 0,
		DOWN = 1,
		FRONT = 2,
		BACK = 3,
		LEFT = 4,
		RIGHT = 5,
	};

	int id;
	String name;
	Dictionary materials;

	BasicsPerset();
	~BasicsPerset();

	int get_id() const;
	String get_name() const;
	Dictionary get_materials() const;

	void set_id(const int& value);
	void set_name(const String& value);
	void set_materials(const Dictionary& value);

	int get_material_id(const int& key) const;

	static Ref<BasicsPerset> instantiate(const int& id,const String& name, const Dictionary& materials);
	static Vector3 get_triangle_normal(const Vector3& a, const Vector3& b, const Vector3& c);

	static void draw_mesh(const int& mesh_key,const Array& arrays, const Vector3& position, const Vector3& rotation);

protected:
	static void _bind_methods();
	static Vector3 _rotate_vertex(const Vector3& vertex, const Vector3i& rotation);
};

VARIANT_ENUM_CAST(BasicsPerset, MeshKey);

#endif // !BASIC_PERSET_H