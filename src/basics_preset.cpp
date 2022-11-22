#include "basics_preset.h"

void BasicsPreset::_bind_methods()
{
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


	ADD_PROPERTY(PropertyInfo(Variant::INT, "up_material_id"), "set_up_material_id", "get_up_material_id");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "down_material_id"), "set_down_material_id", "get_down_material_id");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "front_material_id"), "set_front_material_id", "get_front_material_id");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "back_material_id"), "set_back_material_id", "get_back_material_id");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "left_material_id"), "set_left_material_id", "get_left_material_id");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "right_material_id"), "set_right_material_id", "get_right_material_id");

	BIND_ENUM_CONSTANT(UP);
	BIND_ENUM_CONSTANT(DOWN);
	BIND_ENUM_CONSTANT(FRONT);
	BIND_ENUM_CONSTANT(BACK);
	BIND_ENUM_CONSTANT(LEFT);
	BIND_ENUM_CONSTANT(RIGHT);
}

BasicsPreset::BasicsPreset()
{
	materials[0] = materials[1] = materials[2] = materials[3] = materials[4] = materials[5] = 0;
}

BasicsPreset::~BasicsPreset()
{
}

void BasicsPreset::set_up_material_id(const int &value)
{
	materials[UP] = value;
}

int BasicsPreset::get_up_material_id() const
{
	return materials[UP];
}

void BasicsPreset::set_down_material_id(const int &value)
{
	materials[DOWN] = value;
}

int BasicsPreset::get_down_material_id() const
{
	return materials[DOWN];
}

void BasicsPreset::set_front_material_id(const int &value)
{
	materials[FRONT] = value;
}

int BasicsPreset::get_front_material_id() const
{
	return materials[FRONT];
}

void BasicsPreset::set_back_material_id(const int &value)
{
	materials[BACK] = value;
}

int BasicsPreset::get_back_material_id() const
{
	return materials[BACK];
}

void BasicsPreset::set_left_material_id(const int &value)
{
	materials[LEFT] = value;
}

int BasicsPreset::get_left_material_id() const
{
	return materials[LEFT];
}

void BasicsPreset::set_right_material_id(const int &value)
{
	materials[RIGHT] = value;
}

int BasicsPreset::get_right_material_id() const
{
	return materials[RIGHT];
}

int BasicsPreset::get_material_id(const int &value)
{
	return materials[value];
}