#include "voxel_container.h"

void VoxelContainer::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_presets_data", "value"), &VoxelContainer::set_presets_data);
	ClassDB::bind_method(D_METHOD("get_presets_data"), &VoxelContainer::get_presets_data);

	ClassDB::bind_method(D_METHOD("set_isolated", "value"), &VoxelContainer::set_isolated);
	ClassDB::bind_method(D_METHOD("get_isolated"), &VoxelContainer::get_isolated);

	//ClassDB::bind_method(D_METHOD("set_voxel", "position", "value"), &VoxelContainer::set_voxel);
	//ClassDB::bind_method(D_METHOD("get_voxel", "position"), &VoxelContainer::get_voxel);

	ClassDB::bind_static_method("VoxelContainer", D_METHOD("get_voxel_direction", "direction", "rotation"), &VoxelContainer::get_voxel_direction);
	ClassDB::bind_static_method("VoxelContainer", D_METHOD("get_voxel_type", "value"), &VoxelContainer::get_voxel_type);
	ClassDB::bind_static_method("VoxelContainer", D_METHOD("get_voxel_id", "value"), &VoxelContainer::get_voxel_id);
	ClassDB::bind_static_method("VoxelContainer", D_METHOD("get_voxel_rotation", "value"), &VoxelContainer::get_voxel_rotation);
	ClassDB::bind_static_method("VoxelContainer", D_METHOD("get_voxel_flag", "value"), &VoxelContainer::get_voxel_flag);

	ClassDB::bind_static_method("VoxelContainer", D_METHOD("empty_voxel"), &VoxelContainer::empty_voxel);
	ClassDB::bind_static_method("VoxelContainer", D_METHOD("basics_voxel", "id", "rotation", "flag"), &VoxelContainer::basics_voxel, Vector3i(), 0);
	ClassDB::bind_static_method("VoxelContainer", D_METHOD("mesh_voxel", "id", "rotation", "flag"), &VoxelContainer::mesh_voxel, Vector3i(), 0);
	ClassDB::bind_static_method("VoxelContainer", D_METHOD("device_voxel", "id", "rotation", "flag"), &VoxelContainer::device_voxel, Vector3i(), 0);

	BIND_VIRTUAL_METHOD(VoxelContainer, set_voxel);
	BIND_VIRTUAL_METHOD(VoxelContainer, get_voxel);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "presets_data", PROPERTY_HINT_RESOURCE_TYPE, "PresetsData"), "set_presets_data", "get_presets_data");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "isolated"), "set_isolated", "get_isolated");
}

void VoxelContainer::set_presets_data(const Ref<PresetsData>& value)
{
	presets_data = value;
}

Ref<PresetsData> VoxelContainer::get_presets_data() const
{
	return presets_data;
}


void VoxelContainer::set_isolated(const bool& value)
{
	isolated = value;
}

bool VoxelContainer::get_isolated() const
{
	return isolated;
}

void VoxelContainer::set_voxel(const Vector3i& position, const Voxel& value)
{
}

Voxel VoxelContainer::get_voxel(const Vector3i& position) const
{
	return EMPTY_VOXEL;
}

Vector3i VoxelContainer::get_voxel_direction(const Vector3i& direction, const Vector3i& rotation)
{
	Vector3 result = direction;
	result = result.rotated(Vector3(0, 1, 0), UtilityFunctions::deg_to_rad(rotation.y));
	result = result.rotated(Vector3(1, 0, 0), UtilityFunctions::deg_to_rad(rotation.x));
	result = result.rotated(Vector3(0, 0, 1), UtilityFunctions::deg_to_rad(rotation.z));
	return Vector3i(result);
}

int VoxelContainer::get_voxel_type(const Voxel& value)
{
	return value >> 30;
}

int VoxelContainer::get_voxel_id(const Voxel& value)
{
	return (value << 2) >> 22;
}

Vector3i VoxelContainer::get_voxel_rotation(const Voxel& value)
{
	return Vector3i((value << 12) >> 27, (value << 17) >> 27, (value & (0b11111 << 22) >> 27)) * 15;
}

int VoxelContainer::get_voxel_flag(const Voxel& value)
{
	return (value << 27) >> 27;
}

Voxel VoxelContainer::empty_voxel()
{
	return EMPTY_VOXEL;
}

Voxel VoxelContainer::basics_voxel(const int& id, const Vector3i& rotation, const int& flag)
{
	return BASICS_VOXEL(id, rotation, flag);
}

Voxel VoxelContainer::mesh_voxel(const int& id, const Vector3i& rotation, const int& flag)
{
	return DEVICE_VOXEL(id, rotation, flag);
}

Voxel VoxelContainer::device_voxel(const int& id, const Vector3i& rotation, const int& flag)
{
	return DEVICE_VOXEL(id, rotation, flag);
}