#include "basics_preset.h"

void BasicsPreset::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_up", "value"), &BasicsPreset::set_up);
	ClassDB::bind_method(D_METHOD("get_up"), &BasicsPreset::get_up);

	ClassDB::bind_method(D_METHOD("set_down", "value"), &BasicsPreset::set_down);
	ClassDB::bind_method(D_METHOD("get_down"), &BasicsPreset::get_down);

	ClassDB::bind_method(D_METHOD("set_front", "value"), &BasicsPreset::set_front);
	ClassDB::bind_method(D_METHOD("get_front"), &BasicsPreset::get_front);

	ClassDB::bind_method(D_METHOD("set_back", "value"), &BasicsPreset::set_back);
	ClassDB::bind_method(D_METHOD("get_back"), &BasicsPreset::get_back);

	ClassDB::bind_method(D_METHOD("set_left", "value"), &BasicsPreset::set_left);
	ClassDB::bind_method(D_METHOD("get_left"), &BasicsPreset::get_left);

	ClassDB::bind_method(D_METHOD("set_right", "value"), &BasicsPreset::set_right);
	ClassDB::bind_method(D_METHOD("get_right"), &BasicsPreset::get_right);

	ClassDB::bind_static_method("BasicsPreset", D_METHOD("instantiate", "uuid", "name", "materials"), &BasicsPreset::instantiate);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "up"), "set_up", "get_up");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "down"), "set_down", "get_down");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "front"), "set_front", "get_front");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "back"), "set_back", "get_back");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "left"), "set_left", "get_left");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "right"), "set_right", "get_right");
}

BasicsPreset::BasicsPreset()
{
	up = 0;
	down = 0;
	front = 0;
	back = 0;
	left = 0;
	right = 0;
}

BasicsPreset::~BasicsPreset()
{
}

void BasicsPreset::set_up(const int& value)
{
	up = value;
}

int BasicsPreset::get_up() const
{
	return up;
}

void BasicsPreset::set_down(const int& value)
{
	down = value;
}

int BasicsPreset::get_down() const
{
	return down;
}

void BasicsPreset::set_front(const int& value)
{
	front = value;
}

int BasicsPreset::get_front() const
{
	return front;
}

void BasicsPreset::set_back(const int& value)
{
	back = value;
}

int BasicsPreset::get_back() const
{
	return back;
}

void BasicsPreset::set_left(const int& value)
{
	left = value;
}

int BasicsPreset::get_left() const
{
	return left;
}

void BasicsPreset::set_right(const int& value)
{
	right = value;
}

int BasicsPreset::get_right() const
{
	return right;
}

Ref<BasicsPreset> BasicsPreset::instantiate(const String& uuid, const String& name, const Dictionary& materials)
{
	Ref<BasicsPreset> basics_preset;
	basics_preset.instantiate();
	basics_preset->uuid = uuid;
	basics_preset->name = name;

	basics_preset->set_up((int)materials.get("up", 0));
	basics_preset->set_down((int)materials.get("down", 0));
	basics_preset->set_front((int)materials.get("front", 0));
	basics_preset->set_back((int)materials.get("back", 0));
	basics_preset->set_left((int)materials.get("left", 0));
	basics_preset->set_right((int)materials.get("right", 0));

	return basics_preset;
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

void BasicsPreset::build_mesh(const int& mesh_key,const Array& arrays, const Vector3& position, const Vector3& rotation)
{
	Vector3 vertexs[6];
	Array array_vertex = arrays[Mesh::ARRAY_VERTEX];
	Array array_normal = arrays[Mesh::ARRAY_NORMAL];
	Array array_tex_uv = arrays[Mesh::ARRAY_TEX_UV];

	for (int i = 0; i < 6; i++)
	{
		vertexs[i] = rotate_vertex(brick_vertexs[mesh_key][i], rotation) + position;
		array_vertex.push_back(vertexs[i]);
	}

	Vector3 normal_1 = Plane(vertexs[0], vertexs[1], vertexs[2]).get_normal();
	Vector3 normal_2 = Plane(vertexs[3], vertexs[4], vertexs[5]).get_normal();

	array_normal.push_back(normal_1);
	array_normal.push_back(normal_1);
	array_normal.push_back(normal_1);
	array_normal.push_back(normal_2);
	array_normal.push_back(normal_2);
	array_normal.push_back(normal_2);

	for (int i = 0; i < 6; i++)
	{
		array_tex_uv.push_back(uvs[i]);
	}
}

Vector3 BasicsPreset::rotate_vertex(const Vector3& vertex, const Vector3i& rotation)
{
	Vector3 result = vertex;
	result = result.rotated(Vector3(0, 1, 0), UtilityFunctions::deg_to_rad(rotation.y));
	result = result.rotated(Vector3(1, 0, 0), UtilityFunctions::deg_to_rad(rotation.x));
	result = result.rotated(Vector3(0, 0, 1), UtilityFunctions::deg_to_rad(rotation.z));
	return result;
}
