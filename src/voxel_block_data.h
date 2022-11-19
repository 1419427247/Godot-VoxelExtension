#ifndef VOXEL_CONTAINER_DATA_H
#define VOXEL_CONTAINER_DATA_H

#include "presets_data.h"

#define EMPTY_VOXEL 0 

class VoxelBlockData : public Resource
{
	GDCLASS(VoxelBlockData, Resource);
	enum Type
	{
		EMPTY = 0,
		BASICS = 1,
		MODEL = 2,
		DEVICE = 3,
	};
protected:
	Vector3i size;
	static void _bind_methods();
public:
	VoxelBlockData();
	~VoxelBlockData();

	virtual void set_size(const Vector3i& value);
	virtual Vector3i get_size() const;

	virtual void set_voxels(const PackedByteArray& value);
	virtual PackedByteArray get_voxels() const;

	virtual void set_voxel(const Vector3i& position, const Voxel& value);
	virtual Voxel get_voxel(const Vector3i& position) const;

	virtual void fill(const Voxel& voxel);
	virtual bool is_filled(const Voxel& voxel) const;

	virtual void build_mesh(const Ref<PresetsData>& presets_data,const Array& mesh_arrays,const Vector3i& position,const Voxel& voxel);
	virtual Variant build_device(const Ref<DevicePreset>& device_preset, Vector3i& position, const Voxel& voxel);

	virtual int get_voxel_type(const Voxel& value);
	virtual int get_voxel_id(const Voxel& value);

	static Vector3 rotate_vertex(const Vector3& vertex, const Vector3i& rotation);
	static Vector3 get_triangle_normal(const Vector3& a, const Vector3& b, const Vector3& c);
};
VARIANT_ENUM_CAST(VoxelBlockData, Type);

#endif // !VOXEL_WORLD_DATA_H

