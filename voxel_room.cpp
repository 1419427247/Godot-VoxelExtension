#include "voxel_room.h"

void VoxelRoom::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_voxel_container_data", "value"), &VoxelRoom::set_voxel_container_data);
	ClassDB::bind_method(D_METHOD("get_voxel_container_data"), &VoxelRoom::get_voxel_container_data);
	ClassDB::bind_method(D_METHOD("set_voxel", "position", "value"), &VoxelRoom::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel", "position"), &VoxelRoom::get_voxel);
	ClassDB::bind_method(D_METHOD("get_chunk_key", "position"), &VoxelRoom::get_chunk_key);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "voxel_container_data", PROPERTY_HINT_RESOURCE_TYPE, "VoxelContainerData"), "set_voxel_container_data", "get_voxel_container_data");
}

VoxelRoom::VoxelRoom()
{

}

VoxelRoom::~VoxelRoom()
{

}

void VoxelRoom::set_voxel_container_data(const Ref<VoxelContainerData>& value)
{
	voxel_container_data = value;
}

Ref<VoxelContainerData> VoxelRoom::get_voxel_container_data() const
{
	return voxel_container_data;
}

void VoxelRoom::set_voxel(const Vector3i& position, const Voxel& value)
{
	ERR_FAIL_NULL(voxel_container_data);
	voxel_container_data->set_voxel(position, value);
}

Voxel VoxelRoom::get_voxel(const Vector3i& position) const
{
	ERR_FAIL_NULL_V(voxel_container_data, EMPTY_VOXEL);
	return voxel_container_data->get_voxel(position);
}

Vector3i VoxelRoom::get_chunk_key(const Vector3i& position) const
{
	return Vector3i(
		position.x / chunk_size.x,
		position.y / chunk_size.y,
		position.z / chunk_size.z
	);
}
