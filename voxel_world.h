#ifndef VOXEL_WORLD_H
#define VOXEL_WORLD_H

#include "voxel_container.h"

class VoxelWorld : public VoxelContainer
{
	GDCLASS(VoxelWorld, VoxelContainer);
private:
	Dictionary voxel_container_datas;
protected:
	static void _bind_methods();

public:
	VoxelWorld();
	~VoxelWorld();

	void set_voxel(const Vector3i& position, const Voxel& value) override;
	Voxel get_voxel(const Vector3i& position) const override;

	Vector3i get_chunk_position(const Vector3i& position) const override;
};

#endif // !VOXEL_WORLD_H