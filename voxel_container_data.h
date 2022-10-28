#ifndef VOXEL_WORLD_DATA_H
#define VOXEL_WORLD_DATA_H

#include "preset.h"

//type : 2
//id : 10
//rotation: 15
//flag : 5

#define VOXEL(type,id,rotation,flag) ((type << 30) | (id << 20) | (abs(rotation.x % 360 / 15) << 15) | (abs(rotation.y % 360 / 15)) << 10 | (abs(rotation.z % 360 / 15) << 5) | (flag & 0b11111))

#define EMPTY_VOXEL 0 
#define BASICS_VOXEL(id,rotation,flag) VOXEL(VoxelContainerData::BASICS, id, rotation, flag)
#define MESH_VOXEL(id,rotation,flag) VOXEL(VoxelContainerData::MESH, id, rotation, flag)
#define DEVICE_VOXEL(id,rotation,flag) VOXEL(VoxelContainerData::EMPTY, id, rotation, flag)

class VoxelContainerData : public Resource
{
	GDCLASS(VoxelContainerData, Resource);
	enum Type
	{
		EMPTY = 0,
		BASICS = 1,
		MESH = 2,
		DEVICE = 3,
	};
private:
	Vector3i container_size;
protected:
	static void _bind_methods();
public:
	PackedInt32Array voxels;

	VoxelContainerData();
	~VoxelContainerData();

	void set_container_size(const Vector3i& value);
	Vector3i get_container_size() const;

	void set_voxels(const PackedByteArray& value);
	PackedByteArray get_voxels() const;

	void set_voxel(const Vector3i& position, const Voxel& value);
	Voxel get_voxel(const Vector3i& position) const;
};
#endif // !VOXEL_WORLD_DATA_H

VARIANT_ENUM_CAST(VoxelContainerData, Type);
