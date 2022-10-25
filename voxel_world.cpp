#include "voxel_world.h"

void VoxelWorld::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_presets_data", "value"), &VoxelWorld::set_presets_data);
	ClassDB::bind_method(D_METHOD("get_presets_data"), &VoxelWorld::get_presets_data);

	ClassDB::bind_method(D_METHOD("set_voxel_world_data", "value"), &VoxelWorld::set_voxel_world_data);
	ClassDB::bind_method(D_METHOD("get_voxel_world_data"), &VoxelWorld::get_voxel_world_data);

	ClassDB::bind_method(D_METHOD("set_isolated", "value"), &VoxelWorld::set_isolated);
	ClassDB::bind_method(D_METHOD("get_isolated"), &VoxelWorld::get_isolated);

	ClassDB::bind_method(D_METHOD("set_voxel", "position", "value"), &VoxelWorld::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel", "position"), &VoxelWorld::get_voxel);

	ClassDB::bind_static_method("VoxelWorld", D_METHOD("get_voxel_direction", "direction", "rotation"), &VoxelWorld::get_voxel_direction);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("get_voxel_type", "value"), &VoxelWorld::get_voxel_type);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("get_voxel_id", "value"), &VoxelWorld::get_voxel_id);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("get_voxel_rotation", "value"), &VoxelWorld::get_voxel_rotation);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("get_voxel_flag", "value"), &VoxelWorld::get_voxel_flag);

	ClassDB::bind_static_method("VoxelWorld", D_METHOD("empty_voxel"), &VoxelWorld::empty_voxel);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("basics_voxel", "id", "rotation", "flag"), &VoxelWorld::basics_voxel, 0);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("mesh_voxel", "id", "rotation", "flag"), &VoxelWorld::mesh_voxel, 0);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("device_voxel", "id", "rotation", "flag"), &VoxelWorld::device_voxel, 0);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "presets_data", PROPERTY_HINT_RESOURCE_TYPE, "PresetsData"), "set_presets_data", "get_presets_data");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "voxel_world_data", PROPERTY_HINT_RESOURCE_TYPE, "VoxelWorldData"), "set_voxel_world_data", "get_voxel_world_data");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "isolated"), "set_isolated", "get_isolated");
}

VoxelWorld::VoxelWorld()
{
	this->isolated = false;
}

VoxelWorld::~VoxelWorld()
{

}

void VoxelWorld::set_presets_data(const Ref<PresetsData>& value)
{
	presets_data = value;
}

Ref<PresetsData> VoxelWorld::get_presets_data() const
{
	return presets_data;
}

void VoxelWorld::set_voxel_world_data(const Ref<VoxelWorldData>& value)
{
	voxel_world_data = value;
}

Ref<VoxelWorldData> VoxelWorld::get_voxel_world_data() const
{
	return voxel_world_data;
}

void VoxelWorld::set_isolated(const bool& value)
{
	isolated = value;
}

bool VoxelWorld::get_isolated() const
{
	return isolated;
}

void VoxelWorld::set_voxel(const Vector3i& position, const Voxel& value)
{
	if (voxel_world_data.is_null())
	{
		UtilityFunctions::printerr("voxel_world_data is null");
		return;
	}
	Vector3i world_size = voxel_world_data->get_world_size();
	if (position.x < 0 || position.x >= world_size.x ||
		position.y < 0 || position.y >= world_size.y ||
		position.z < 0 || position.z >= world_size.z) {
		return;
	}
	int index = ((position.x * world_size.y * world_size.z) + (position.y * world_size.z) + position.z);
	Voxel voxel = voxel_world_data->voxels[index];

	int type = get_voxel_type(voxel);
	int id = get_voxel_id(voxel);
	Vector3i rotation = get_voxel_rotation(voxel);
	int flag = get_voxel_flag(voxel);

	voxel_world_data->voxels[index] = value;
}

Voxel VoxelWorld::get_voxel(const Vector3i& position) const
{
	if (voxel_world_data.is_null())
	{
		UtilityFunctions::printerr("voxel_world_data is null");
		return VoxelWorld::empty_voxel();
	}
	Vector3i world_size = voxel_world_data->get_world_size();
	if (position.x < 0 || position.x >= world_size.x ||
		position.y < 0 || position.y >= world_size.y ||
		position.z < 0 || position.z >= world_size.z) {
		return VoxelWorld::empty_voxel();
	}
	int index = ((position.x * world_size.y * world_size.z) + (position.y * world_size.z) + position.z);
	return voxel_world_data->voxels[index];
}

static Vector3 direction_memorandum[8][32] = { Vector3() };

//Vector3i VoxelWorld::get_voxel_direction(const Vector3i& direction, const Vector3i& rotation)
//{
//	Vector3* result = &direction_memorandum[direction.x * 4 + direction.y * 2 + direction.z][rotation.x / 90 * 4 * 4 + rotation.y / 90 * 4 + rotation.z];
//	if (*result == Vector3i())
//	{
//		*result = direction;
//		result->rotate(Vector3(0, 1, 0), UtilityFunctions::deg_to_rad(rotation.y));
//		result->rotate(Vector3(1, 0, 0), UtilityFunctions::deg_to_rad(rotation.x));
//		result->rotate(Vector3(0, 0, 1), UtilityFunctions::deg_to_rad(rotation.z));
//	}
//	return Vector3i(*result);
//}

Vector3i VoxelWorld::get_voxel_direction(const Vector3i& direction, const Vector3i& rotation)
{
	Vector3 result = direction;
	result = result.rotated(Vector3(0, 1, 0), UtilityFunctions::deg_to_rad(rotation.y));
	result = result.rotated(Vector3(1, 0, 0), UtilityFunctions::deg_to_rad(rotation.x));
	result = result.rotated(Vector3(0, 0, 1), UtilityFunctions::deg_to_rad(rotation.z));
	return Vector3i(result);
}

int VoxelWorld::get_voxel_type(const Voxel& value)
{
	return value >> 30;
}

int VoxelWorld::get_voxel_id(const Voxel& value)
{
	return (value << 2) >> 22;
}

Vector3i VoxelWorld::get_voxel_rotation(const Voxel& value)
{
	return Vector3i((value << 12) >> 27, (value << 17) >> 27, (value & (0b11111 << 22) >> 27)) * 15;
}

int VoxelWorld::get_voxel_flag(const Voxel& value)
{
	return (value << 27) >> 27;
}

Voxel VoxelWorld::empty_voxel()
{
	return 0;
}

Voxel VoxelWorld::basics_voxel(const int& id, const Vector3i& rotation, const int& flag)
{
	return VOXEL(VoxelWorldData::BASICS, id, rotation, flag);
}

Voxel VoxelWorld::mesh_voxel(const int& id, const Vector3i& rotation, const int& flag)
{
	return VOXEL(VoxelWorldData::MESH, id, rotation, flag);
}

Voxel VoxelWorld::device_voxel(const int& id, const Vector3i& rotation, const int& flag)
{
	return VOXEL(VoxelWorldData::EMPTY, id, rotation, flag);
}