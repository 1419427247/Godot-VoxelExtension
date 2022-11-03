#include "voxel_world.h"

void VoxelWorld::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_voxel", "position", "value"), &VoxelWorld::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel", "position"), &VoxelWorld::get_voxel);

	ClassDB::bind_method(D_METHOD("get_chunk_position", "position"), &VoxelWorld::get_chunk_position);
}

VoxelWorld::VoxelWorld()
{
}

VoxelWorld::~VoxelWorld()
{
}

void VoxelWorld::set_voxel(const Vector3i& position, const Voxel& value)
{
	Vector3i chunk_position = get_chunk_position(position);
	Ref<VoxelContainerData> voxel_container_data = voxel_container_datas.get(chunk_position, nullptr);
	if (voxel_container_data.is_null())
	{
		voxel_container_data.instantiate();
		voxel_container_data->set_container_size(chunk_size);
		voxel_container_datas[chunk_position] = voxel_container_data;
	}

	voxel_container_data->set_voxel({
		position.x < 0 ? chunk_size.x - ((-1 * position.x - 1) % chunk_size.x) - 1 : (position.x % chunk_size.x),
		position.y < 0 ? chunk_size.y - ((-1 * position.y - 1) % chunk_size.y) - 1 : (position.y % chunk_size.y),
		position.z < 0 ? chunk_size.z - ((-1 * position.z - 1) % chunk_size.z) - 1 : (position.z % chunk_size.z)
		}, value);

}

Voxel VoxelWorld::get_voxel(const Vector3i& position) const
{
	Vector3i chunk_position = get_chunk_position(position);
	Ref<VoxelContainerData> voxel_container_data = voxel_container_datas.get(chunk_position, nullptr);
	if (voxel_container_data.is_null())
	{
		return EMPTY_VOXEL;
	}
	return voxel_container_data->get_voxel({
		position.x < 0 ? chunk_size.x - ((-1 * position.x - 1) % chunk_size.x) - 1 : (position.x % chunk_size.x),
		position.y < 0 ? chunk_size.y - ((-1 * position.y - 1) % chunk_size.y) - 1 : (position.y % chunk_size.y),
		position.z < 0 ? chunk_size.z - ((-1 * position.z - 1) % chunk_size.z) - 1 : (position.z % chunk_size.z)
		});
}

Vector3i VoxelWorld::get_chunk_position(const Vector3i& position) const
{
	return Vector3i(
		position.x < 0 ? (position.x + 1) / chunk_size.x - 1 : position.x / chunk_size.x,
		position.y < 0 ? (position.y + 1) / chunk_size.y - 1 : position.y / chunk_size.y,
		position.z < 0 ? (position.z + 1) / chunk_size.z - 1 : position.z / chunk_size.z
	);
}
