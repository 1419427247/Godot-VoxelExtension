#include "standard_voxel_block_data.h"

void StandardVoxelBlockData::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_size", "value"), &StandardVoxelBlockData::set_size);
	ClassDB::bind_method(D_METHOD("get_size"), &StandardVoxelBlockData::get_size);

	ClassDB::bind_method(D_METHOD("set_voxels_data", "value"), &StandardVoxelBlockData::set_voxels_data);
	ClassDB::bind_method(D_METHOD("get_voxels_data"), &StandardVoxelBlockData::get_voxels_data);

	ClassDB::bind_method(D_METHOD("set_voxel", "position", "value"), &StandardVoxelBlockData::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel", "position"), &StandardVoxelBlockData::get_voxel);

	ClassDB::bind_method(D_METHOD("fill", "voxel"), &StandardVoxelBlockData::fill);
	ClassDB::bind_method(D_METHOD("is_filled", "voxel"), &StandardVoxelBlockData::is_filled);

	ClassDB::bind_static_method("StandardVoxelBlockData", D_METHOD("get_voxel_type", "value"), &StandardVoxelBlockData::get_voxel_type);
	ClassDB::bind_static_method("StandardVoxelBlockData", D_METHOD("get_voxel_id", "value"), &StandardVoxelBlockData::get_voxel_id);
	ClassDB::bind_static_method("StandardVoxelBlockData", D_METHOD("get_voxel_direction", "direction", "rotation"), &StandardVoxelBlockData::get_voxel_direction);
	ClassDB::bind_static_method("StandardVoxelBlockData", D_METHOD("get_voxel_rotation", "value"), &StandardVoxelBlockData::get_voxel_rotation);

	ClassDB::bind_static_method("StandardVoxelBlockData", D_METHOD("empty_voxel"), &StandardVoxelBlockData::empty_voxel);
	ClassDB::bind_static_method("StandardVoxelBlockData", D_METHOD("basics_voxel", "id", "rotation"), &StandardVoxelBlockData::basics_voxel, Vector3i());
	ClassDB::bind_static_method("StandardVoxelBlockData", D_METHOD("model_voxel", "id", "rotation"), &StandardVoxelBlockData::model_voxel, Vector3i());
	ClassDB::bind_static_method("StandardVoxelBlockData", D_METHOD("device_voxel", "id", "rotation"), &StandardVoxelBlockData::device_voxel, Vector3i());
}

void StandardVoxelBlockData::_basics_mesh(const Ref<MeshPreset>& mesh_preset, const Array& mesh_arrays, const int& direction, const Vector3& position, const Vector3& rotation)
{
	struct MemorandumData
	{
		Vector3 vertexs[6][6];
		Vector3 normals[6];
		float tangents[6][4];
	};
	static Vector2 basics_uvs[] = {
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 0),
		Vector2(1, 1),
		Vector2(0, 1),
	};
	static Vector3 basics_vertexs[][6] = {
		{
			Vector3(0.5, 0.5, 0.5),
			Vector3(-0.5, 0.5, 0.5),
			Vector3(-0.5, 0.5, -0.5),
			Vector3(0.5, 0.5, 0.5),
			Vector3(-0.5, 0.5, -0.5),
			Vector3(0.5, 0.5, -0.5),
		},
		{
			Vector3(-0.5, -0.5, 0.5),
			Vector3(0.5, -0.5, 0.5),
			Vector3(0.5, -0.5, -0.5),
			Vector3(-0.5, -0.5, 0.5),
			Vector3(0.5, -0.5, -0.5),
			Vector3(-0.5, -0.5, -0.5),
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
			Vector3(0.5, 0.5, -0.5),
			Vector3(-0.5, 0.5, -0.5),
			Vector3(-0.5, -0.5, -0.5),
			Vector3(0.5, 0.5, -0.5),
			Vector3(-0.5, -0.5, -0.5),
			Vector3(0.5, -0.5, -0.5),
		},
		{
			Vector3(0.5, 0.5, 0.5),
			Vector3(0.5, 0.5, -0.5),
			Vector3(0.5, -0.5, -0.5),
			Vector3(0.5, 0.5, 0.5),
			Vector3(0.5, -0.5, -0.5),
			Vector3(0.5, -0.5, 0.5),
		},
		{
			Vector3(-0.5, 0.5, -0.5),
			Vector3(-0.5, 0.5, 0.5),
			Vector3(-0.5, -0.5, 0.5),
			Vector3(-0.5, 0.5, -0.5),
			Vector3(-0.5, -0.5, 0.5),
			Vector3(-0.5, -0.5, -0.5),
		}
	};

	static MemorandumData* memorandum[24 * 24 * 24] = { nullptr };

	if (mesh_preset.is_null()) {
		int index = (rotation.x / 15 * 24 * 24 + rotation.y / 15 * 24 + rotation.z / 15);
		MemorandumData* data = memorandum[index];
		if (data == nullptr)
		{
			data = (MemorandumData*)memalloc(sizeof(MemorandumData));
			for (int i = 0; i < 6; i++)
			{
				Vector3 vertexs[3] = {
					data->vertexs[i][0] = MeshPreset::rotate_vertex(basics_vertexs[i][0],rotation),
					data->vertexs[i][1] = MeshPreset::rotate_vertex(basics_vertexs[i][1],rotation),	
					data->vertexs[i][2] = MeshPreset::rotate_vertex(basics_vertexs[i][2],rotation),
				};
				Vector2 uvs[3] = {
					basics_uvs[0],
					basics_uvs[1],
					basics_uvs[2],
				};
				Vector3 tangent;
				Vector3 binormal;
				Vector3 normal;
				MeshPreset::get_tbn(vertexs, uvs, &tangent, &binormal, &normal);

				data->normals[i] = normal;

				data->tangents[i][0] = tangent.x;
				data->tangents[i][1] = tangent.y;
				data->tangents[i][2] = tangent.z;
				data->tangents[i][3] = binormal.dot(normal.cross(tangent)) < 0 ? -1 : 1;

				data->vertexs[i][3] = MeshPreset::rotate_vertex(basics_vertexs[i][3], rotation);
				data->vertexs[i][4] = MeshPreset::rotate_vertex(basics_vertexs[i][4], rotation);
				data->vertexs[i][5] = MeshPreset::rotate_vertex(basics_vertexs[i][5], rotation);
			}
		}
		memorandum[index] = data;
		Array array_vertex = mesh_arrays[Mesh::ARRAY_VERTEX];
		Array array_normal = mesh_arrays[Mesh::ARRAY_NORMAL];
		Array tangent_array = mesh_arrays[Mesh::ARRAY_TANGENT];
		Array array_tex_uv = mesh_arrays[Mesh::ARRAY_TEX_UV];

		for (int i = 0; i < 6; i++)
		{
			array_vertex.push_back(data->vertexs[direction][i] + position);
			array_normal.push_back(data->normals[direction]);
			for (int j = 0; j < 4; j++)
			{
				tangent_array.push_back(data->tangents[direction][j]);
			}
			array_tex_uv.push_back(basics_uvs[i]);
		}
	}
	else {
		mesh_preset->build_mesh(mesh_arrays, direction, position, rotation);
	}
}

void StandardVoxelBlockData::_model_mesh(const Ref<ModelPreset>& model_preset, const Array& mesh_arrays, const int& mask, const Vector3& position, const Vector3& rotation)
{
	TypedArray<MeshPreset> mesh_presets = model_preset->get_mesh_preset();
	Ref<MeshPreset> model_mesh = mesh_presets[mask];
	if (model_mesh == nullptr)
	{
		model_mesh = mesh_presets[0];
	}
	ERR_FAIL_NULL(model_mesh);
	Ref<Mesh> mesh = model_mesh->get_mesh();
	if (mesh == nullptr)
	{
		return;
	}
	TypedArray<int> materials = model_mesh->get_materials();
	for (int i = 0; i < mesh->get_surface_count(); i++)
	{
		int material_id = materials[i];
		ERR_FAIL_INDEX(material_id, mesh_arrays.size());
		Array arrays = mesh_arrays[material_id];
		model_mesh->build_mesh(arrays, i, position, rotation);
	}
}

void StandardVoxelBlockData::_build_basics_mesh(const Ref<PresetsData>& presets_data, const Ref<BasicsPreset>& basics_preset, const Voxel& voxel, const Array& mesh_arrays, const Vector3i& position) {
	TypedArray<BasicsPreset> basics_presets = presets_data->get_basics_presets();
	Ref<MeshPreset> mesh_preset = basics_preset->get_basics_mesh();
	Vector3i rotation = get_voxel_rotation(voxel);
	if (rotation.x % 90 != 0 || rotation.y % 90 != 0 || rotation.z % 90 != 0)
	{
		for (int direction = 0; direction < 6; direction++)
		{
			int material_id = basics_preset->get_material_id(direction);
			ERR_FAIL_INDEX(material_id, mesh_arrays.size());
			Array arrays = mesh_arrays[material_id];
			_basics_mesh(mesh_preset, arrays, direction, position, rotation);
		}
	}
	else {
		for (int direction = 0; direction < 6; direction++) {
			Voxel relative_voxel = get_voxel(position + get_voxel_direction(direction, rotation));
			int relative_voxel_type = get_voxel_type(relative_voxel);
			int relative_voxel_id = get_voxel_id(relative_voxel);

			if (relative_voxel_type != BASICS) {
				int material_id = basics_preset->get_material_id(direction);
				ERR_FAIL_INDEX(material_id, mesh_arrays.size());
				Array arrays = mesh_arrays[material_id];
				_basics_mesh(mesh_preset, arrays, direction, position, rotation);
			}
			else {
				Vector3i relative_voxel_rotation = get_voxel_rotation(voxel);
				if (((basics_preset->get_transparent() == false) && ((cast_to<BasicsPreset>(basics_presets[relative_voxel_id])->get_transparent()) == true)) || relative_voxel_rotation.x % 90 != 0 || relative_voxel_rotation.y % 90 != 0 || relative_voxel_rotation.z % 90 != 0) {
					int material_id = basics_preset->get_material_id(direction);
					ERR_FAIL_INDEX(material_id, mesh_arrays.size());
					Array arrays = mesh_arrays[material_id];
					_basics_mesh(mesh_preset, arrays, direction, position, rotation);
				}
			}
		}
	}
}

void StandardVoxelBlockData::_build_model_mesh(const Ref<PresetsData>& presets_data, const Ref<ModelPreset>& model_preset, const Voxel& voxel, const Array& mesh_arrays, const Vector3i& position) {
	TypedArray<ModelPreset> model_presets = presets_data->get_model_presets();
	Vector3i rotation = get_voxel_rotation(voxel);
	int mask = 0;
	if (model_preset->is_use_mask())
	{
		Voxel voxels[6] = {
			get_voxel(position + get_voxel_direction(Preset::UP,rotation)),
			get_voxel(position + get_voxel_direction(Preset::DOWN,rotation)),
			get_voxel(position + get_voxel_direction(Preset::FRONT,rotation)),
			get_voxel(position + get_voxel_direction(Preset::BACK,rotation)),
			get_voxel(position + get_voxel_direction(Preset::LEFT,rotation)),
			get_voxel(position + get_voxel_direction(Preset::RIGHT,rotation)),
		};
		mask =
			((voxels[0] >> 15) == (voxel >> 15)) << 5 |
			((voxels[1] >> 15) == (voxel >> 15)) << 4 |
			((voxels[2] >> 15) == (voxel >> 15)) << 3 |
			((voxels[3] >> 15) == (voxel >> 15)) << 2 |
			((voxels[4] >> 15) == (voxel >> 15)) << 1 |
			((voxels[5] >> 15) == (voxel >> 15)) << 0;
	}
	_model_mesh(model_preset, mesh_arrays, mask, position, rotation);
}

Variant StandardVoxelBlockData::_build_device(const Ref<DevicePreset>& device_preset, const Vector3i& position, const Voxel& voxel)
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

	return device;
}

int StandardVoxelBlockData::_get_voxel_type(const Voxel& value)
{
	return get_voxel_type(value);
}

int StandardVoxelBlockData::_get_voxel_id(const Voxel& value)
{
	return get_voxel_id(value);
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
	if (use_custom_datas == true)
	{
		custom_datas.resize(size.x * size.y * size.z);
	}
	notify_property_list_changed();
}

Vector3i StandardVoxelBlockData::get_size() const {
	return VoxelBlockData::get_size();
}

void StandardVoxelBlockData::set_voxels_data(const PackedByteArray& value)
{
	voxels = value.decompress(4 * size.x * size.y * size.z).to_int32_array();
}

PackedByteArray StandardVoxelBlockData::get_voxels_data() const
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
	else {
		if (voxel_container != nullptr)
		{
			if (voxel_container->is_isolated() == false) {
				voxel_container->set_voxel(position + key * size, value);
			}
		}
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
	else {
		if (voxel_container != nullptr)
		{
			if (voxel_container->is_isolated() == false) {
				return voxel_container->get_voxel(position + key * size);
			}
		}
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

int StandardVoxelBlockData::get_voxel_type(const Voxel& value)
{
	return (value & 0b11'000000000000000'000000000000000) >> 30;
}

int StandardVoxelBlockData::get_voxel_id(const Voxel& value)
{
	return (value & 0b00'111111111111111'000000000000000) >> 15;
}

Vector3i StandardVoxelBlockData::get_voxel_rotation(const Voxel& value)
{
	return Vector3i((value & 0b00'000000000000000'11111'00000'00000) >> 10, (value & 0b00'000000000000000'00000'11111'00000) >> 5, (value & 0b00'000000000000000'00000'00000'11111)) * 15;
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