#ifndef VOXEL_CONTAINER_DATA_H
#define VOXEL_CONTAINER_DATA_H

#include "presets_data.h"
#include "device.h"
//type : 2
//id : 10
//rotation: 15
//flag : 5

class VoxelContainerData : public Resource
{
	GDCLASS(VoxelContainerData, Resource);
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

	void fill(const Voxel& voxel);
	bool is_filled(const Voxel& voxel) const;
};
#endif // !VOXEL_WORLD_DATA_H

