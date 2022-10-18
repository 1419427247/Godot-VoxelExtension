#ifndef VOXEL_WORLD_H
#define VOXEL_WORLD_H

#include "voxel_world_data.h"

class VoxelWorld : public Node3D
{
	GDCLASS(VoxelWorld, Node3D);
private:
	Ref<VoxelWorldData> voxel_world_data;
	bool isolated;
	Timer* timer;
protected:
	void _on_timer_timeout();
	void _notification(int p_what);

	static void _bind_methods();
public:
	VoxelWorld();
	~VoxelWorld();

	void set_voxel_world_data(const Ref<VoxelWorldData>& value);
	Ref<VoxelWorldData> get_voxel_world_data() const;

	void set_isolated(const bool& value);
	bool get_isolated() const;

	void set_step(const double& value);
	double get_step();
};


#endif // !VOXEL_WORLD_H