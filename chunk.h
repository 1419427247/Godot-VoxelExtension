#ifndef CHUNK_H
#define CHUNK_H

#include "voxel_room.h"

class Chunk : public Node3D
{
	GDCLASS(Chunk, Node3D);
	enum Filter
	{
		BASICS_FILTER = 0b1,
		MESH_FILTER = 0b10,
		DEVICE_FILTER = 0b100,
		TRANSPARENT_TRUE_FILTER = 0b01000,
		TRANSPARENT_FALSE_FILTER = 0b10000,
		COLLIDER_TRUE_FILTER = 0b1000000,
		COLLIDER_FALSE_FILTER = 0b10000000,
	};
private:
	Vector3i chunk_position;
	Array mesh_arrays;

	Dictionary devices;
protected:
	Array get_mesh_array(const int& index);

	void build_basics(const Ref<PresetsData>& presets_data, const Ref<VoxelRoomData>& voxel_room_data, Ref<BasicsPreset>& basics_preset, const Vector3i& local_position, const Vector3i& rotation);
	void build_mesh(const Ref<VoxelRoomData>& voxel_room_data, Ref<MeshPreset>& mesh_preset, const Vector3i& local_position, const Vector3i& rotation);

	static void _bind_methods();
public:
	Chunk();
	~Chunk();

	VoxelRoom* get_voxel_room() const;

	void set_chunk_position(const Vector3i& value);
	Vector3i get_chunk_position() const;

	Dictionary get_devices() const;

	void set_voxel(const Vector3i& local_position, const Voxel& value);
	Voxel get_voxel(const Vector3i& local_position) const;

	Vector3i get_voxel_local_position(const Vector3& point, const Vector3& normal) const;

	ArrayMesh* generate_mesh(const int& filter = BASICS_FILTER | MESH_FILTER);
	ConcavePolygonShape3D* generate_collider(const int& filter = BASICS_FILTER | MESH_FILTER);
	void generate_device();

	void print_error(const String& value) const;
};

VARIANT_ENUM_CAST(Chunk, Chunk::Filter);

#endif
