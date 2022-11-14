#ifndef VOXEL_BLOCK_H
#define VOXEL_BLOCK_H

#include "voxel_room.h"
#include "voxel_world.h"

class VoxelBlock : public Node3D
{
	GDCLASS(VoxelBlock, Node3D);
protected:
	Vector3i key;
	Dictionary devices;
	Array mesh_arrays;

	static void _bind_methods();
public:
	VoxelBlock();
	~VoxelBlock();

	VoxelContainer* get_voxel_container() const;

	void set_key(const Vector3i& value);
	Vector3i get_key() const;

	Dictionary get_devices() const;

	void set_voxel(const Vector3i& position, const Voxel& value);
	Voxel get_voxel(const Vector3i& position) const;

	Vector3 point_converted_to_block(const Vector3& point)const;
	Vector3 normal_converted_to_block(const Vector3& point)const;
	Vector3i get_voxel_local_position(const Vector3& point, const Vector3& normal) const;

	ArrayMesh* generate_mesh(const int& filter = 0b1);
	ConcavePolygonShape3D* generate_collider(const int& filter = 0b1);
	void generate_device(const int& filter = 0b1);


	bool is_filled(const Voxel& voxel) const;
};

#endif
