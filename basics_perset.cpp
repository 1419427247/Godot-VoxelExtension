#include "basics_perset.h"

BasicsPerset::BasicsPerset()
{
}

BasicsPerset::~BasicsPerset()
{
}

int BasicsPerset::get_id() const
{
	return id;
}

String BasicsPerset::get_name() const
{
	return name;
}

Dictionary BasicsPerset::get_materials() const
{
	return materials;
}

void BasicsPerset::set_id(const int& value)
{
	this->id = value;
}

void BasicsPerset::set_name(const String& value)
{
	this->name = value;
}

void BasicsPerset::set_materials(const Dictionary& value)
{
	this->materials = value;
}

int BasicsPerset::get_material_id(const int& key) const
{
	return materials.get(key, 0);
}

Ref<BasicsPerset> BasicsPerset::instantiate(const int& id, const String& name, const Dictionary& materials)
{
	Ref<BasicsPerset> basics_perset;
	basics_perset.instantiate();
	basics_perset->id = id;
	basics_perset->name = name;
	basics_perset->materials = materials;
	return basics_perset;
}

Vector3 BasicsPerset::get_triangle_normal(const Vector3& a,const Vector3& b,const Vector3& c)
{
	return (c - a).cross(b - a);
}

static Vector2 uvs[] = {
	Vector2(0, 0), Vector2(1, 0), Vector2(1, 1),
	Vector2(0, 0), Vector2(1, 1), Vector2(0, 1),
};

static Vector3 brick_up_vertexs[] = {
	Vector3(-0.5, 0.5, -0.5),Vector3(0.5, 0.5, -0.5),Vector3(0.5, 0.5, 0.5),
	Vector3(-0.5, 0.5, -0.5),Vector3(0.5, 0.5, 0.5),Vector3(-0.5, 0.5, 0.5),
};
static Vector3 brick_down_vertexs[] = {
	Vector3(0.5, -0.5, -0.5),Vector3(-0.5, -0.5, -0.5),Vector3(-0.5, -0.5, 0.5),
	Vector3(0.5, -0.5, -0.5),Vector3(-0.5, -0.5, 0.5),Vector3(0.5, -0.5, 0.5),
};
static Vector3 brick_front_vertexs[] = {
	Vector3(0.5, 0.5, -0.5),Vector3(-0.5, 0.5, -0.5),Vector3(-0.5, -0.5, -0.5),
	Vector3(0.5, 0.5, -0.5),Vector3(-0.5, -0.5, -0.5),Vector3(0.5, -0.5, -0.5),
};
static Vector3 brick_back_vertexs[] = {
	Vector3(-0.5, 0.5, 0.5),Vector3(0.5, 0.5, 0.5),Vector3(0.5, -0.5, 0.5),
	Vector3(-0.5, 0.5, 0.5),Vector3(0.5, -0.5, 0.5),Vector3(-0.5, -0.5, 0.5),
};
static Vector3 brick_left_vertexs[] = {
	Vector3(-0.5, 0.5, -0.5),Vector3(-0.5, 0.5, 0.5),Vector3(-0.5, -0.5, 0.5),
	Vector3(-0.5, 0.5, -0.5),Vector3(-0.5, -0.5, 0.5),Vector3(-0.5, -0.5, -0.5),
};
static Vector3 brick_right_vertexs[] = {
	Vector3(0.5, 0.5, 0.5),Vector3(0.5, 0.5, -0.5),Vector3(0.5, -0.5, -0.5),
	Vector3(0.5, 0.5, 0.5),Vector3(0.5, -0.5, -0.5),Vector3(0.5, -0.5, 0.5),
};

static Vector3* brick_vertexs[] = {
	brick_up_vertexs,
	brick_down_vertexs,
	brick_front_vertexs,
	brick_back_vertexs,
	brick_left_vertexs,
	brick_right_vertexs
};
void BasicsPerset::draw_mesh(const int& mesh_key,const Array& arrays, const Vector3& position, const Vector3& rotation)
{
	Vector3* vertexs = brick_vertexs[mesh_key];
	Array array_vertex = arrays[Mesh::ARRAY_VERTEX];
	Array array_normal = arrays[Mesh::ARRAY_NORMAL];
	Array array_tex_uv = arrays[Mesh::ARRAY_TEX_UV];

	for (size_t i = 0; i < 6; i++)
	{
		array_vertex.push_back(_rotate_vertex(vertexs[i], rotation) + position);
	}

	Vector3 normal_1 = get_triangle_normal(vertexs[0], vertexs[1], vertexs[2]);
	Vector3 normal_2 = get_triangle_normal(vertexs[3], vertexs[4], vertexs[5]);

	array_normal.push_back(normal_1);
	array_normal.push_back(normal_1);
	array_normal.push_back(normal_1);
	array_normal.push_back(normal_2);
	array_normal.push_back(normal_2);
	array_normal.push_back(normal_2);

	for (size_t i = 0; i < 6; i++)
	{
		array_tex_uv.push_back(uvs[i]);
	}
}


void BasicsPerset::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_id", "value"), &BasicsPerset::set_id);
	ClassDB::bind_method(D_METHOD("set_name", "value"), &BasicsPerset::set_name);
	ClassDB::bind_method(D_METHOD("set_materials", "value"), &BasicsPerset::set_materials);

	ClassDB::bind_method(D_METHOD("get_id"), &BasicsPerset::get_id);
	ClassDB::bind_method(D_METHOD("get_name"), &BasicsPerset::get_name);
	ClassDB::bind_method(D_METHOD("get_materials"), &BasicsPerset::get_materials);

	ClassDB::bind_method(D_METHOD("get_material_id", "id"), &BasicsPerset::get_material_id);

	ClassDB::bind_static_method("BasicsPerset", D_METHOD("instantiate", "id", "name", "materials"), &BasicsPerset::instantiate);
	ClassDB::bind_static_method("BasicsPerset", D_METHOD("get_triangle_normal", "a", "b", "c"), &BasicsPerset::get_triangle_normal);

	ClassDB::add_property("BasicsPerset", PropertyInfo(Variant::INT, "id"), "set_id", "get_id");
	ClassDB::add_property("BasicsPerset", PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");
	ClassDB::add_property("BasicsPerset", PropertyInfo(Variant::DICTIONARY, "materials"), "set_materials", "get_materials");

	BIND_ENUM_CONSTANT(UP);
	BIND_ENUM_CONSTANT(DOWN);
	BIND_ENUM_CONSTANT(FRONT);
	BIND_ENUM_CONSTANT(BACK);
	BIND_ENUM_CONSTANT(LEFT);
	BIND_ENUM_CONSTANT(RIGHT);
}

Vector3 BasicsPerset::_rotate_vertex(const Vector3& vertex, const Vector3i& rotation)
{
	Vector3 result = vertex;
	result = result.rotated(Vector3(1, 0, 0), UtilityFunctions::deg_to_rad(rotation.x));
	result = result.rotated(Vector3(0, 1, 0), UtilityFunctions::deg_to_rad(rotation.y));
	result = result.rotated(Vector3(0, 0, 1), UtilityFunctions::deg_to_rad(rotation.z));
	return result;
}