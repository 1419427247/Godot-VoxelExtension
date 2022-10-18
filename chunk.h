#ifndef CHUNK_H
#define CHUNK_H

#include "voxel_world.h"

class Chunk : public Node3D
{
	GDCLASS(Chunk, Node3D);
private:
	Vector3i chunk_position;
	Dictionary data;

	VoxelWorld* voxel_world;

	MeshInstance3D* mesh_instance;

	StaticBody3D* collision;
	CollisionShape3D* collision_shap;

	Area3D* trigger;
	CollisionShape3D* trigger_shap;

	Array basics_arrays;
	Array mesh_arrays;
	Array device_arrays;
protected:
	Array get_mesh_array(const int& index);
	void build_basics(const Ref<VoxelWorldData>& voxel_world_data, Ref<BasicsPreset>& basics_preset, const Vector3i& local_position, const Vector3i& rotation);
	void build_mesh(const Ref<VoxelWorldData>& voxel_world_data, Ref<MeshPreset>& mesh_preset, const Vector3i& local_position, const Vector3i& rotation);
	static void _bind_methods();
	void _notification(int p_what);

public:
	Chunk();
	~Chunk();

	void set_chunk_position(const Vector3i& value);
	Vector3i get_chunk_position() const;

	void set_voxel(const Vector3i& local_position, const Voxel& voxel);
	Voxel get_voxel(const Vector3i& local_position) const;

	Vector3i get_voxel_local_position(const Vector3& point, const Vector3& normal) const;

	void generate_mesh();
	void generate_collider();
	void generate_trigger();
};

#endif
