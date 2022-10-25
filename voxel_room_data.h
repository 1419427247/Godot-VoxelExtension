#ifndef VOXEL_WORLD_DATA_H
#define VOXEL_WORLD_DATA_H

#include "basics_preset.h"
#include "mesh_preset.h"
#include "device_preset.h"
#include "custom_material.h"

//type : 2
//id : 10
//rotation: 15
//flag : 5

class VoxelRoomData : public Resource
{
	GDCLASS(VoxelRoomData, Resource);
	enum VoxelType
	{
		EMPTY = 0,
		BASICS = 1,
		MESH = 2,
		DEVICE = 3,
	};
private:
	Vector3i room_size;
protected:
	static void _bind_methods();
public:
	Vector3i chunk_size;
	Vector3i chunk_count;

	PackedInt32Array voxels;

	VoxelRoomData();
	~VoxelRoomData();

	void set_chunk_size(const Vector3i& value);
	Vector3i get_chunk_size() const;

	void set_chunk_count(const Vector3i& value);
	Vector3i get_chunk_count() const;

	Vector3i get_room_size() const;

	void set_voxels(const PackedByteArray& value);
	PackedByteArray get_voxels() const;
};
#endif // !VOXEL_WORLD_DATA_H

VARIANT_ENUM_CAST(VoxelRoomData, VoxelType);
