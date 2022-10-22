#include "voxel_world_data.h"

void VoxelWorldData::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_chunk_size", "value"), &VoxelWorldData::set_chunk_size);
	ClassDB::bind_method(D_METHOD("get_chunk_size"), &VoxelWorldData::get_chunk_size);

	ClassDB::bind_method(D_METHOD("set_chunk_count", "value"), &VoxelWorldData::set_chunk_count);
	ClassDB::bind_method(D_METHOD("get_chunk_count"), &VoxelWorldData::get_chunk_count);

	ClassDB::bind_method(D_METHOD("get_world_size"), &VoxelWorldData::get_world_size);

	ClassDB::bind_method(D_METHOD("set_voxels", "value"), &VoxelWorldData::set_voxels);
	ClassDB::bind_method(D_METHOD("get_voxels"), &VoxelWorldData::get_voxels);

	//ClassDB::bind_method(D_METHOD("register_preset"), &VoxelWorldData::register_preset);

	ClassDB::bind_method(D_METHOD("set_custom_materials"), &VoxelWorldData::set_custom_materials);
	ClassDB::bind_method(D_METHOD("get_custom_materials"), &VoxelWorldData::get_custom_materials);

	ClassDB::bind_method(D_METHOD("set_basics_presets"), &VoxelWorldData::set_basics_presets);
	ClassDB::bind_method(D_METHOD("get_basics_presets"), &VoxelWorldData::get_basics_presets);

	ClassDB::bind_method(D_METHOD("set_mesh_presets"), &VoxelWorldData::set_mesh_presets);
	ClassDB::bind_method(D_METHOD("get_mesh_presets"), &VoxelWorldData::get_mesh_presets);

	ClassDB::bind_method(D_METHOD("set_device_presets"), &VoxelWorldData::set_device_presets);
	ClassDB::bind_method(D_METHOD("get_device_presets"), &VoxelWorldData::get_device_presets);



	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "chunk_size"), "set_chunk_size", "get_chunk_size");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "chunk_count"), "set_chunk_count", "get_chunk_count");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_BYTE_ARRAY, "voxels"), "set_voxels", "get_voxels");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "custom_materials", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::OBJECT) + "/" + String::num_int64(PROPERTY_HINT_RESOURCE_TYPE) + ":CustomMaterial"), "set_custom_materials", "get_custom_materials");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "basics_presets", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::OBJECT) + "/" + String::num_int64(PROPERTY_HINT_RESOURCE_TYPE) + ":BasicsPreset"), "set_basics_presets", "get_basics_presets");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "mesh_presets", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::OBJECT) + "/" + String::num_int64(PROPERTY_HINT_RESOURCE_TYPE) + ":MeshPreset"), "set_mesh_presets", "get_mesh_presets");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "device_presets", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::OBJECT) + "/" + String::num_int64(PROPERTY_HINT_RESOURCE_TYPE) + ":DevicePreset"), "set_device_presets", "get_device_presets");

	BIND_ENUM_CONSTANT(EMPTY);
	BIND_ENUM_CONSTANT(BASICS);
	BIND_ENUM_CONSTANT(MESH);
	BIND_ENUM_CONSTANT(DEVICE);
}

VoxelWorldData::VoxelWorldData()
{
	set_chunk_size(Vector3i(8, 8, 8));
	set_chunk_count(Vector3i(1, 1, 1));
}

VoxelWorldData::~VoxelWorldData()
{
}


void VoxelWorldData::set_chunk_size(const Vector3i& value) {
	if (value.x <= 0 || value.y <= 0 || value.z <= 0)
	{
		UtilityFunctions::printerr("Chunk size is an invalid value");
		return;
	}
	this->chunk_size = value;
	world_size = chunk_count * chunk_size;
	voxels.resize(world_size.x * world_size.y * world_size.z);
}

Vector3i VoxelWorldData::get_chunk_size() const {
	return chunk_size;
}

void VoxelWorldData::set_chunk_count(const Vector3i& value) {
	if (value.x <= 0 || value.y <= 0 || value.z <= 0)
	{
		UtilityFunctions::printerr("Chunk count is an invalid value");
		return;
	}
	chunk_count = value;
	world_size = chunk_count * chunk_size;
	voxels.resize(world_size.x * world_size.y * world_size.z);
}

Vector3i VoxelWorldData::get_chunk_count() const {
	return chunk_count;
}

Vector3i VoxelWorldData::get_world_size() const {
	return world_size;
}

void VoxelWorldData::set_voxels(const PackedInt32Array& value)
{
	voxels = value;
}

PackedInt32Array VoxelWorldData::get_voxels() const
{
	return voxels;
}

//int VoxelWorldData::register_preset(const Ref<Preset>& value)
//{
//	String uuid = value->get_uuid();
//	int index = -1;
//	if (preset_map.get(uuid, nullptr).get_type() != Variant::NIL) {
//		UtilityFunctions::printerr("This preset + " + value->get_name() + " + is already registered");
//		return index;
//	}
//	String name = value->get_class();
//	Array presets;
//	if (name == StringName("CustomMaterial")) {
//		presets = custom_materials;
//	}
//	else if (name == StringName("BasicsPreset")) {
//		presets = basics_presets;
//	}
//	else if (name == StringName("DevicePreset")) {
//		presets = device_presets;
//	}
//	else {
//		UtilityFunctions::printerr("This object + " + value->get_class() + " + is not a preset");
//		return index;
//	}
//	for (index = 0; index < presets.size(); index++)
//	{
//		if (presets[index].get_type() == Variant::NIL) {
//			preset_map[uuid] = index;
//			presets[index] = value;
//			return index;
//		}
//	}
//	index = presets.size();
//	presets.push_back(value);
//	preset_map[uuid] = index;
//	return index;
//}

void VoxelWorldData::set_custom_materials(const TypedArray <CustomMaterial>& value)
{
	custom_materials = value;
}

TypedArray <CustomMaterial> VoxelWorldData::get_custom_materials() {
	return custom_materials;
}

void VoxelWorldData::set_basics_presets(const TypedArray <BasicsPreset>& value)
{
	basics_presets = value;
}

TypedArray <BasicsPreset> VoxelWorldData::get_basics_presets()
{
	return basics_presets;
}

void VoxelWorldData::set_mesh_presets(const TypedArray <MeshPreset>& value)
{
	mesh_presets = value;
}

TypedArray <MeshPreset> VoxelWorldData::get_mesh_presets()
{
	return mesh_presets;
}

void VoxelWorldData::set_device_presets(const TypedArray <DevicePreset>& value)
{
	device_presets = value;
}

TypedArray <DevicePreset> VoxelWorldData::get_device_presets() {
	return device_presets;
}

