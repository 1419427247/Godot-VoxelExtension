#ifndef VOXEL_WORLD_DATA_H
#define VOXEL_WORLD_DATA_H
#include "preset.h"

#include "material_preset.h"
#include "basics_preset.h"
#include "mesh_preset.h"
#include "device_preset.h"


//type : 2
//id : 10
//flag : 20

typedef unsigned int Voxel;
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
	Vector3i world_size;
protected:
	static void _bind_methods();
public:
	Vector3i chunk_size;
	Vector3i chunk_count;

	PackedInt32Array voxels;

	Dictionary voxels_information;

	Dictionary preset_map;

	TypedArray<MaterialPreset> material_presets;
	TypedArray<BasicsPreset> basics_presets;
	TypedArray<MeshPreset> mesh_presets;
	TypedArray<DevicePreset> device_presets;

	VoxelWorldData();
	~VoxelWorldData();

	void set_chunk_size(const Vector3i& value);
	Vector3i get_chunk_size() const;

	void set_chunk_count(const Vector3i& value);
	Vector3i get_chunk_count() const;

	Vector3i get_world_size() const;

	void set_voxels(const PackedInt32Array& value);
	PackedInt32Array get_voxels() const;

	void set_material_presets(const TypedArray <MaterialPreset>& value);
	TypedArray <MaterialPreset> get_material_presets();

	void set_basics_presets(const TypedArray <BasicsPreset>& value);
	TypedArray <BasicsPreset> get_basics_presets();

	void set_mesh_presets(const TypedArray <MeshPreset>& value);
	TypedArray <MeshPreset> get_mesh_presets();

	void set_device_presets(const TypedArray <DevicePreset>& value);
	TypedArray <DevicePreset> get_device_presets();

	int register_preset(const Ref<Preset>& value);

};
#endif // !VOXEL_WORLD_DATA_H

VARIANT_ENUM_CAST(VoxelWorldData, VoxelType);
