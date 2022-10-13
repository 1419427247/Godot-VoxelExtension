#ifndef BASIC_PERSET_H
#define BASIC_PERSET_H

#include "perset.h"

using namespace godot;

class BasicsPerset : public Perset
{
	GDCLASS(BasicsPerset, Perset);
	enum MeshKey {
		UP = 0,
		DOWN = 1,
		FRONT = 2,
		BACK = 3,
		LEFT = 4,
		RIGHT = 5,
	};
	static const int ARRAY_MAX = 6;
private:
	Array materials;
protected:
	static void _bind_methods();
	static Vector3 _rotate_vertex(const Vector3& vertex, const Vector3i& rotation);
public:
	BasicsPerset();
	~BasicsPerset();

	void set_material(const int& key, const int& id);
	int get_material(const int& key) const;

	Array get_materials() const;

	static Ref<BasicsPerset> instantiate(const String& uuid,const String& name, const Dictionary& materials);

	static Vector3 get_triangle_normal(const Vector3& a, const Vector3& b, const Vector3& c);
	static void draw_mesh(const int& mesh_key,const Array& arrays, const Vector3& position, const Vector3& rotation);
};

VARIANT_ENUM_CAST(BasicsPerset, MeshKey);

#endif // !BASIC_PERSET_H