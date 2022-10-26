#include "voxel_room.h"

void VoxelRoom::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_presets_data", "value"), &VoxelRoom::set_presets_data);
	ClassDB::bind_method(D_METHOD("get_presets_data"), &VoxelRoom::get_presets_data);

	ClassDB::bind_method(D_METHOD("set_voxel_room_data", "value"), &VoxelRoom::set_voxel_room_data);
	ClassDB::bind_method(D_METHOD("get_voxel_room_data"), &VoxelRoom::get_voxel_room_data);

	ClassDB::bind_method(D_METHOD("set_isolated", "value"), &VoxelRoom::set_isolated);
	ClassDB::bind_method(D_METHOD("get_isolated"), &VoxelRoom::get_isolated);

	ClassDB::bind_method(D_METHOD("set_voxel", "position", "value"), &VoxelRoom::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel", "position"), &VoxelRoom::get_voxel);

	ClassDB::bind_static_method("VoxelRoom", D_METHOD("get_voxel_direction", "direction", "rotation"), &VoxelRoom::get_voxel_direction);
	ClassDB::bind_static_method("VoxelRoom", D_METHOD("get_voxel_type", "value"), &VoxelRoom::get_voxel_type);
	ClassDB::bind_static_method("VoxelRoom", D_METHOD("get_voxel_id", "value"), &VoxelRoom::get_voxel_id);
	ClassDB::bind_static_method("VoxelRoom", D_METHOD("get_voxel_rotation", "value"), &VoxelRoom::get_voxel_rotation);
	ClassDB::bind_static_method("VoxelRoom", D_METHOD("get_voxel_flag", "value"), &VoxelRoom::get_voxel_flag);

	ClassDB::bind_static_method("VoxelRoom", D_METHOD("empty_voxel"), &VoxelRoom::empty_voxel);
	ClassDB::bind_static_method("VoxelRoom", D_METHOD("basics_voxel", "id", "rotation", "flag"), &VoxelRoom::basics_voxel, 0);
	ClassDB::bind_static_method("VoxelRoom", D_METHOD("mesh_voxel", "id", "rotation", "flag"), &VoxelRoom::mesh_voxel, 0);
	ClassDB::bind_static_method("VoxelRoom", D_METHOD("device_voxel", "id", "rotation", "flag"), &VoxelRoom::device_voxel, 0);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "presets_data", PROPERTY_HINT_RESOURCE_TYPE, "PresetsData"), "set_presets_data", "get_presets_data");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "voxel_room_data", PROPERTY_HINT_RESOURCE_TYPE, "VoxelRoomData"), "set_voxel_room_data", "get_voxel_room_data");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "isolated"), "set_isolated", "get_isolated");
}

VoxelRoom::VoxelRoom()
{
	isolated = false;
}

VoxelRoom::~VoxelRoom()
{

}

void VoxelRoom::set_presets_data(const Ref<PresetsData>& value)
{
	presets_data = value;
}

Ref<PresetsData> VoxelRoom::get_presets_data() const
{
	return presets_data;
}

void VoxelRoom::set_voxel_room_data(const Ref<VoxelRoomData>& value)
{
	voxel_room_data = value;
}

Ref<VoxelRoomData> VoxelRoom::get_voxel_room_data() const
{
	return voxel_room_data;
}

void VoxelRoom::set_isolated(const bool& value)
{
	isolated = value;
}

bool VoxelRoom::get_isolated() const
{
	return isolated;
}

void VoxelRoom::set_voxel(const Vector3i& position, const Voxel& value)
{
	ERR_FAIL_NULL_MSG(voxel_room_data, "");
	Vector3i room_size = voxel_room_data->get_room_size();
	if (position.x < 0 || position.x >= room_size.x ||
		position.y < 0 || position.y >= room_size.y ||
		position.z < 0 || position.z >= room_size.z) {
		return;
	}
	int index = ((position.x * room_size.y * room_size.z) + (position.y * room_size.z) + position.z);
	Voxel voxel = voxel_room_data->voxels[index];

	int type = get_voxel_type(voxel);
	int id = get_voxel_id(voxel);
	Vector3i rotation = get_voxel_rotation(voxel);
	int flag = get_voxel_flag(voxel);

	voxel_room_data->voxels[index] = value;
}

Voxel VoxelRoom::get_voxel(const Vector3i& position) const
{
	ERR_FAIL_NULL_V_MSG(voxel_room_data, VoxelRoom::empty_voxel(), "");
	Vector3i room_size = voxel_room_data->get_room_size();
	if (position.x < 0 || position.x >= room_size.x ||
		position.y < 0 || position.y >= room_size.y ||
		position.z < 0 || position.z >= room_size.z) {
		return VoxelRoom::empty_voxel();
	}
	int index = ((position.x * room_size.y * room_size.z) + (position.y * room_size.z) + position.z);
	return voxel_room_data->voxels[index];
}

Vector3i VoxelRoom::get_voxel_direction(const Vector3i& direction, const Vector3i& rotation)
{
	Vector3 result = direction;
	result = result.rotated(Vector3(0, 1, 0), UtilityFunctions::deg_to_rad(rotation.y));
	result = result.rotated(Vector3(1, 0, 0), UtilityFunctions::deg_to_rad(rotation.x));
	result = result.rotated(Vector3(0, 0, 1), UtilityFunctions::deg_to_rad(rotation.z));
	return Vector3i(result);
}

int VoxelRoom::get_voxel_type(const Voxel& value)
{
	return value >> 30;
}

int VoxelRoom::get_voxel_id(const Voxel& value)
{
	return (value << 2) >> 22;
}

Vector3i VoxelRoom::get_voxel_rotation(const Voxel& value)
{
	return Vector3i((value << 12) >> 27, (value << 17) >> 27, (value & (0b11111 << 22) >> 27)) * 15;
}

int VoxelRoom::get_voxel_flag(const Voxel& value)
{
	return (value << 27) >> 27;
}

Voxel VoxelRoom::empty_voxel()
{
	return 0;
}

Voxel VoxelRoom::basics_voxel(const int& id, const Vector3i& rotation, const int& flag)
{
	return VOXEL(VoxelRoomData::BASICS, id, rotation, flag);
}

Voxel VoxelRoom::mesh_voxel(const int& id, const Vector3i& rotation, const int& flag)
{
	return VOXEL(VoxelRoomData::MESH, id, rotation, flag);
}

Voxel VoxelRoom::device_voxel(const int& id, const Vector3i& rotation, const int& flag)
{
	return VOXEL(VoxelRoomData::EMPTY, id, rotation, flag);
}