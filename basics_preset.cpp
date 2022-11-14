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

	ClassDB::bind_static_method("BasicsPreset", D_METHOD("instantiate", "name", "materials"), &BasicsPreset::instantiate);

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
	filter = 0b01;
}

BasicsPreset::~BasicsPreset()
{
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

int BasicsPreset::get_material_id(const int& value) {
	return materials[value];
}

Ref<BasicsPreset> BasicsPreset::instantiate(const String& name, const Dictionary& materials)
{
	Ref<BasicsPreset> basics_preset;
	basics_preset.instantiate();
	basics_preset->name = name;

	basics_preset->set_up_material_id((int)materials.get(UP, 0));
	basics_preset->set_down_material_id((int)materials.get(DOWN, 0));
	basics_preset->set_front_material_id((int)materials.get(FRONT, 0));
	basics_preset->set_back_material_id((int)materials.get(BACK, 0));
	basics_preset->set_left_material_id((int)materials.get(LEFT, 0));
	basics_preset->set_right_material_id((int)materials.get(RIGHT, 0));

	return basics_preset;
}

static Vector2 uvs[] = {
	Vector2(0, 0), Vector2(1, 0), Vector2(1, 1),
	Vector2(0, 0), Vector2(1, 1), Vector2(0, 1),
};

static Vector3 brick_vertexs[][6] = {
	{
		Vector3(-0.5, 0.5, -0.5),Vector3(0.5, 0.5, -0.5),Vector3(0.5, 0.5, 0.5),
		Vector3(-0.5, 0.5, -0.5),Vector3(0.5, 0.5, 0.5),Vector3(-0.5, 0.5, 0.5),
	},
	{
		Vector3(0.5, -0.5, -0.5),Vector3(-0.5, -0.5, -0.5),Vector3(-0.5, -0.5, 0.5),
		Vector3(0.5, -0.5, -0.5),Vector3(-0.5, -0.5, 0.5),Vector3(0.5, -0.5, 0.5),
	},
	{
		Vector3(0.5, 0.5, -0.5),Vector3(-0.5, 0.5, -0.5),Vector3(-0.5, -0.5, -0.5),
		Vector3(0.5, 0.5, -0.5),Vector3(-0.5, -0.5, -0.5),Vector3(0.5, -0.5, -0.5),
	},
	{
		Vector3(-0.5, 0.5, 0.5),Vector3(0.5, 0.5, 0.5),Vector3(0.5, -0.5, 0.5),
		Vector3(-0.5, 0.5, 0.5),Vector3(0.5, -0.5, 0.5),Vector3(-0.5, -0.5, 0.5),
	},
	{
		Vector3(-0.5, 0.5, -0.5),Vector3(-0.5, 0.5, 0.5),Vector3(-0.5, -0.5, 0.5),
		Vector3(-0.5, 0.5, -0.5),Vector3(-0.5, -0.5, 0.5),Vector3(-0.5, -0.5, -0.5),
	},
	{
		Vector3(0.5, 0.5, 0.5), Vector3(0.5, 0.5, -0.5), Vector3(0.5, -0.5, -0.5),
		Vector3(0.5, 0.5, 0.5), Vector3(0.5, -0.5, -0.5), Vector3(0.5, -0.5, 0.5),
	}
};

static BasicsPreset::BasicsData* basics_data_memorandum[24 * 24 * 24] = { nullptr };
void BasicsPreset::build_mesh(const int& direction, const Array& arrays, const Vector3& position, const Vector3& rotation)
{
	int index = (rotation.x / 15 * 24 * 24 + rotation.y / 15 * 24 + rotation.z / 15);
	BasicsData* basics_mesh_data = basics_data_memorandum[index];
	if (basics_mesh_data == nullptr)
	{
		basics_mesh_data = (BasicsData*)memalloc(sizeof(BasicsData));
		for (int i = 0; i < 6; i++)
		{
			Vector3 vertexs[6];
			for (int j = 0; j < 6; j++)
			{
				basics_mesh_data->vertexs[i][j] = (vertexs[j] = rotate_vertex(brick_vertexs[i][j], rotation));
			}
			basics_mesh_data->normals[i][0] = Plane(vertexs[0], vertexs[1], vertexs[2]).get_normal();
			basics_mesh_data->normals[i][1] = Plane(vertexs[3], vertexs[4], vertexs[5]).get_normal();
		}
		basics_data_memorandum[index] = basics_mesh_data;
	}

	Array array_vertex = arrays[Mesh::ARRAY_VERTEX];
	Array array_normal = arrays[Mesh::ARRAY_NORMAL];
	Array array_tex_uv = arrays[Mesh::ARRAY_TEX_UV];
	for (int i = 0; i < 6; i++)
	{
		array_vertex.push_back(basics_mesh_data->vertexs[direction][i] + position);
	}

	for (int i = 0; i < 3; i++)
	{
		array_normal.push_back(basics_mesh_data->normals[direction][0]);
	}
	for (int i = 0; i < 3; i++)
	{
		array_normal.push_back(basics_mesh_data->normals[direction][1]);
	}
	for (int i = 0; i < 6; i++)
	{
		array_tex_uv.push_back(uvs[i]);
	}
}