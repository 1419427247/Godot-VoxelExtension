#ifndef VOXEL_WORLD_H
#define VOXEL_WORLD_H

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/array_mesh.hpp>

using namespace godot;

class Chunk;
class BasicsPerset;

class VoxelWorld : public Node3D
{
	GDCLASS(VoxelWorld, Node3D);

	friend class Chunk;
	friend class BasicsPerset;
private:
	int chunk_size;
	Vector3i chunk_count;
	Vector3i world_size;

	PackedByteArray voxels;
	Dictionary voxels_information;

	Array material_persets;
	Array basics_persets;
	Array device_persets;
public:
	enum VoxelType
	{
		EMPTY = 0,
		BASICS = 1,
		MESH = 2,
		DEVICE = 3,
	};

	VoxelWorld();
	~VoxelWorld();

	int get_chunk_size();
	Vector3i get_chunk_count();
	Vector3i get_world_size();

	void set_chunk_size(const int& value);
	void set_chunk_count(const Vector3i& value);


	Array get_material_persets() const;
	Array get_basics_persets() const;
	Array get_device_persets() const;

	void set_material_persets(const Array& value);
	void set_basics_persets(const Array& value);
	void set_device_persets(const Array& value);

	void set_voxel(const int& type, const int& id, const Vector3i& position, const Vector3i& rotation);
	int get_voxel_type(const Vector3i& position) const;
	int get_voxel_id(const Vector3i& position) const;
	Vector3i get_voxel_rotation(const Vector3i& position) const;

	Vector3i get_voxel_relative_position(const Vector3i& position, const Vector3& direction, const Vector3i& rotation) const;

protected:
	static void _bind_methods();

	void _notification(int p_what);
};

VARIANT_ENUM_CAST(VoxelWorld, VoxelType);

#endif // !VOXEL_WORLD_H