#include "voxel_world.h"

#include <godot_cpp/classes/editor_plugin.hpp>


void VoxelWorld::_notification(int p_what) {

}

void VoxelWorld::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_voxel_world_data", "value"), &VoxelWorld::set_voxel_world_data);
	ClassDB::bind_method(D_METHOD("get_voxel_world_data"), &VoxelWorld::get_voxel_world_data);

	ClassDB::bind_method(D_METHOD("set_isolated", "value"), &VoxelWorld::set_isolated);
	ClassDB::bind_method(D_METHOD("get_isolated"), &VoxelWorld::get_isolated);

	ClassDB::bind_method(D_METHOD("set_voxel", "position", "value"), &VoxelWorld::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel", "position"), &VoxelWorld::get_voxel);

	ClassDB::bind_static_method("VoxelWorld", D_METHOD("get_voxel_direction", "direction", "rotation"), &VoxelWorld::get_voxel_direction);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("get_voxel_type", "value"), &VoxelWorld::get_voxel_type);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("get_voxel_id", "value"), &VoxelWorld::get_voxel_id);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("get_voxel_flag", "value"), &VoxelWorld::get_voxel_flag);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("empty_voxel"), &VoxelWorld::empty_voxel);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("basics_voxel", "id", "rotation"), &VoxelWorld::basics_voxel);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("mesh_voxel", "id", "rotation"), &VoxelWorld::mesh_voxel);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("device_voxel", "id", "flag"), &VoxelWorld::device_voxel, 0);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "voxel_world_data", PROPERTY_HINT_RESOURCE_TYPE, "VoxelWorldData"), "set_voxel_world_data", "get_voxel_world_data");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "isolated"), "set_isolated", "get_isolated");
}

VoxelWorld::VoxelWorld()
{
	this->isolated = false;
	this->mutex.instantiate();
}

VoxelWorld::~VoxelWorld()
{

}

void VoxelWorld::set_voxel_world_data(const Ref<VoxelWorldData>& value)
{
	voxel_world_data = value;
}

Ref<VoxelWorldData> VoxelWorld::get_voxel_world_data() const
{
	return voxel_world_data;
}

void VoxelWorld::set_devices(const Dictionary& value)
{
	devices = value;
}

Dictionary VoxelWorld::get_devices() const
{
	return devices;
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
	}
	Vector3i world_size = voxel_world_data->get_world_size();
	if (position.x < 0 || position.x >= world_size.x ||
		position.y < 0 || position.y >= world_size.y ||
		position.z < 0 || position.z >= world_size.z) {
		return;
	}
	int index = ((position.x * world_size.y * world_size.z) + (position.y * world_size.z) + position.z);
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

Vector3i VoxelWorld::get_voxel_direction(const Vector3& direction, const Vector3i& rotation)
{
	Vector3 result = direction;
	result = result.rotated(Vector3(1, 0, 0), UtilityFunctions::deg_to_rad(rotation.x));
	result = result.rotated(Vector3(0, 1, 0), UtilityFunctions::deg_to_rad(rotation.y));
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

int VoxelWorld::get_voxel_flag(const Voxel& value)
{
	return (value << 12) >> 12;

}

Vector3i VoxelWorld::flag_to_rotation(const int& value)
{
	return Vector3i((value & (0b11111 << 10)) >> 10, (value & (0b11111 << 5)) >> 5, (value & 0b11111)) * 15;
}

int VoxelWorld::rotation_to_flag(const Vector3i& value)
{
	return ((value.x / 15) << 10) | ((value.y / 15) << 5) | (value.z / 15);
}

Voxel VoxelWorld::empty_voxel()
{
	return 0;
}

Voxel VoxelWorld::basics_voxel(const int& id, const Vector3i& rotation)
{
	return (VoxelWorldData::BASICS << 30) | (id << 20) | rotation_to_flag(rotation);
}

Voxel VoxelWorld::mesh_voxel(const int& id, const Vector3i& rotation)
{
	return (VoxelWorldData::MESH << 30) | (id << 20) | rotation_to_flag(rotation);
}

Voxel VoxelWorld::device_voxel(const int& id, const int& flag)
{
	return (VoxelWorldData::DEVICE << 30) | (id << 20) | flag;
}