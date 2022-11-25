#ifndef SIMPLE_VOXEL_BLOCK_H
#define SIMPLE_VOXEL_BLOCK_H


#include "voxel_block_data.h"

//00'000000'00000000
#define SIMPLE_VOXEL(type,id,height) ((type << 14) | ((height - 1) << 8) | id)

#define SIMPLE_BASICS_VOXEL(id,height) SIMPLE_VOXEL(VoxelBlockData::BASICS, id, height)
#define SIMPLE_MODEL_VOXEL(id,height) SIMPLE_VOXEL(VoxelBlockData::MODEL, id, height)
#define SIMPLE_DEVICE_VOXEL(id,height) SIMPLE_VOXEL(VoxelBlockData::DEVICE, id, height)

class SimpleVoxelBlockData : public VoxelBlockData
{
	GDCLASS(SimpleVoxelBlockData, VoxelBlockData);
protected:
	PackedByteArray voxels;
	static void _bind_methods();
public:
	SimpleVoxelBlockData();
	~SimpleVoxelBlockData();
	virtual void set_size(const Vector3i& value);
	virtual Vector3i get_size() const;

	virtual void set_voxels(const PackedByteArray& value);
	virtual PackedByteArray get_voxels() const;

	virtual void set_voxel(const Vector3i& position, const Voxel& value);
	virtual Voxel get_voxel(const Vector3i& position) const;

	virtual void fill(const Voxel& voxel);
	virtual bool is_filled(const Voxel& voxel) const;

	_inline void build_basics_mesh(const int& direction, const int& height, const Array& mesh_arrays, const Vector3& position);
	_inline void build_model_mesh(Ref<ModelPreset>& model_preset, const Array& mesh_arrays, const Vector3& position);

	//virtual void build_mesh(const Ref<PresetsData>& presets_data, const Array& mesh_arrays, const Vector3i& position, const Voxel& voxel);
	//virtual Variant build_device(const Ref<DevicePreset>& device_preset, Vector3i& position);

	virtual int get_voxel_type(const Voxel& value);
	virtual int get_voxel_id(const Voxel& value);

	int get_voxel_height(const Voxel& value);

	Voxel empty_voxel();
	Voxel basics_voxel(const int& id, const int& height = 64);
	Voxel model_voxel(const int& id, const int& height = 64);
	Voxel device_voxel(const int& id, const int& height = 64);
};

#endif // !SIMPLE_VOXEL_BLOCK_H
