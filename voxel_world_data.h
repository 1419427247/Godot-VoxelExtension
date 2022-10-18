#ifndef VOXEL_WORLD_DATA_H
#define VOXEL_WORLD_DATA_H
#include "preset.h"

#include "material_preset.h"
#include "basics_preset.h"
#include "mesh_preset.h"
#include "device_preset.h"

typedef int Voxel;
class VoxelWorldData : public Resource
{
	GDCLASS(VoxelWorldData, Resource);
	enum VoxelType
	{
		EMPTY = 0,
		BASICS = 1,
		MESH = 2,
		DEVICE = 3,
	};
private:
	Vector3i chunk_size;
	Vector3i chunk_count;

	Vector3i world_size;

	PackedByteArray voxels;
	Dictionary voxels_information;

	Dictionary preset_map;

	TypedArray<MaterialPreset> material_presets;
	TypedArray<BasicsPreset> basics_presets;
	TypedArray<MeshPreset> mesh_presets;
	TypedArray<DevicePreset> device_presets;
protected:
	static void _bind_methods();
public:
	VoxelWorldData();
	~VoxelWorldData();

	void set_chunk_size(const Vector3i& value);
	Vector3i get_chunk_size() const;

	void set_chunk_count(const Vector3i& value);
	Vector3i get_chunk_count() const;

	Vector3i get_world_size() const;

	void set_voxels(const PackedByteArray& value);
	PackedByteArray get_voxels() const;

	void set_material_presets(const TypedArray <MaterialPreset>& value);
	TypedArray <MaterialPreset> get_material_presets();

	void set_basics_presets(const TypedArray <BasicsPreset>& value);
	TypedArray <BasicsPreset> get_basics_presets();

	void set_mesh_presets(const TypedArray <MeshPreset>& value);
	TypedArray <MeshPreset> get_mesh_presets();

	void set_device_presets(const TypedArray <DevicePreset>& value);
	TypedArray <DevicePreset> get_device_presets();

	int register_preset(const Ref<Preset>& value);

	void set_voxel(const Vector3i& position, const Voxel& voxel);
	Voxel get_voxel(const Vector3i& position) const;

	static Vector3i get_voxel_direction(const Vector3& direction, const Vector3i& rotation);
	static int get_voxel_type(const Voxel& voxel);
	static int get_voxel_id(const Voxel& voxel);
	static int get_voxel_flag(const Voxel& voxel);

	static Vector3i flag_to_rotation(const int& flag);

	static Voxel empty_voxel();
	static Voxel basics_voxel(const int& id, const Vector3i& rotation);
	static Voxel mesh_voxel(const int& id, const Vector3i& rotation);
	static Voxel device_voxel(const int& id);
};
#endif // !VOXEL_WORLD_DATA_H

VARIANT_ENUM_CAST(VoxelWorldData, VoxelType);
