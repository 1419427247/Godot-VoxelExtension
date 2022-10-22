#ifndef VOXEL_WORLD_H
#define VOXEL_WORLD_H

#include "voxel_world_data.h"

class VoxelWorld : public Node3D
{
	GDCLASS(VoxelWorld, Node3D);
private:
	Ref<VoxelWorldData> voxel_world_data;
	Ref<Mutex> mutex;

	Dictionary devices;

	bool isolated;
protected:
	void _notification(int p_what);

	static void _bind_methods();
public:
	VoxelWorld();
	~VoxelWorld();

	void set_voxel_world_data(const Ref<VoxelWorldData>& value);
	Ref<VoxelWorldData> get_voxel_world_data() const;

	void set_devices(const Dictionary& value);
	Dictionary get_devices() const;

	void set_isolated(const bool& value);
	bool get_isolated() const;

	void set_voxel(const Vector3i& position, const Voxel& value);
	Voxel get_voxel(const Vector3i& position) const;

	static Vector3i get_voxel_direction(const Vector3& direction, const Vector3i& rotation);
	static int get_voxel_type(const Voxel& value);
	static int get_voxel_id(const Voxel& value);
	static int get_voxel_flag(const Voxel& value);

	static Vector3i flag_to_rotation(const int& value);

	static int rotation_to_flag(const Vector3i& value);

	static Voxel empty_voxel();
	static Voxel basics_voxel(const int& id, const Vector3i& rotation);
	static Voxel mesh_voxel(const int& id, const Vector3i& rotation);
	static Voxel device_voxel(const int& id, const int& flag = 0);
};

#endif // !VOXEL_WORLD_H