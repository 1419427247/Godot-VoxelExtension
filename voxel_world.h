#ifndef VOXEL_WORLD_H
#define VOXEL_WORLD_H

#include "voxel_container.h"

class VoxelWorld : public VoxelContainer
{
	GDCLASS(VoxelWorld, VoxelContainer);
private:
	Dictionary voxel_container_datas;
	//Ref<VoxelContainerData> voxel_container_data;
protected:
	static void _bind_methods();

public:
	VoxelWorld();
	~VoxelWorld();

	//void set_voxel_container_data(const Ref<VoxelContainerData>& value);
	//Ref<VoxelContainerData> get_voxel_container_data() const;

	void set_voxel(const Vector3i& position, const Voxel& value);
	Voxel get_voxel(const Vector3i& position) const;
};

#endif // !VOXEL_WORLD_H