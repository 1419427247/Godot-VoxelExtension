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
	enum MeshType {
		BRICK = 0,
		HALF_BRICK = 1,
	};

	int id;
	String name;
	int mesh_type;
	Color color;
	Dictionary materials;

	BasicsPerset();
	~BasicsPerset();

	int get_id() const;
	String get_name() const;
	int get_mesh_type() const;
	Color get_color() const;
	Dictionary get_materials() const;

	void set_id(int value);
	void set_name(String value);
	void set_mesh_type(int value);
	void set_color(Color value);
	void set_materials(Dictionary value);


	int get_material_id(String key) const;

	static Ref<BasicsPerset> instantiate(int id, String name, int mesh_type, Color color, Dictionary materials);
	static Vector3 get_triangle_normal(Vector3 a, Vector3 b, Vector3 c);

	static void draw_brick_front_mesh(Array& arrays, int index, const Vector3i& position, const Vector3i& rotation);
	static void draw_brick_back_mesh(Array& arrays, int index, const Vector3i& position, const Vector3i& rotation);
	static void draw_brick_left_mesh(Array& arrays, int index, const Vector3i& position, const Vector3i& rotation);
	static void draw_brick_right_mesh(Array& arrays, int index, const Vector3i& position, const Vector3i& rotation);
	static void draw_brick_up_mesh(Array& arrays, int index, const Vector3i& position, const Vector3i& rotation);
	static void draw_brick_down_mesh(Array& arrays, int index, const Vector3i& position, const Vector3i& rotation);

protected:
	static void _bind_methods();

	static void _rotate_mesh(Array& vertexs, const Vector3i& rotation);
	static void _draw_brick_mesh(Array& vertexs, Array& arrays, const int index, const Vector3& position, const Vector3i& rotation);
};

VARIANT_ENUM_CAST(BasicsPerset, MeshType);

#endif // !BASIC_PERSET_H