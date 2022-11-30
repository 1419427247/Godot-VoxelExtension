#ifndef VOXEL_CONTAINER_DATA_H
#define VOXEL_CONTAINER_DATA_H

#include "voxel_container.h"

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
	Vector3i key;
	Vector3i size;
	Ref<PresetsData> presets_data;
	VoxelContainer* voxel_container;
	bool use_custom_datas;
	Array custom_datas;
	
	Dictionary devices;

	static void _bind_methods();

	virtual void _build_basics_mesh(const Ref<PresetsData>& presets_data, const Ref<BasicsPreset>& basics_preset, const Voxel& voxel, const Array& mesh_arrays, const Vector3i& position);
	virtual void _build_model_mesh(const Ref<PresetsData>& presets_data, const Ref<ModelPreset>& model_preset, const Voxel& voxel, const Array& mesh_arrays, const Vector3i& position);
	virtual Variant _build_device(const Ref<DevicePreset>& device_preset, const Vector3i& position, const Voxel& voxel);

	virtual int _get_voxel_type(const Voxel& value);
	virtual int _get_voxel_id(const Voxel& value);
public:
	VoxelBlockData();
	~VoxelBlockData();

	void set_key(const Vector3i& value);
	Vector3i get_key() const;

	virtual void set_size(const Vector3i& value);
	virtual Vector3i get_size() const;

	void set_presets_data(const Ref<PresetsData>& value);
	Ref<PresetsData> get_presets_data() const;

	void set_voxel_container(Variant value);
	Variant get_voxel_container() const;

	void set_use_custom_datas(const bool& value);
	bool is_use_custom_datas();

	void set_custom_datas(const Array& value);
	Array get_custom_datas() const;

	TypedArray<Device> get_devices() const;

	virtual void set_voxels(const PackedByteArray& value);
	virtual PackedByteArray get_voxels() const;

	virtual void set_voxel(const Vector3i& position, const Voxel& value);
	virtual Voxel get_voxel(const Vector3i& position) const;
	
	void set_custom_data(const Vector3i& position, const Variant& value);
	Variant get_custom_data(const Vector3i& position);

	virtual void fill(const Voxel& voxel);
	virtual bool is_filled(const Voxel& voxel) const;

	ArrayMesh* generate_mesh(const int& filter = 0b1);
	ConcavePolygonShape3D* generate_collider(const int& filter = 0b1);
	TypedArray<Device> generate_device(const int& filter = 0b1);

	_inline static Vector3 translate_point_to_voxel_block_coordinatet(const Transform3D& global_transform, const Vector3& point);
	_inline static Vector3 translate_normal_to_voxel_block_coordinatet(const Transform3D& global_transform, const Vector3& point);
	_inline static Vector3i get_voxel_position(const Transform3D& global_transform, const Vector3& point, const Vector3& normal);
};
VARIANT_ENUM_CAST(VoxelBlockData, Type);

#endif // !VOXEL_WORLD_DATA_H

	