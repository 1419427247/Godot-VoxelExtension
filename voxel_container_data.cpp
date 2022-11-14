#include "voxel_container_data.h"

void VoxelContainerData::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_container_size", "value"), &VoxelContainerData::set_container_size);
	ClassDB::bind_method(D_METHOD("get_container_size"), &VoxelContainerData::get_container_size);

	ClassDB::bind_method(D_METHOD("set_voxels", "value"), &VoxelContainerData::set_voxels);
	ClassDB::bind_method(D_METHOD("get_voxels"), &VoxelContainerData::get_voxels);

	ClassDB::bind_method(D_METHOD("set_voxel", "value"), &VoxelContainerData::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel"), &VoxelContainerData::get_voxel);

	ClassDB::bind_method(D_METHOD("fill","voxel"), &VoxelContainerData::fill);
	ClassDB::bind_method(D_METHOD("is_filled", "voxel"), &VoxelContainerData::is_filled);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "container_size"), "set_container_size", "get_container_size");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_BYTE_ARRAY, "voxels"), "set_voxels", "get_voxels");

	BIND_ENUM_CONSTANT(EMPTY);
	BIND_ENUM_CONSTANT(BASICS);
	BIND_ENUM_CONSTANT(MODEL);
	BIND_ENUM_CONSTANT(DEVICE);
}

VoxelContainerData::VoxelContainerData()
{
	set_container_size(Vector3i(8, 8, 8));
}

VoxelContainerData::~VoxelContainerData()
{
}


void VoxelContainerData::set_container_size(const Vector3i& value) {
	ERR_FAIL_COND_MSG(value.x <= 0 || value.y <= 0 || value.z <= 0, "The container size is an invalid value");
	container_size = value;
	voxels.resize(container_size.x * container_size.y * container_size.z);
}

Vector3i VoxelContainerData::get_container_size() const {
	return container_size;
}

void VoxelContainerData::set_voxels(const PackedByteArray& value)
{
	//voxels = value.decompress(4096).to_int32_array();
}

PackedByteArray VoxelContainerData::get_voxels() const
{
	//return voxels.to_byte_array().compress();
	return PackedByteArray();
}

void VoxelContainerData::set_voxel(const Vector3i& position, const Voxel& value)
{
	if (position.x < 0 || position.x >= container_size.x ||
		position.y < 0 || position.y >= container_size.y ||
		position.z < 0 || position.z >= container_size.z) {
		return;
	}
	int index = ((position.x * container_size.y * container_size.z) + (position.y * container_size.z) + position.z);
	voxels[index] = value;
}

Voxel VoxelContainerData::get_voxel(const Vector3i& position) const
{
	if (position.x < 0 || position.x >= container_size.x ||
		position.y < 0 || position.y >= container_size.y ||
		position.z < 0 || position.z >= container_size.z) {
		return EMPTY_VOXEL;
	}
	int index = ((position.x * container_size.y * container_size.z) + (position.y * container_size.z) + position.z);
	return voxels[index];
}

void VoxelContainerData::fill(const Voxel& voxel){
	for (int i = 0; i < container_size.x * container_size.y * container_size.z; i++)
	{
		voxels[i] = voxel;
	}
}


bool VoxelContainerData::is_filled(const Voxel& voxel) const {
	for (int i = 0; i < voxels.size(); i++)
	{
		if (voxels[i] != voxel)
		{
			return false;
		}
	}
	return true;
}
