#ifndef CHUNK_H
#define CHUNK_H

#include "voxel_world.h"

class BasicsPerset;

class Chunk : public Node3D
{
	GDCLASS(Chunk, Node3D);

private:
	Dictionary data;
	
	Vector3i chunk_position;

	VoxelWorld* voxel_world;
	MeshInstance3D* mesh_instance;
	
	StaticBody3D* collision;
	CollisionShape3D* collision_shap;

	Area3D* trigger;
	CollisionShape3D* trigger_shap;

	Array mesh_arrays;
public:
	Chunk();
	~Chunk();

	void set_chunk_position(const Vector3i& value);
	Vector3i get_chunk_position() const;

	void set_voxel(const Vector3i& local_position,const Voxel& voxel);
	Voxel get_voxel(const Vector3i& local_position) const;

	Vector3i get_voxel_local_position(const Vector3& point, const Vector3& normal) const;

	void generate_mesh();
	void generate_collider();
	void generate_trigger();

protected:
	void draw_basics_mesh(const Ref<BasicsPerset>& basics_perset, const Vector3i& relative_position, const Vector3i& rotation);
	Array get_mesh_array(const int& index);
	static void _bind_methods();
	void _notification(int p_what);
};

#endif
