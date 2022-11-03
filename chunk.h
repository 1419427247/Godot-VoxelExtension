#ifndef CHUNK_H
#define CHUNK_H

#include "voxel_room.h"
#include "voxel_world.h"

class Chunk : public Node3D
{
	GDCLASS(Chunk, Node3D);
	enum Filter
	{
		EMPTY_FILTER = 0b1,
		BASICS_FILTER = 0b10,
		MESH_FILTER = 0b100,
		DEVICE_FILTER = 0b1000,
		TRANSPARENT_TRUE_FILTER = 0b010000,
		TRANSPARENT_FALSE_FILTER = 0b100000,
		COLLIDER_TRUE_FILTER = 0b10000000,
		COLLIDER_FALSE_FILTER = 0b100000000,
	};
private:

	Vector3i chunk_position;
	Array mesh_arrays;

	Dictionary devices;

protected:
	void build_basics(const Ref<PresetsData>& presets_data, Ref<BasicsPreset>& basics_preset, const Vector3i& local_position, const Vector3i& rotation);
	void build_mesh(Ref<MeshPreset>& mesh_preset, const Vector3i& local_position, const Vector3i& rotation);

	static void _bind_methods();
public:
	Chunk();
	~Chunk();

	VoxelContainer* get_voxel_container() const;

	void set_chunk_position(const Vector3i& value);
	Vector3i get_chunk_position() const;

	Dictionary get_devices() const;

	void set_voxel(const Vector3i& local_position, const Voxel& value);
	Voxel get_voxel(const Vector3i& local_position) const;

	Vector3i get_voxel_local_position(const Vector3& point, const Vector3& normal) const;

	ArrayMesh* generate_mesh(const int& filter = BASICS_FILTER | MESH_FILTER);
	ConcavePolygonShape3D* generate_collider(const int& filter = BASICS_FILTER | MESH_FILTER);
	void generate_device();
};

VARIANT_ENUM_CAST(Chunk, Chunk::Filter);

#endif
