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

#define VOXEL(type,id,rotation,flag) ((type << 30) | (id << 20) | (abs(rotation.x % 360 / 15) << 15) | (abs(rotation.y % 360 / 15)) << 10 | (abs(rotation.z % 360 / 15) << 5) | (flag & 0b11111))

#define EMPTY_VOXEL 0 
#define BASICS_VOXEL(id,rotation,flag) VOXEL(VoxelRoomData::BASICS, id, rotation, flag)
#define MESH_VOXEL(id,rotation,flag) VOXEL(VoxelRoomData::MESH, id, rotation, flag)
#define DEVICE_VOXEL(id,rotation,flag) VOXEL(VoxelRoomData::EMPTY, id, rotation, flag)

class VoxelRoomData : public Resource
{
	GDCLASS(VoxelRoomData, Resource);
	enum Type
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

	void set_voxel(const Vector3i& position, const Voxel& value);
	Voxel get_voxel(const Vector3i& position) const;
	Ref<VoxelRoomData> copy(const Vector3i& from, const Vector3i& to);
	void paste(const Ref<VoxelRoomData>& voxel_room_data, const Vector3i& position, const Vector3i& direction);
};
#endif // !VOXEL_WORLD_DATA_H

VARIANT_ENUM_CAST(VoxelRoomData, Type);
