#include "simple_voxel_block_data.h"

void SimpleVoxelBlockData::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_size", "value"), &SimpleVoxelBlockData::set_size);
	ClassDB::bind_method(D_METHOD("get_size"), &SimpleVoxelBlockData::get_size);

	ClassDB::bind_method(D_METHOD("set_voxels", "value"), &SimpleVoxelBlockData::set_voxels);
	ClassDB::bind_method(D_METHOD("get_voxels"), &SimpleVoxelBlockData::get_voxels);

	ClassDB::bind_method(D_METHOD("set_voxel", "position", "value"), &SimpleVoxelBlockData::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel", "position"), &SimpleVoxelBlockData::get_voxel);

	ClassDB::bind_method(D_METHOD("fill", "voxel"), &SimpleVoxelBlockData::fill);
	ClassDB::bind_method(D_METHOD("is_filled", "voxel"), &SimpleVoxelBlockData::is_filled);

	ClassDB::bind_method(D_METHOD("get_voxel_type", "value"), &SimpleVoxelBlockData::get_voxel_type);
	ClassDB::bind_method(D_METHOD("get_voxel_id", "value"), &SimpleVoxelBlockData::get_voxel_id);
	ClassDB::bind_method(D_METHOD("get_voxel_height", "value"), &SimpleVoxelBlockData::get_voxel_height);

	ClassDB::bind_method(D_METHOD("empty_voxel"), &SimpleVoxelBlockData::empty_voxel);
	ClassDB::bind_method(D_METHOD("basics_voxel", "id", "height"), &SimpleVoxelBlockData::basics_voxel, 64);
	ClassDB::bind_method(D_METHOD("model_voxel", "id", "height"), &SimpleVoxelBlockData::model_voxel, 64);
	ClassDB::bind_method(D_METHOD("device_voxel", "id", "height"), &SimpleVoxelBlockData::device_voxel, 64);

	ADD_PROPERTY(PropertyInfo(Variant::PACKED_INT32_ARRAY, "voxels"), "set_voxels", "get_voxels");
}

SimpleVoxelBlockData::SimpleVoxelBlockData()
{
	set_size(Vector3i(8, 8, 8));
}

SimpleVoxelBlockData::~SimpleVoxelBlockData()
{
}

void SimpleVoxelBlockData::set_size(const Vector3i& value)
{
	VoxelBlockData::set_size(value);
	voxels.resize(size.x * size.y * size.z * 2);
}

Vector3i SimpleVoxelBlockData::get_size() const
{
	return size;
}

void SimpleVoxelBlockData::set_voxels(const PackedByteArray& value)
{
	voxels = value.decompress(4096);
	if (voxels.size() != size.x * size.y * size.z)
	{
		voxels.resize(size.x * size.y * size.z * 2);
	}
}

PackedByteArray SimpleVoxelBlockData::get_voxels() const
{
	return voxels.compress();
}

void SimpleVoxelBlockData::set_voxel(const Vector3i& position, const Voxel& value)
{
	if (position.x >= 0 && position.x < size.x &&
		position.y >= 0 && position.y < size.y &&
		position.z >= 0 && position.z < size.z)
	{
		int index = ((position.x * size.y * size.z) + (position.y * size.z) + position.z) * 2;
		voxels[index] = value >> 8;
		voxels[index + 1] = value;
	}
}

Voxel SimpleVoxelBlockData::get_voxel(const Vector3i& position) const
{
	if (position.x >= 0 && position.x < size.x &&
		position.y >= 0 && position.y < size.y &&
		position.z >= 0 && position.z < size.z)
	{
		int index = ((position.x * size.y * size.z) + (position.y * size.z) + position.z) * 2;
		return voxels[index] << 8 | voxels[index + 1];
	}
	return EMPTY_VOXEL;
}

void SimpleVoxelBlockData::fill(const Voxel& voxel)
{
	for (int i = 0; i < voxels.size(); i += 2)
	{
		voxels[i] = voxel >> 8;
		voxels[i + 1] = voxel;
	}
}

bool SimpleVoxelBlockData::is_filled(const Voxel& voxel) const
{
	for (int i = 0; i < voxels.size(); i += 2)
	{
		if ((voxels[i] << 8 | voxels[i + 1]) != voxel)
		{
			return false;
		}
	}
	return true;
}

void SimpleVoxelBlockData::build_basics_mesh(const int& direction, const int& height, const Array& mesh_arrays, const Vector3& position)
{
	static Vector2 uvs[] = {
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 0),
		Vector2(1, 1),
		Vector2(0, 1),
	};
	static Vector3 vertexs[][6] = {
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

	Array array_vertex = mesh_arrays[Mesh::ARRAY_VERTEX];
	Array array_normal = mesh_arrays[Mesh::ARRAY_NORMAL];
	Array array_tex_uv = mesh_arrays[Mesh::ARRAY_TEX_UV];
	for (int i = 0; i < 6; i++)
	{
		Vector3 vertex = vertexs[direction][i];
		vertex.y *= (height / static_cast<float>(64));
		vertex.y -= ((64 - height) / static_cast<float>(64)) / 2;
		array_vertex.push_back(vertex + position);
	}
	for (int i = 0; i < 6; i++)
	{
		array_normal.push_back(DIRCTIONS[direction]);
	}
	if (direction > 1)
	{
		for (int i = 0; i < 6; i++)
		{
			Vector2 uv = uvs[i];
			if (uv.y == 0)
			{
				uv.y = ((64 - height) / static_cast<float>(64));
			}
			array_tex_uv.push_back(uv);
		}
	}
	else {
		for (int i = 0; i < 6; i++)
		{
			array_tex_uv.push_back(uvs[i]);
		}
	}
}

void SimpleVoxelBlockData::build_model_mesh(Ref<ModelPreset>& model_preset, const Array& mesh_arrays, const Vector3& position)
{
	Ref<Mesh> mesh = model_preset->get_mesh();
	ERR_FAIL_NULL(mesh);
	TypedArray<int> materials = model_preset->get_materials();
	for (int i = 0; i < mesh->get_surface_count(); i++)
	{
		int material_id = materials[i];
		ERR_FAIL_INDEX(material_id, mesh_arrays.size());
		Array arrays = mesh_arrays[material_id];
		model_preset->build_mesh(arrays, i, position, Vector3i());
	}
}

void SimpleVoxelBlockData::build_mesh(const Ref<PresetsData>& presets_data, const Array& mesh_arrays, const Vector3i& position, const Voxel& voxel)
{
	int type = get_voxel_type(voxel);
	switch (type)
	{
	case BASICS:
	{
		TypedArray<BasicsPreset> basics_presets = presets_data->get_basics_presets();
		int id = get_voxel_id(voxel);
		int height = get_voxel_height(voxel);

		Ref<BasicsPreset> basics_preset = basics_presets[id];
		ERR_FAIL_NULL_MSG(basics_preset, "The basics_preset with id " + String::num_int64(id) + " is null");

		for (int direction = 2; direction < 6; direction++) {
			Voxel relative_voxel = get_voxel(position + DIRCTIONS[direction]);
			int relative_voxel_type = get_voxel_type(relative_voxel);
			if (relative_voxel_type != BASICS) {
				int material_id = basics_preset->get_material_id(direction);
				ERR_FAIL_INDEX(material_id, mesh_arrays.size());
				Array arrays = mesh_arrays[material_id];
				build_basics_mesh(direction, height, arrays, position);
			}
			else {
				int relative_voxel_id = get_voxel_type(relative_voxel);
				Ref<BasicsPreset> relative_basics_preset = basics_presets[relative_voxel_id];
				int relative_voxel_height = get_voxel_height(relative_voxel);
				if (relative_basics_preset->get_transparent() != basics_preset->get_transparent() || height != relative_voxel_height) {
					int material_id = basics_preset->get_material_id(direction);
					ERR_FAIL_INDEX(material_id, mesh_arrays.size());
					Array arrays = mesh_arrays[material_id];
					build_basics_mesh(direction, height, arrays, position);
				}
			}
		}

		Voxel up_voxel = get_voxel(position + DIRCTIONS[BasicsPreset::UP]);
		int up_voxel_type = get_voxel_type(up_voxel);
		if (up_voxel_type != BASICS)
		{
			int material_id = basics_preset->get_material_id(BasicsPreset::UP);
			ERR_FAIL_INDEX(material_id, mesh_arrays.size());
			Array arrays = mesh_arrays[material_id];
			build_basics_mesh(BasicsPreset::UP, height, arrays, position);
		}
		else
		{
			int up_voxel_id = get_voxel_type(up_voxel);
			Ref<BasicsPreset> up_basics_preset = basics_presets[up_voxel_id];
			if (up_basics_preset->get_transparent() != basics_preset->get_transparent() || height != 64) {
				int material_id = basics_preset->get_material_id(BasicsPreset::UP);
				ERR_FAIL_INDEX(material_id, mesh_arrays.size());
				Array arrays = mesh_arrays[material_id];
				build_basics_mesh(BasicsPreset::UP, height, arrays, position);
			}
		}

		Voxel down_voxel = get_voxel(position + DIRCTIONS[BasicsPreset::DOWN]);
		int down_voxel_type = get_voxel_type(down_voxel);
		if (down_voxel_type != BASICS)
		{
			int material_id = basics_preset->get_material_id(BasicsPreset::DOWN);
			ERR_FAIL_INDEX(material_id, mesh_arrays.size());
			Array arrays = mesh_arrays[material_id];
			build_basics_mesh(BasicsPreset::DOWN, height, arrays, position);
		}
		else
		{
			int down_voxel_id = get_voxel_type(down_voxel);
			int down_voxel_height = get_voxel_height(down_voxel);
			Ref<BasicsPreset> down_basics_preset = basics_presets[down_voxel_id];
			if (down_basics_preset->get_transparent() != basics_preset->get_transparent() || down_voxel_height != 64) {
				int material_id = basics_preset->get_material_id(BasicsPreset::DOWN);
				ERR_FAIL_INDEX(material_id, mesh_arrays.size());
				Array arrays = mesh_arrays[material_id];
				build_basics_mesh(BasicsPreset::DOWN, height, arrays, position);
			}
		}
		break;
	}
	case MODEL:
	{
		TypedArray<ModelPreset> model_presets = presets_data->get_model_presets();
		int id = get_voxel_id(voxel);

		Ref<ModelPreset> model_preset = model_presets[id];
		ERR_FAIL_NULL_MSG(model_preset, "The model_preset with id " + String::num_int64(id) + " is null");
		build_model_mesh(model_preset, mesh_arrays, position);
		break;
	}
	}
}

Variant SimpleVoxelBlockData::build_device(const Ref<DevicePreset>& device_preset, Vector3i& position)
{
	Node* node = device_preset->get_packed_scene()->instantiate();
	Device* device = cast_to<Device>(node);
	if (device == nullptr)
	{
		node->queue_free();
	}
	device->set_device_preset(device_preset);

	device->set_position(position);
	call_deferred("add_child", device);
	return device;
}

int SimpleVoxelBlockData::get_voxel_type(const Voxel& value)
{
	return (value & 0b11'000000'00000000) >> 14;
}

int SimpleVoxelBlockData::get_voxel_id(const Voxel& value)
{
	return ((value & 0b00'000000'11111111));
}

int SimpleVoxelBlockData::get_voxel_height(const Voxel& value)
{
	return ((value & 0b00'111111'00000000) >> 8) + 1;
}

Voxel SimpleVoxelBlockData::empty_voxel()
{
	return EMPTY_VOXEL;
}

Voxel SimpleVoxelBlockData::basics_voxel(const int& id, const int& height)
{
	return SIMPLE_BASICS_VOXEL(id, height);
}

Voxel SimpleVoxelBlockData::model_voxel(const int& id, const int& height)
{
	return SIMPLE_MODEL_VOXEL(id, height);
}

Voxel SimpleVoxelBlockData::device_voxel(const int& id, const int& height)
{
	return SIMPLE_DEVICE_VOXEL(id, height);
}
