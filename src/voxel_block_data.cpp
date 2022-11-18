#include "voxel_block_data.h"

void VoxelBlockData::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_size", "value"), &VoxelBlockData::set_size);
	ClassDB::bind_method(D_METHOD("get_size"), &VoxelBlockData::get_size);

	ClassDB::bind_method(D_METHOD("set_voxels", "value"), &VoxelBlockData::set_voxels);
	ClassDB::bind_method(D_METHOD("get_voxels"), &VoxelBlockData::get_voxels);

	ClassDB::bind_method(D_METHOD("set_voxel", "position", "value"), &VoxelBlockData::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel", "position"), &VoxelBlockData::get_voxel);

	ClassDB::bind_method(D_METHOD("fill", "voxel"), &VoxelBlockData::fill);
	ClassDB::bind_method(D_METHOD("is_filled", "voxel"), &VoxelBlockData::is_filled);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "size"), "set_size", "get_size");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_INT32_ARRAY, "voxels"), "set_voxels", "get_voxels");
}

VoxelBlockData::VoxelBlockData()
{
	set_size(Vector3i(8, 8, 8));
}

VoxelBlockData::~VoxelBlockData()
{
}

void VoxelBlockData::set_size(const Vector3i& value) {
	ERR_FAIL_COND_MSG(value.x <= 0 || value.y <= 0 || value.z <= 0, "The container size is an invalid value");
	size = value;
	voxels.resize(size.x * size.y * size.z);
}

Vector3i VoxelBlockData::get_size() const {
	return size;
}

void VoxelBlockData::set_voxels(const PackedByteArray& value)
{
	voxels = value.decompress(4096).to_int32_array();
	if (voxels.size() != size.x * size.y * size.z)
	{
		voxels.resize(size.x * size.y * size.z);
	}
}

PackedByteArray VoxelBlockData::get_voxels() const
{
	return voxels.to_byte_array().compress();
}

void VoxelBlockData::set_voxel(const Vector3i& position, const Voxel& value)
{
	if (position.x < 0 || position.x >= size.x ||
		position.y < 0 || position.y >= size.y ||
		position.z < 0 || position.z >= size.z) {
		return;
	}
	int index = ((position.x * size.y * size.z) + (position.y * size.z) + position.z);
	voxels[index] = value;
}

Voxel VoxelBlockData::get_voxel(const Vector3i& position) const
{
	if (position.x < 0 || position.x >= size.x ||
		position.y < 0 || position.y >= size.y ||
		position.z < 0 || position.z >= size.z) {
		return EMPTY_VOXEL;
	}
	int index = ((position.x * size.y * size.z) + (position.y * size.z) + position.z);
	return voxels[index];
}

void VoxelBlockData::fill(const Voxel& voxel) {
	for (int i = 0; i < size.x * size.y * size.z; i++)
	{
		voxels[i] = voxel;
	}
}


bool VoxelBlockData::is_filled(const Voxel& voxel) const {
	for (int i = 0; i < voxels.size(); i++)
	{
		if (voxels[i] != voxel)
		{
			return false;
		}
	}
	return true;
}
