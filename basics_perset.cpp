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

int BasicsPerset::get_mesh_type() const
{
	return mesh_type;
}

Color BasicsPerset::get_color() const
{
	return color;
}

Dictionary BasicsPerset::get_materials() const
{
	return materials;
}

void BasicsPerset::set_id(int value)
{
	this->id = value;
}

void BasicsPerset::set_name(String value)
{
	this->name = value;
}

void BasicsPerset::set_mesh_type(int value)
{
	this->mesh_type = value;
}

void BasicsPerset::set_color(Color value)
{
	this->color = value;
}

void BasicsPerset::set_materials(Dictionary value)
{
	this->materials = value;
}

int BasicsPerset::get_material_id(String key) const
{
	return materials.get(key, 0);
}


Ref<BasicsPerset> BasicsPerset::instantiate(int id, String name, int mesh_type, Color color, Dictionary materials)
{
	Ref<BasicsPerset> basics_perset;
	basics_perset.instantiate();
	basics_perset->id = id;
	basics_perset->name = name;
	basics_perset->mesh_type = mesh_type;
	basics_perset->color = color;
	basics_perset->materials = materials;
	return basics_perset;
}

Vector3 BasicsPerset::get_triangle_normal(Vector3 a, Vector3 b, Vector3 c)
{
	return (c - a).cross(b - a);
}

static Vector3 _brick_vertexs[] = {
	Vector3(0.5, -0.5, -0.5),
	Vector3(0.5, 0.5, -0.5),
	Vector3(-0.5, 0.5, -0.5),
	Vector3(-0.5, -0.5, -0.5),
	Vector3(0.5, -0.5, 0.5),
	Vector3(0.5, 0.5, 0.5),
	Vector3(-0.5, 0.5, 0.5),
	Vector3(-0.5, -0.5, 0.5),
};

static Vector2 _brick_uvs[] = {
	Vector2(0, 0), Vector2(1, 0), Vector2(1, 1),
	Vector2(0, 0), Vector2(1, 1), Vector2(0, 1),
};

void BasicsPerset::draw_brick_front_mesh(Array& arrays, int index, const Vector3i& position, const Vector3i& rotation)
{
	Array vertex;
	vertex.push_back(Variant(_brick_vertexs[3]));
	vertex.push_back(Variant(_brick_vertexs[1]));
	vertex.push_back(Variant(_brick_vertexs[2]));
	vertex.push_back(Variant(_brick_vertexs[3]));
	vertex.push_back(Variant(_brick_vertexs[1]));
	vertex.push_back(Variant(_brick_vertexs[0]));
	_draw_brick_mesh(vertex, arrays, index, position, rotation);
}

void BasicsPerset::draw_brick_back_mesh(Array& arrays, int index, const Vector3i& position, const Vector3i& rotation)
{
	Array vertex;
	vertex.push_back(Variant(_brick_vertexs[6]));
	vertex.push_back(Variant(_brick_vertexs[5]));
	vertex.push_back(Variant(_brick_vertexs[4]));
	vertex.push_back(Variant(_brick_vertexs[6]));
	vertex.push_back(Variant(_brick_vertexs[4]));
	vertex.push_back(Variant(_brick_vertexs[7]));
	_draw_brick_mesh(vertex, arrays, index, position, rotation);
}

void BasicsPerset::draw_brick_left_mesh(Array& arrays, int index, const Vector3i& position, const Vector3i& rotation)
{
	Array vertex;
	vertex.push_back(Variant(_brick_vertexs[2]));
	vertex.push_back(Variant(_brick_vertexs[6]));
	vertex.push_back(Variant(_brick_vertexs[7]));
	vertex.push_back(Variant(_brick_vertexs[2]));
	vertex.push_back(Variant(_brick_vertexs[7]));
	vertex.push_back(Variant(_brick_vertexs[3]));
	_draw_brick_mesh(vertex, arrays, index, position, rotation);
}

void BasicsPerset::draw_brick_right_mesh(Array& arrays, int index, const Vector3i& position, const Vector3i& rotation)
{
	Array vertex;
	vertex.push_back(Variant(_brick_vertexs[5]));
	vertex.push_back(Variant(_brick_vertexs[1]));
	vertex.push_back(Variant(_brick_vertexs[0]));
	vertex.push_back(Variant(_brick_vertexs[5]));
	vertex.push_back(Variant(_brick_vertexs[0]));
	vertex.push_back(Variant(_brick_vertexs[4]));
	_draw_brick_mesh(vertex, arrays, index, position, rotation);
}

void BasicsPerset::draw_brick_up_mesh(Array& arrays, int index, const Vector3i& position, const Vector3i& rotation)
{
	Array vertex;
	vertex.push_back(Variant(_brick_vertexs[2]));
	vertex.push_back(Variant(_brick_vertexs[1]));
	vertex.push_back(Variant(_brick_vertexs[5]));
	vertex.push_back(Variant(_brick_vertexs[2]));
	vertex.push_back(Variant(_brick_vertexs[5]));
	vertex.push_back(Variant(_brick_vertexs[6]));
	_draw_brick_mesh(vertex, arrays, index, position, rotation);
}

void BasicsPerset::draw_brick_down_mesh(Array& arrays, int index, const Vector3i& position, const Vector3i& rotation)
{
	vertex.push_back(Variant(_brick_vertexs[0]));
	vertex.push_back(Variant(_brick_vertexs[3]));
	vertex.push_back(Variant(_brick_vertexs[7]));
	vertex.push_back(Variant(_brick_vertexs[0]));
	vertex.push_back(Variant(_brick_vertexs[7]));
	vertex.push_back(Variant(_brick_vertexs[4]));
	_draw_brick_mesh(vertex, arrays, index, position, rotation);
}

void BasicsPerset::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_id", "value"), &BasicsPerset::set_id);
	ClassDB::bind_method(D_METHOD("set_name", "value"), &BasicsPerset::set_name);
	ClassDB::bind_method(D_METHOD("set_mesh_type", "value"), &BasicsPerset::set_mesh_type);
	ClassDB::bind_method(D_METHOD("set_color", "value"), &BasicsPerset::set_color);
	ClassDB::bind_method(D_METHOD("set_materials", "value"), &BasicsPerset::set_materials);

	ClassDB::bind_method(D_METHOD("get_id"), &BasicsPerset::get_id);
	ClassDB::bind_method(D_METHOD("get_name"), &BasicsPerset::get_name);
	ClassDB::bind_method(D_METHOD("get_mesh_type"), &BasicsPerset::get_mesh_type);
	ClassDB::bind_method(D_METHOD("get_color"), &BasicsPerset::get_color);
	ClassDB::bind_method(D_METHOD("get_materials"), &BasicsPerset::get_materials);

	ClassDB::bind_method(D_METHOD("get_material_id", "id"), &BasicsPerset::get_material_id);

	ClassDB::bind_static_method("BasicsPerset", D_METHOD("instantiate", "id", "name", "mesh_type", "color", "materials"), &BasicsPerset::instantiate);
	ClassDB::bind_static_method("BasicsPerset", D_METHOD("get_triangle_normal", "a", "b", "c"), &BasicsPerset::get_triangle_normal);

	ClassDB::add_property("BasicsPerset", PropertyInfo(Variant::INT, "id"), "set_id", "get_id");
	ClassDB::add_property("BasicsPerset", PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");
	ClassDB::add_property("BasicsPerset", PropertyInfo(Variant::INT, "mesh_type"), "set_mesh_type", "get_mesh_type");
	ClassDB::add_property("BasicsPerset", PropertyInfo(Variant::COLOR, "color"), "set_color", "get_color");
	ClassDB::add_property("BasicsPerset", PropertyInfo(Variant::DICTIONARY, "materials"), "set_materials", "get_materials");
}

void BasicsPerset::_rotate_mesh(Array& vertexs, const Vector3i& rotation)
{
	if (rotation.x != 0) {
		for (size_t i = 0; i < vertexs.size(); i++)
		{
			vertexs[i] = static_cast<Vector3>(vertexs[i]).rotated(Vector3(1, 0, 0), UtilityFunctions::deg_to_rad(rotation.x));
		}
	}
	if (rotation.y != 0) {
		for (size_t i = 0; i < vertexs.size(); i++)
		{
			vertexs[i] = static_cast<Vector3>(vertexs[i]).rotated(Vector3(0, 1, 0), UtilityFunctions::deg_to_rad(rotation.y));
		}
	}
	if (rotation.z != 0) {
		for (size_t i = 0; i < vertexs.size(); i++)
		{
			vertexs[i] = static_cast<Vector3>(vertexs[i]).rotated(Vector3(0, 0, 1), UtilityFunctions::deg_to_rad(rotation.z));
		}
	}
}

void BasicsPerset::_draw_brick_mesh(Array& vertexs, Array& arrays, const int index, const Vector3& position, const Vector3i& rotation)
{
	_rotate_mesh(vertexs, rotation);

	PackedVector3Array* array_vertex = &(PackedVector3Array)(((Array)arrays[index])[Mesh::ARRAY_VERTEX]);
	PackedVector3Array* array_normal = &(PackedVector3Array)(((Array)arrays[index])[Mesh::ARRAY_NORMAL]);
	PackedVector2Array* array_tex_uv = &(PackedVector2Array)(((Array)arrays[index])[Mesh::ARRAY_TEX_UV]);

	for (size_t i = 0; i < vertexs.size(); i++)
	{
		Vector3 value = static_cast<Vector3>(vertexs[i]) + position;
		array_vertex->push_back(value);
	}

	Vector3 normal_1 = get_triangle_normal(vertexs[0], vertexs[1], vertexs[2]);
	Vector3 normal_2 = get_triangle_normal(vertexs[3], vertexs[4], vertexs[5]);

	array_normal->push_back(normal_1);
	array_normal->push_back(normal_1);
	array_normal->push_back(normal_1);
	array_normal->push_back(normal_2);
	array_normal->push_back(normal_2);
	array_normal->push_back(normal_2);

	for (size_t i = 0; i < sizeof(_brick_uvs) / sizeof(Vector2); i++)
	{
		array_tex_uv->push_back(_brick_uvs[i]);
	}
}
