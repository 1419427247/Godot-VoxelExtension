#include "voxel_world.h"

void VoxelWorld::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_voxel", "position", "value"), &VoxelWorld::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel", "position"), &VoxelWorld::get_voxel);
	
	ClassDB::bind_method(D_METHOD("set_voxel_container_datas", "value"), &VoxelWorld::set_voxel_container_datas);
	ClassDB::bind_method(D_METHOD("get_voxel_container_datas"), &VoxelWorld::get_voxel_container_datas);

	ClassDB::bind_method(D_METHOD("get_block_key", "position"), &VoxelWorld::get_block_key);

	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "voxel_container_data"), "set_voxel_container_datas", "get_voxel_container_datas");

}

VoxelWorld::VoxelWorld()
{
}

VoxelWorld::~VoxelWorld()
{
}

void VoxelWorld::set_voxel_container_datas(const Dictionary& value)
{
	voxel_container_datas = value;
}

Dictionary VoxelWorld::get_voxel_container_datas() const
{
	return voxel_container_datas;
}
	
void VoxelWorld::set_voxel(const Vector3i& position, const Voxel& value)
{
	Vector3i chunk_key = get_block_key(position);
	Ref<VoxelContainerData> voxel_container_data = voxel_container_datas.get(chunk_key, nullptr);
	if (voxel_container_data.is_null())
	{
		return;
	}
	Vector3i block_size = get_block_size();
	voxel_container_data->set_voxel({
		position.x < 0 ? block_size.x - ((-1 * position.x - 1) % block_size.x) - 1 : (position.x % block_size.x),
		position.y < 0 ? block_size.y - ((-1 * position.y - 1) % block_size.y) - 1 : (position.y % block_size.y),
		position.z < 0 ? block_size.z - ((-1 * position.z - 1) % block_size.z) - 1 : (position.z % block_size.z)
		}, value);
}

Voxel VoxelWorld::get_voxel(const Vector3i& position) const
{
	Vector3i chunk_key = get_block_key(position);
	Ref<VoxelContainerData> voxel_container_data = voxel_container_datas.get(chunk_key, nullptr);
	if (voxel_container_data.is_null())
	{
		return EMPTY_VOXEL;
	}
	Vector3i block_size = get_block_size();
	return voxel_container_data->get_voxel({
		position.x < 0 ? block_size.x - ((-1 * position.x - 1) % block_size.x) - 1 : (position.x % block_size.x),
		position.y < 0 ? block_size.y - ((-1 * position.y - 1) % block_size.y) - 1 : (position.y % block_size.y),
		position.z < 0 ? block_size.z - ((-1 * position.z - 1) % block_size.z) - 1 : (position.z % block_size.z)
		});
}

Vector3i VoxelWorld::get_block_key(const Vector3i& position) const
{
	Vector3i block_size = get_block_size();
	return Vector3i(
		position.x < 0 ? (position.x + 1) / block_size.x - 1 : position.x / block_size.x,
		position.y < 0 ? (position.y + 1) / block_size.y - 1 : position.y / block_size.y,
		position.z < 0 ? (position.z + 1) / block_size.z - 1 : position.z / block_size.z
	);
}