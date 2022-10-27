#ifndef VOXEL_WORLD_H
#define VOXEL_WORLD_H

#include"voxel_container.h"

class VoxelRoom : public VoxelContainer
{
	GDCLASS(VoxelRoom, VoxelContainer);
private:
	Ref<VoxelRoomData> voxel_room_data;
protected:
	static void _bind_methods();

public:
	VoxelRoom();
	~VoxelRoom();

	void set_voxel_room_data(const Ref<VoxelRoomData>& value);
	Ref<VoxelRoomData> get_voxel_room_data() const;

	void set_voxel(const Vector3i& position, const Voxel& value);
	Voxel get_voxel(const Vector3i& position) const;
};

#endif // !VOXEL_WORLD_H