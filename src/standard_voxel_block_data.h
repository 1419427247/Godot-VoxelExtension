#ifndef STANDARD_VOXEL_BLOCK_DATA
#define STANDARD_VOXEL_BLOCK_DATA

#include "voxel_block_data.h"

#define STANDARD_VOXEL(type,id,rotation) ((type << 30) | (id << 15) | (abs(rotation.x % 360 / 15) << 10) | (abs(rotation.y % 360 / 15)) << 5 | (abs(rotation.z % 360 / 15)))

#define STANDARD_BASICS_VOXEL(id,rotation) STANDARD_VOXEL(VoxelBlockData::BASICS, id, rotation)
#define STANDARD_MODEL_VOXEL(id,rotation) STANDARD_VOXEL(VoxelBlockData::MODEL, id, rotation)
#define STANDARD_DEVICE_VOXEL(id,rotation) STANDARD_VOXEL(VoxelBlockData::DEVICE, id, rotation)

class StandardVoxelBlockData : public VoxelBlockData
{
	GDCLASS(StandardVoxelBlockData, VoxelBlockData);
protected:
	PackedInt32Array voxels;
	static void _bind_methods();
public:
	StandardVoxelBlockData();
	~StandardVoxelBlockData();
	virtual void set_size(const Vector3i& value);
	virtual Vector3i get_size() const;

	virtual void set_voxels(const PackedByteArray& value);
	virtual PackedByteArray get_voxels() const;

	virtual void set_voxel(const Vector3i& position, const Voxel& value);
	virtual Voxel get_voxel(const Vector3i& position) const;

	virtual void fill(const Voxel& voxel);
	virtual bool is_filled(const Voxel& voxel) const;

	_inline void build_basics_mesh(const int& direction, const Array& arrays, const Vector3& position, const Vector3& rotation);
	_inline void build_model_mesh(Ref<ModelPreset>& model_preset, const Array& mesh_arrays, const Vector3& position, const Vector3& rotation);

	virtual void build_mesh(const Ref<PresetsData>& presets_data, const Array& mesh_arrays, const Vector3i& position, const Voxel& voxel);
	virtual Variant build_device(const Ref<DevicePreset>& device_preset, Vector3i& position, const Voxel& voxel);

	int get_voxel_type(const Voxel& value) override;
	int get_voxel_id(const Voxel& value) override;
	Vector3i get_voxel_rotation(const Voxel& value);
	Vector3i get_voxel_direction(const int& direction, const Vector3i& rotation);
	Voxel empty_voxel();
	Voxel basics_voxel(const int& id, const Vector3i& rotation = Vector3i());
	Voxel model_voxel(const int& id, const Vector3i& rotation = Vector3i());
	Voxel device_voxel(const int& id, const Vector3i& rotation = Vector3i());
};

#endif // !STANDARD_VOXEL_BLOCK_DATA
