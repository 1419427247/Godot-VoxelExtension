#include "standard_voxel_block_data.h"

void StandardVoxelBlockData::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_size", "value"), &StandardVoxelBlockData::set_size);
	ClassDB::bind_method(D_METHOD("get_size"), &StandardVoxelBlockData::get_size);

	ClassDB::bind_method(D_METHOD("set_voxels", "value"), &StandardVoxelBlockData::set_voxels);
	ClassDB::bind_method(D_METHOD("get_voxels"), &StandardVoxelBlockData::get_voxels);

	ClassDB::bind_method(D_METHOD("set_voxel", "position", "value"), &StandardVoxelBlockData::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel", "position"), &StandardVoxelBlockData::get_voxel);

	ClassDB::bind_method(D_METHOD("fill", "voxel"), &StandardVoxelBlockData::fill);
	ClassDB::bind_method(D_METHOD("is_filled", "voxel"), &StandardVoxelBlockData::is_filled);

	ClassDB::bind_method(D_METHOD("get_voxel_type", "value"), &StandardVoxelBlockData::get_voxel_type);
	ClassDB::bind_method(D_METHOD("get_voxel_id", "value"), &StandardVoxelBlockData::get_voxel_id);

	ClassDB::bind_method(D_METHOD("get_voxel_direction", "direction", "rotation"), &StandardVoxelBlockData::get_voxel_direction);
	ClassDB::bind_method(D_METHOD("get_voxel_rotation", "value"), &StandardVoxelBlockData::get_voxel_rotation);
	ClassDB::bind_method(D_METHOD("empty_voxel"), &StandardVoxelBlockData::empty_voxel);
	ClassDB::bind_method(D_METHOD("basics_voxel", "id", "rotation"), &StandardVoxelBlockData::basics_voxel, Vector3i());
	ClassDB::bind_method(D_METHOD("model_voxel", "id", "rotation"), &StandardVoxelBlockData::model_voxel, Vector3i());
	ClassDB::bind_method(D_METHOD("device_voxel", "id", "rotation"), &StandardVoxelBlockData::device_voxel, Vector3i());

	ADD_PROPERTY(PropertyInfo(Variant::PACKED_INT32_ARRAY, "voxels"), "set_voxels", "get_voxels");
}

StandardVoxelBlockData::StandardVoxelBlockData()
{
	set_size(Vector3i(8, 8, 8));
}

StandardVoxelBlockData::~StandardVoxelBlockData()
{
}


void StandardVoxelBlockData::set_size(const Vector3i& value) {
	VoxelBlockData::set_size(value);
	voxels.resize(size.x * size.y * size.z);
}

Vector3i StandardVoxelBlockData::get_size() const {
	return VoxelBlockData::get_size();
}

void StandardVoxelBlockData::set_voxels(const PackedByteArray& value)
{
	voxels = value.decompress(4096).to_int32_array();
	if (voxels.size() != size.x * size.y * size.z)
	{
		voxels.resize(size.x * size.y * size.z);
	}
}

PackedByteArray StandardVoxelBlockData::get_voxels() const
{
	return voxels.to_byte_array().compress();
}

void StandardVoxelBlockData::set_voxel(const Vector3i& position, const Voxel& value)
{
	if (position.x >= 0 && position.x < size.x &&
		position.y >= 0 && position.y < size.y &&
		position.z >= 0 && position.z < size.z)
	{
		int index = ((position.x * size.y * size.z) + (position.y * size.z) + position.z);
		voxels[index] = value;
	}
}

Voxel StandardVoxelBlockData::get_voxel(const Vector3i& position) const
{
	if (position.x >= 0 && position.x < size.x &&
		position.y >= 0 && position.y < size.y &&
		position.z >= 0 && position.z < size.z)
	{
		int index = ((position.x * size.y * size.z) + (position.y * size.z) + position.z);
		return voxels[index];
	}
	return EMPTY_VOXEL;
}

void StandardVoxelBlockData::fill(const Voxel& voxel)
{
	for (int i = 0; i < size.x * size.y * size.z; i++)
	{
		voxels[i] = voxel;
	}
}

bool StandardVoxelBlockData::is_filled(const Voxel& voxel) const
{
	for (int i = 0; i < voxels.size(); i++)
	{
		if (voxels[i] != voxel)
		{
			return false;
		}
	}
	return true;
}

void StandardVoxelBlockData::build_basics_mesh(const int& direction, const Array& mesh_arrays, const Vector3& position, const Vector3& rotation)
{
	struct MemorandumData
	{
		Vector3 vertexs[6][6];
		Vector3 normals[6];
	};
	static Vector2 uvs[] = {
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 0),
		Vector2(1, 1),
		Vector2(0, 1),
	};
	static Vector3 brick_vertexs[][6] = {
		{
			Vector3(-0.5, 0.5, -0.5),
			Vector3(0.5, 0.5, -0.5),
			Vector3(0.5, 0.5, 0.5),
			Vector3(-0.5, 0.5, -0.5),
			Vector3(0.5, 0.5, 0.5),
			Vector3(-0.5, 0.5, 0.5),
		},
		{
			Vector3(0.5, -0.5, -0.5),
			Vector3(-0.5, -0.5, -0.5),
			Vector3(-0.5, -0.5, 0.5),
			Vector3(0.5, -0.5, -0.5),
			Vector3(-0.5, -0.5, 0.5),
			Vector3(0.5, -0.5, 0.5),
		},
		{
			Vector3(0.5, 0.5, -0.5),
			Vector3(-0.5, 0.5, -0.5),
			Vector3(-0.5, -0.5, -0.5),
			Vector3(0.5, 0.5, -0.5),
			Vector3(-0.5, -0.5, -0.5),
			Vector3(0.5, -0.5, -0.5),
		},
		{
			Vector3(-0.5, 0.5, 0.5),
			Vector3(0.5, 0.5, 0.5),
			Vector3(0.5, -0.5, 0.5),
			Vector3(-0.5, 0.5, 0.5),
			Vector3(0.5, -0.5, 0.5),
			Vector3(-0.5, -0.5, 0.5),
		},
		{
			Vector3(-0.5, 0.5, -0.5),
			Vector3(-0.5, 0.5, 0.5),
			Vector3(-0.5, -0.5, 0.5),
			Vector3(-0.5, 0.5, -0.5),
			Vector3(-0.5, -0.5, 0.5),
			Vector3(-0.5, -0.5, -0.5),
		},
		{
			Vector3(0.5, 0.5, 0.5),
			Vector3(0.5, 0.5, -0.5),
			Vector3(0.5, -0.5, -0.5),
			Vector3(0.5, 0.5, 0.5),
			Vector3(0.5, -0.5, -0.5),
			Vector3(0.5, -0.5, 0.5),
		} };
	static MemorandumData* memorandum[24 * 24 * 24] = { nullptr };
	int index = (rotation.x / 15 * 24 * 24 + rotation.y / 15 * 24 + rotation.z / 15);
	MemorandumData* data = memorandum[index];
	if (data == nullptr)
	{
		data = (MemorandumData*)memalloc(sizeof(MemorandumData));
		for (int i = 0; i < 6; i++)
		{
			Vector3 vertexs[6];
			for (int j = 0; j < 6; j++)
			{
				data->vertexs[i][j] = (vertexs[j] = rotate_vertex(brick_vertexs[i][j], rotation));
			}
			data->normals[i] = Plane(vertexs[0], vertexs[1], vertexs[2]).get_normal();
			//data->normals[i][1] = Plane(vertexs[3], vertexs[4], vertexs[5]).get_normal();
		}
		memorandum[index] = data;
	}

	Array array_vertex = mesh_arrays[Mesh::ARRAY_VERTEX];
	Array array_normal = mesh_arrays[Mesh::ARRAY_NORMAL];
	Array array_tex_uv = mesh_arrays[Mesh::ARRAY_TEX_UV];
	for (int i = 0; i < 6; i++)
	{
		array_vertex.push_back(data->vertexs[direction][i] + position);
	}
	for (int i = 0; i < 6; i++)
	{
		array_normal.push_back(data->normals[direction]);
	}
	for (int i = 0; i < 6; i++)
	{
		array_tex_uv.push_back(uvs[i]);
	}
}

void StandardVoxelBlockData::build_model_mesh(Ref<ModelPreset>& model_preset, const Array& mesh_arrays, const Vector3& position, const Vector3& rotation)
{
	Ref<Mesh> mesh = model_preset->get_mesh();
	ERR_FAIL_NULL(mesh);
	TypedArray<int> materials = model_preset->get_materials();
	for (int i = 0; i < mesh->get_surface_count(); i++)
	{
		int material_id = materials[i];
		ERR_FAIL_INDEX(material_id, mesh_arrays.size());
		Array arrays = mesh_arrays[material_id];
		model_preset->build_mesh(arrays, i, position, rotation);
	}
}



void StandardVoxelBlockData::build_mesh(const Ref<PresetsData>& presets_data, const Array& mesh_arrays, const Vector3i& position, const Voxel& voxel)
{
	int type = get_voxel_type(voxel);
	switch (type)
	{
	case BASICS:
	{
		TypedArray<BasicsPreset> basics_presets = presets_data->get_basics_presets();
		int id = get_voxel_id(voxel);

		Ref<BasicsPreset> basics_preset = basics_presets[id];
		ERR_FAIL_NULL_MSG(basics_preset, "The basics_preset with id " + String::num_int64(id) + " is null");
		Vector3i rotation = get_voxel_rotation(voxel);
		if (rotation.x % 90 != 0 || rotation.y % 90 != 0 || rotation.z % 90 != 0)
		{
			for (int direction = 0; direction < 6; direction++)
			{
				int material_id = basics_preset->get_material_id(direction);
				ERR_FAIL_INDEX(material_id, mesh_arrays.size());
				Array arrays = mesh_arrays[material_id];
				build_basics_mesh(direction, arrays, position, rotation);
			}
		}
		else {
			for (int direction = 0; direction < 6; direction++) {
				Voxel voxel = get_voxel(position + get_voxel_direction(direction, rotation));
				int type = get_voxel_type(voxel);
				int id = get_voxel_id(voxel);

				if (type != BASICS) {
					int material_id = basics_preset->get_material_id(direction);
					ERR_FAIL_INDEX(material_id, mesh_arrays.size());
					Array arrays = mesh_arrays[material_id];
					build_basics_mesh(direction, arrays, position, rotation);
				}
				else {
					Vector3i voxel_rotation = get_voxel_rotation(voxel);
					Ref<BasicsPreset> preset = basics_presets[id];
					if (preset->get_transparent() != basics_preset->get_transparent() || voxel_rotation.x % 90 != 0 || voxel_rotation.y % 90 != 0 || voxel_rotation.z % 90 != 0) {
						int material_id = basics_preset->get_material_id(direction);
						ERR_FAIL_INDEX(material_id, mesh_arrays.size());
						Array arrays = mesh_arrays[material_id];
						build_basics_mesh(direction, arrays, position, rotation);
					}
				}
			}
		}
		break;
	}
	case MODEL:
	{
		TypedArray<BasicsPreset> model_presets = presets_data->get_model_presets();
		int id = get_voxel_id(voxel);

		Ref<ModelPreset> model_preset = model_presets[id];
		ERR_FAIL_NULL_MSG(model_preset, "The model_preset with id " + String::num_int64(id) + " is null");
		Vector3i rotation = get_voxel_rotation(voxel);
		build_model_mesh(model_preset, mesh_arrays, position, rotation);
		break;
	}
	}
}

Variant StandardVoxelBlockData::build_device(const Ref<DevicePreset>& device_preset, Vector3i& position, const Voxel& voxel)
{
	Vector3i rotation = get_voxel_rotation(voxel);
	Node* node = device_preset->get_packed_scene()->instantiate();
	Device* device = cast_to<Device>(node);
	if (device == nullptr)
	{
		node->queue_free();
	}
	device->set_device_preset(device_preset);

	device->set_position(position);
	device->set_rotation(rotation);
	call_deferred("add_child", device);
	return device;
}

int StandardVoxelBlockData::get_voxel_type(const Voxel& value)
{
	return value >> 30;
}

int StandardVoxelBlockData::get_voxel_id(const Voxel& value)
{
	return (value & 0b00'111111111111111'000000000000000) >> 15;
}

Vector3i StandardVoxelBlockData::get_voxel_rotation(const Voxel& value)
{
	return Vector3i((value & 0b00'000000000000000'11111'00000'00000) >> 10, (value & 0b00'000000000000000'00000'11111'00000) >> 5, (value & 0b00'000000000000000'00000'00000'11111) << 27) * 15;
}

Vector3i StandardVoxelBlockData::get_voxel_direction(const int& direction, const Vector3i& rotation)
{
	static Vector3 memorandum[6][24 * 24 * 24] = { Vector3() };
	Vector3* result = &memorandum[direction][rotation.x / 15 * 24 * 24 + rotation.y / 15 * 24 + rotation.z / 15];
	if (*result == Vector3i())
	{
		*result = DIRCTIONS[direction];
		result->rotate(Vector3(0, 1, 0), UtilityFunctions::deg_to_rad(rotation.y));
		result->rotate(Vector3(1, 0, 0), UtilityFunctions::deg_to_rad(rotation.x));
		result->rotate(Vector3(0, 0, 1), UtilityFunctions::deg_to_rad(rotation.z));
	}
	return Vector3i(*result);
}

Voxel StandardVoxelBlockData::empty_voxel()
{
	return EMPTY_VOXEL;
}

Voxel StandardVoxelBlockData::basics_voxel(const int& id, const Vector3i& rotation)
{
	return STANDARD_BASICS_VOXEL(id, rotation);
}

Voxel StandardVoxelBlockData::model_voxel(const int& id, const Vector3i& rotation)
{
	return STANDARD_MODEL_VOXEL(id, rotation);
}

Voxel StandardVoxelBlockData::device_voxel(const int& id, const Vector3i& rotation)
{
	return STANDARD_DEVICE_VOXEL(id, rotation);
}