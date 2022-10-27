#include "voxel_room.h"

void VoxelRoom::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_voxel_room_data", "value"), &VoxelRoom::set_voxel_room_data);
	ClassDB::bind_method(D_METHOD("get_voxel_room_data"), &VoxelRoom::get_voxel_room_data);

	ClassDB::bind_method(D_METHOD("set_voxel", "position", "value"), &VoxelRoom::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel", "position"), &VoxelRoom::get_voxel);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "voxel_room_data", PROPERTY_HINT_RESOURCE_TYPE, "VoxelRoomData"), "set_voxel_room_data", "get_voxel_room_data");

}

VoxelRoom::VoxelRoom()
{
	isolated = false;
}

VoxelRoom::~VoxelRoom()
{

}

void VoxelRoom::set_voxel_room_data(const Ref<VoxelRoomData>& value)
{
	voxel_room_data = value;
}

Ref<VoxelRoomData> VoxelRoom::get_voxel_room_data() const
{
	return voxel_room_data;
}

void VoxelRoom::set_voxel(const Vector3i& position, const Voxel& value)
{
	ERR_FAIL_NULL(voxel_room_data);
	Vector3i room_size = voxel_room_data->get_room_size();
	voxel_room_data->set_voxel(position, value);
}

Voxel VoxelRoom::get_voxel(const Vector3i& position) const
{
	ERR_FAIL_NULL_V(voxel_room_data, EMPTY_VOXEL);
	return voxel_room_data->get_voxel(position);
}