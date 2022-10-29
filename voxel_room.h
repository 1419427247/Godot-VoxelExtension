#ifndef VOXEL_ROOM_H
#define VOXEL_ROOM_H

#include"voxel_container.h"

class VoxelRoom : public VoxelContainer
{
	GDCLASS(VoxelRoom, VoxelContainer);
private:
	Ref<VoxelContainerData> voxel_container_data;
protected:
	static void _bind_methods();

public:
	VoxelRoom();
	~VoxelRoom();

	void set_voxel_container_data(const Ref<VoxelContainerData>& value);
	Ref<VoxelContainerData> get_voxel_container_data() const;

	void set_voxel(const Vector3i& position, const Voxel& value) override;
	Voxel get_voxel(const Vector3i& position) const override;

	Vector3i get_chunk_position(const Vector3i& position) const override;

};

#endif // !VOXEL_ROOM_H