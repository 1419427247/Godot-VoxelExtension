#ifndef CHUNK_H
#define CHUNK_H

#include "voxel_room.h"

class Chunk : public Node3D
{
	GDCLASS(Chunk, Node3D);
private:
	VoxelRoom* voxel_room;
	Vector3i chunk_position;
	Array mesh_arrays;

	Dictionary devices;
protected:
	Array get_mesh_array(const int& index);

	void build_basics(const Ref<PresetsData>& presets_data, const Ref<VoxelRoomData>& voxel_room_data, Ref<BasicsPreset>& basics_preset, const Vector3i& local_position, const Vector3i& rotation);
	void build_mesh(const Ref<VoxelRoomData>& voxel_room_data, Ref<MeshPreset>& mesh_preset, const Vector3i& local_position, const Vector3i& rotation);

	static void _bind_methods();
	void _notification(int p_what);

public:
	Chunk();
	~Chunk();

	void set_chunk_position(const Vector3i& value);
	Vector3i get_chunk_position() const;

	Dictionary get_devices() const;

	void set_voxel(const Vector3i& local_position, const Voxel& value);
	Voxel get_voxel(const Vector3i& local_position) const;

	Vector3i get_voxel_local_position(const Vector3& point, const Vector3& normal) const;

	Ref<ArrayMesh> generate_mesh();
	Ref<ConcavePolygonShape3D> generate_collider();
	void generate_device();

	void print_error(const String& value) const;
};

#endif
