#ifndef STANDARD_VOXEL_BLOCK_DATA
#define STANDARD_VOXEL_BLOCK_DATA

#include "voxel_block_data.h"

#define STANDARD_VOXEL(type,id,rotation) (((type & 0b11) << 30) | ((id & 0b111111111111111) << 15) | (abs(rotation.x % 360 / 15) << 10) | (abs(rotation.y % 360 / 15)) << 5 | (abs(rotation.z % 360 / 15)))

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
	virtual void set_size(const Vector3i& value) override;
	virtual Vector3i get_size() const override;

	virtual void set_voxels(const PackedByteArray& value) override;
	virtual PackedByteArray get_voxels() const override;

	virtual void set_voxel(const Vector3i& position, const Voxel& value) override;
	virtual Voxel get_voxel(const Vector3i& position) const override;

	virtual void fill(const Voxel& voxel) override;
	virtual bool is_filled(const Voxel& voxel) const override;

	_inline void _basics_mesh(const Ref<BasicsMesh>& basics_mesh, const Array& mesh_arrays, const int& direction, const Vector3& position, const Vector3& rotation);
	_inline void _model_mesh(const Ref<ModelPreset>& model_preset, const Array& mesh_arrays, const int& mask, const Vector3& position, const Vector3& rotation);

	virtual void _build_basics_mesh(const Ref<PresetsData>& presets_data, const Ref<BasicsPreset>& basics_preset, const Voxel& voxel, const Array& mesh_arrays, const Vector3i& position) override;
	virtual void _build_model_mesh(const Ref<PresetsData>& presets_data, const Ref<ModelPreset>& model_preset, const Voxel& voxel, const Array& mesh_arrays, const Vector3i& position) override;
	virtual Variant _build_device(const Ref<DevicePreset>& device_preset, const Vector3i& position, const Voxel& voxel) override;

	virtual int _get_voxel_type(const Voxel& value) override;
	virtual int _get_voxel_id(const Voxel& value) override;

	_inline static int get_voxel_type(const Voxel& value);
	_inline static int get_voxel_id(const Voxel& value);
	_inline static Vector3i get_voxel_rotation(const Voxel& value);
	_inline static Vector3i get_voxel_direction(const int& direction, const Vector3i& rotation);
	_inline static Voxel empty_voxel();
	_inline static Voxel basics_voxel(const int& id, const Vector3i& rotation = Vector3i());
	_inline static Voxel model_voxel(const int& id, const Vector3i& rotation = Vector3i());
	_inline static Voxel device_voxel(const int& id, const Vector3i& rotation = Vector3i());
};

#endif // !STANDARD_VOXEL_BLOCK_DATA
