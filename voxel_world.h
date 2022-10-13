#ifndef VOXEL_WORLD_H
#define VOXEL_WORLD_H

#include "perset.h"

#include "material_perset.h"
#include "basics_perset.h"
#include "mesh_perset.h"
#include "device_perset.h"

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
	Vector3i chunk_size;
	Vector3i chunk_count;
	Vector3i world_size;

	bool isolated;

	PackedByteArray voxels;
	Dictionary voxels_information;

	Timer* timer;

	Dictionary perset_map;
	Array material_persets;
	Array basics_persets;
	Array mesh_persets;
	Array device_persets;
protected:
	void _on_timer_timeout();
	void _notification(int p_what);

	static void _bind_methods();
public:

	VoxelWorld();
	~VoxelWorld();

	void set_chunk_size(const Vector3i& value);
	Vector3i get_chunk_size() const;

	void set_chunk_count(const Vector3i& value);
	Vector3i get_chunk_count() const;

	Vector3i get_world_size() const;

	void set_isolated(const bool& value);
	bool get_isolated() const;

	void set_step(const double& value);
	double get_step();

	int register_perset(const Ref<Perset>& value);
	Array get_material_persets();
	Array get_basics_persets();
	Array get_mesh_persets();
	Array get_device_persets();


	void set_voxel(const Vector3i& position, const Voxel& voxel);
	Voxel get_voxel(const Vector3i& position) const;

	Vector3i get_voxel_direction(const Vector3& direction, const Vector3i& rotation) const;

	PackedByteArray save();
	void load(PackedByteArray value);

	static int get_voxel_type(const Voxel& voxel);
	static int get_voxel_id(const Voxel& voxel);
	static int get_voxel_flag(const Voxel& voxel);

	static Vector3i flag_to_rotation(const int& flag);

	static Voxel empty_voxel();
	static Voxel basics_voxel(const int& id, const Vector3i& rotation);
	static Voxel mesh_voxel(const int& id, const Vector3i& rotation);
	static Voxel device_voxel(const int& id);

};

VARIANT_ENUM_CAST(VoxelWorld, VoxelType);

#endif // !VOXEL_WORLD_H