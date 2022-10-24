#ifndef CHUNK_DATA_H
#define CHUNK_DATA_H

#include"presets_data.h"

//type : 2
//id : 10
//rotation: 15
//flag : 5

class ChunkData : public Resource
{
	GDCLASS(ChunkData, Resource);
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

	Dictionary preset_map;

	ChunkData();
	~ChunkData();

	void set_chunk_size(const Vector3i& value);
	Vector3i get_chunk_size() const;

	void set_chunk_count(const Vector3i& value);
	Vector3i get_chunk_count() const;

	Vector3i get_world_size() const;

	void set_voxels(const PackedByteArray& value);
	PackedByteArray get_voxels() const;

	void set_custom_materials(const TypedArray <CustomMaterial>& value);
	TypedArray <CustomMaterial> get_custom_materials();

	void set_basics_presets(const TypedArray <BasicsPreset>& value);
	TypedArray <BasicsPreset> get_basics_presets();

	void set_mesh_presets(const TypedArray <MeshPreset>& value);
	TypedArray <MeshPreset> get_mesh_presets();

	void set_device_presets(const TypedArray <DevicePreset>& value);
	TypedArray <DevicePreset> get_device_presets();

	//int register_preset(const Ref<Preset>& value);

};
VARIANT_ENUM_CAST(ChunkData, VoxelType);
#endif // !CHUNK_DATA_H