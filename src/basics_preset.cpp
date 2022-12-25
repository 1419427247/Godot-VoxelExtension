#include "basics_preset.h"

void BasicsPreset::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_basics_mesh", "value"), &BasicsPreset::set_basics_mesh);
	ClassDB::bind_method(D_METHOD("get_basics_mesh"), &BasicsPreset::get_basics_mesh);

	ClassDB::bind_method(D_METHOD("set_up_material_id", "value"), &BasicsPreset::set_up_material_id);
	ClassDB::bind_method(D_METHOD("get_up_material_id"), &BasicsPreset::get_up_material_id);
	ClassDB::bind_method(D_METHOD("set_down_material_id", "value"), &BasicsPreset::set_down_material_id);
	ClassDB::bind_method(D_METHOD("get_down_material_id"), &BasicsPreset::get_down_material_id);
	ClassDB::bind_method(D_METHOD("set_front_material_id", "value"), &BasicsPreset::set_front_material_id);
	ClassDB::bind_method(D_METHOD("get_front_material_id"), &BasicsPreset::get_front_material_id);
	ClassDB::bind_method(D_METHOD("set_back_material_id", "value"), &BasicsPreset::set_back_material_id);
	ClassDB::bind_method(D_METHOD("get_back_material_id"), &BasicsPreset::get_back_material_id);
	ClassDB::bind_method(D_METHOD("set_left_material_id", "value"), &BasicsPreset::set_left_material_id);
	ClassDB::bind_method(D_METHOD("get_left_material_id"), &BasicsPreset::get_left_material_id);
	ClassDB::bind_method(D_METHOD("set_right_material_id", "value"), &BasicsPreset::set_right_material_id);
	ClassDB::bind_method(D_METHOD("get_right_material_id"), &BasicsPreset::get_right_material_id);

	ClassDB::bind_method(D_METHOD("set_up_material_uv", "value"), &BasicsPreset::set_up_material_uv);
	ClassDB::bind_method(D_METHOD("get_up_material_uv"), &BasicsPreset::get_up_material_uv);
	ClassDB::bind_method(D_METHOD("set_down_material_uv", "value"), &BasicsPreset::set_down_material_uv);
	ClassDB::bind_method(D_METHOD("get_down_material_uv"), &BasicsPreset::get_down_material_uv);
	ClassDB::bind_method(D_METHOD("set_front_material_uv", "value"), &BasicsPreset::set_front_material_uv);
	ClassDB::bind_method(D_METHOD("get_front_material_uv"), &BasicsPreset::get_front_material_uv);
	ClassDB::bind_method(D_METHOD("set_back_material_uv", "value"), &BasicsPreset::set_back_material_uv);
	ClassDB::bind_method(D_METHOD("get_back_material_uv"), &BasicsPreset::get_back_material_uv);
	ClassDB::bind_method(D_METHOD("set_left_material_uv", "value"), &BasicsPreset::set_left_material_uv);
	ClassDB::bind_method(D_METHOD("get_left_material_uv"), &BasicsPreset::get_left_material_uv);
	ClassDB::bind_method(D_METHOD("set_right_material_uv", "value"), &BasicsPreset::set_right_material_uv);
	ClassDB::bind_method(D_METHOD("get_right_material_uv"), &BasicsPreset::get_right_material_uv);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "mesh_preset", PROPERTY_HINT_RESOURCE_TYPE, "MeshPreset"), "set_basics_mesh", "get_basics_mesh");

	ADD_PROPERTY(PropertyInfo(Variant::INT, "up_material_id"), "set_up_material_id", "get_up_material_id");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "down_material_id"), "set_down_material_id", "get_down_material_id");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "front_material_id"), "set_front_material_id", "get_front_material_id");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "back_material_id"), "set_back_material_id", "get_back_material_id");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "left_material_id"), "set_left_material_id", "get_left_material_id");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "right_material_id"), "set_right_material_id", "get_right_material_id");

	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "up_material_uv", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::VECTOR2) + "/" + String::num_int64(PROPERTY_HINT_NONE) + ":"), "set_up_material_uv", "get_up_material_uv");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "down_material_uv", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::VECTOR2) + "/" + String::num_int64(PROPERTY_HINT_NONE) + ":"), "set_down_material_uv", "get_down_material_uv");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "front_material_uv", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::VECTOR2) + "/" + String::num_int64(PROPERTY_HINT_NONE) + ":"), "set_front_material_uv", "get_front_material_uv");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "back_material_uv", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::VECTOR2) + "/" + String::num_int64(PROPERTY_HINT_NONE) + ":"), "set_back_material_uv", "get_back_material_uv");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "left_material_uv", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::VECTOR2) + "/" + String::num_int64(PROPERTY_HINT_NONE) + ":"), "set_left_material_uv", "get_left_material_uv");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "right_material_uv", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::VECTOR2) + "/" + String::num_int64(PROPERTY_HINT_NONE) + ":"), "set_right_material_uv", "get_right_material_uv");
}

BasicsPreset::BasicsPreset()
{
	materials.resize(6);
	for (int i = 0; i < 6; i++)
	{
		uvs[i].push_back(Vector2(0, 0));
		uvs[i].push_back(Vector2(1, 0));
		uvs[i].push_back(Vector2(1, 1));
		uvs[i].push_back(Vector2(0, 0));
		uvs[i].push_back(Vector2(1, 1));
		uvs[i].push_back(Vector2(0, 1));
	}
}

BasicsPreset::~BasicsPreset()
{
}

void BasicsPreset::set_basics_mesh(const Ref<MeshPreset>& value)
{
	mesh_preset = value;
}

Ref<MeshPreset> BasicsPreset::get_basics_mesh() const
{
	return mesh_preset;
}

void BasicsPreset::set_up_material_id(const int& value)
{
	materials[UP] = value;
}

int BasicsPreset::get_up_material_id() const
{
	return materials[UP];
}

void BasicsPreset::set_down_material_id(const int& value)
{
	materials[DOWN] = value;
}

int BasicsPreset::get_down_material_id() const
{
	return materials[DOWN];
}

void BasicsPreset::set_front_material_id(const int& value)
{
	materials[FRONT] = value;
}

int BasicsPreset::get_front_material_id() const
{
	return materials[FRONT];
}

void BasicsPreset::set_back_material_id(const int& value)
{
	materials[BACK] = value;
}

int BasicsPreset::get_back_material_id() const
{
	return materials[BACK];
}

void BasicsPreset::set_left_material_id(const int& value)
{
	materials[LEFT] = value;
}

int BasicsPreset::get_left_material_id() const
{
	return materials[LEFT];
}

void BasicsPreset::set_right_material_id(const int& value)
{
	materials[RIGHT] = value;
}

int BasicsPreset::get_right_material_id() const
{
	return materials[RIGHT];
}

int BasicsPreset::get_material_id(const int& value) const
{
	return materials[value];
}

void BasicsPreset::set_up_material_uv(const TypedArray<Vector2>& value)
{
	if (value.size() != 6)
	{
		return;
	}
	uvs[UP] = value;
}

TypedArray<Vector2> BasicsPreset::get_up_material_uv() const
{
	return uvs[UP];
}

void BasicsPreset::set_down_material_uv(const TypedArray<Vector2>& value)
{
	if (value.size() != 6)
	{
		return;
	}
	uvs[DOWN] = value;
}

TypedArray<Vector2> BasicsPreset::get_down_material_uv() const
{
	return uvs[DOWN];
}

void BasicsPreset::set_front_material_uv(const TypedArray<Vector2>& value)
{
	if (value.size() != 6)
	{
		return;
	}
	uvs[FRONT] = value;
}

TypedArray<Vector2> BasicsPreset::get_front_material_uv() const
{
	return uvs[FRONT];
}

void BasicsPreset::set_back_material_uv(const TypedArray<Vector2>& value)
{
	if (value.size() != 6)
	{
		return;
	}
	uvs[BACK] = value;
}

TypedArray<Vector2> BasicsPreset::get_back_material_uv() const
{
	return uvs[BACK];
}

void BasicsPreset::set_left_material_uv(const TypedArray<Vector2>& value)
{
	if (value.size() != 6)
	{
		return;
	}
	uvs[LEFT] = value;
}

TypedArray<Vector2> BasicsPreset::get_left_material_uv() const
{
	return uvs[LEFT];
}

void BasicsPreset::set_right_material_uv(const TypedArray<Vector2>& value)
{
	if (value.size() != 6)
	{
		return;
	}
	uvs[RIGHT] = value;
}

TypedArray<Vector2> BasicsPreset::get_right_material_uv() const
{
	return uvs[RIGHT];
}

Vector2 BasicsPreset::get_material_uv(const int& direction, const int& index) const
{
	return uvs[direction][index];
}
