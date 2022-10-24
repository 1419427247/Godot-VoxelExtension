#ifndef VOXEL_WORLD_H
#define VOXEL_WORLD_H

#include "voxel_world_data.h"
#include "presets_data.h"

class VoxelWorld : public Node3D
{
	GDCLASS(VoxelWorld, Node3D);
private:
	Ref<PresetsData> presets_data;
	Ref<VoxelWorldData> voxel_world_data;
	bool isolated;
protected:
	static void _bind_methods();
public:
	VoxelWorld();
	~VoxelWorld();

	void set_presets_data(const Ref<PresetsData>& value);
	Ref<PresetsData> get_presets_data() const;

	void set_voxel_world_data(const Ref<VoxelWorldData>& value);
	Ref<VoxelWorldData> get_voxel_world_data() const;

	void set_isolated(const bool& value);
	bool get_isolated() const;

	void set_voxel(const Vector3i& position, const Voxel& value);
	Voxel get_voxel(const Vector3i& position) const;

	static Vector3i get_voxel_direction(const Vector3& direction, const Vector3i& rotation);

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