#ifndef CHUNK_H
#define CHUNK_H

#include "voxel_world.h"

class Chunk : public Node3D
{
	GDCLASS(Chunk, Node3D);
	enum
	{
		MESH_FLAG = 0b001,
		COLLIDER_FLAG = 0b0010,
		TRIGGER_FLAG = 0b0100,
		DEVICE_FLAG = 0b1000,
	};
private:
	VoxelWorld* voxel_world;
	Vector3i chunk_position;
	Array mesh_arrays;
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

	void set_voxel(const Vector3i& local_position, const Voxel& value);
	Voxel get_voxel(const Vector3i& local_position) const;

	Vector3i get_voxel_local_position(const Vector3& point, const Vector3& normal) const;

	Ref<ArrayMesh> generate_mesh();
	Ref<ConcavePolygonShape3D> generate_trigger();
};

#endif
