#ifndef VOXEL_WORLD_H
#define VOXEL_WORLD_H

#include "perset.h"

#include "texture_perset.h"
#include "material_perset.h"
#include "basics_perset.h"
#include "mesh_perset.h"

using namespace godot;

typedef int Voxel;
class VoxelWorld : public Node3D
{

	GDCLASS(VoxelWorld, Node3D);

	enum VoxelType
	{
		EMPTY = 0,
		BASICS = 1,
		MESH = 2,
		DEVICE = 3,
	};

private:
	int chunk_size;
	Vector3i chunk_count;
	Vector3i world_size;

	PackedByteArray voxels;
	Dictionary voxels_information;

	Dictionary perset_map;

	Array texture_persets;
	Array material_persets;
	Array basics_persets;
	Array mesh_persets;
	Array device_persets;

	Timer* timer;
public:
	VoxelWorld();
	~VoxelWorld();

	void set_chunk_size(const int& value);
	int get_chunk_size() const;

	void set_chunk_count(const Vector3i& value);
	Vector3i get_chunk_count() const;

	Vector3i get_world_size() const;

	int register_perset(const Ref<Perset> value);

	Array get_material_persets() const;
	Array get_basics_persets() const;
	Array get_mesh_persets() const;
	Array get_device_persets() const;

	void set_step(const double& value);
	double get_step();

	void set_voxel(const Vector3i& position, const Voxel& flag);
	Voxel get_voxel(const Vector3i& position) const;

	Vector3i get_voxel_direction(const Vector3& direction, const Vector3i& rotation) const;

	PackedByteArray save();
	void load(PackedByteArray value);

	static uint8_t get_voxel_type(const Voxel& voxel);
	static uint8_t get_voxel_id(const Voxel& voxel);
	static uint8_t get_voxel_flag(const Voxel& voxel);

	static Vector3i flag_to_rotation(const uint8_t& flag);
protected:
	void _on_timer_timeout();
	void _notification(int p_what);
	
	static void _bind_methods();
};

VARIANT_ENUM_CAST(VoxelWorld, VoxelType);

#endif // !VOXEL_WORLD_H