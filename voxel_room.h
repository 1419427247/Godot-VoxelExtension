#ifndef VOXEL_WORLD_H
#define VOXEL_WORLD_H

#include "voxel_room_data.h"
#include "presets_data.h"
#include "device.h"

class VoxelRoom : public Node3D
{
	GDCLASS(VoxelRoom, Node3D);
private:
	Ref<PresetsData> presets_data;
	Ref<VoxelRoomData> voxel_room_data;
	bool isolated;
protected:
	static void _bind_methods();
public:
	VoxelRoom();
	~VoxelRoom();

	void set_presets_data(const Ref<PresetsData>& value);
	Ref<PresetsData> get_presets_data() const;

	void set_voxel_room_data(const Ref<VoxelRoomData>& value);
	Ref<VoxelRoomData> get_voxel_room_data() const;

	void set_isolated(const bool& value);
	bool get_isolated() const;

	void set_voxel(const Vector3i& position, const Voxel& value);
	Voxel get_voxel(const Vector3i& position) const;

	static Vector3i get_voxel_direction(const Vector3i& direction, const Vector3i& rotation);

	static int get_voxel_type(const Voxel& value);
	static int get_voxel_id(const Voxel& value);
	static Vector3i get_voxel_rotation(const Voxel& value);
	static int get_voxel_flag(const Voxel& value);

	static Voxel empty_voxel();
	static Voxel basics_voxel(const int& id, const Vector3i& rotation, const int& flag = 0);
	static Voxel mesh_voxel(const int& id, const Vector3i& rotation, const int& flag = 0);
	static Voxel device_voxel(const int& id, const Vector3i& rotation, const int& flag = 0);
};

#endif // !VOXEL_WORLD_H