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

	ClassDB::bind_method(D_METHOD("register_preset"), &VoxelWorldData::register_preset);

	ClassDB::bind_method(D_METHOD("set_material_presets"), &VoxelWorldData::set_material_presets);
	ClassDB::bind_method(D_METHOD("get_material_presets"), &VoxelWorldData::get_material_presets);

	ClassDB::bind_method(D_METHOD("set_basics_presets"), &VoxelWorldData::set_basics_presets);
	ClassDB::bind_method(D_METHOD("get_basics_presets"), &VoxelWorldData::get_basics_presets);

	ClassDB::bind_method(D_METHOD("set_mesh_presets"), &VoxelWorldData::set_mesh_presets);
	ClassDB::bind_method(D_METHOD("get_mesh_presets"), &VoxelWorldData::get_mesh_presets);

	ClassDB::bind_method(D_METHOD("set_device_presets"), &VoxelWorldData::set_device_presets);
	ClassDB::bind_method(D_METHOD("get_device_presets"), &VoxelWorldData::get_device_presets);

	ClassDB::bind_method(D_METHOD("set_voxel", "position", "voxel"), &VoxelWorldData::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel", "position"), &VoxelWorldData::get_voxel);

	ClassDB::bind_static_method("VoxelWorldData", D_METHOD("get_voxel_direction", "direction", "rotation"), &VoxelWorldData::get_voxel_direction);
	ClassDB::bind_static_method("VoxelWorldData", D_METHOD("get_voxel_type", "voxel"), &VoxelWorldData::get_voxel_type);
	ClassDB::bind_static_method("VoxelWorldData", D_METHOD("get_voxel_id", "voxel"), &VoxelWorldData::get_voxel_id);
	ClassDB::bind_static_method("VoxelWorldData", D_METHOD("get_voxel_flag", "voxel"), &VoxelWorldData::get_voxel_flag);

	ClassDB::bind_static_method("VoxelWorldData", D_METHOD("empty_voxel"), &VoxelWorldData::empty_voxel);
	ClassDB::bind_static_method("VoxelWorldData", D_METHOD("basics_voxel", "id", "rotation"), &VoxelWorldData::basics_voxel);
	ClassDB::bind_static_method("VoxelWorldData", D_METHOD("mesh_voxel", "id", "rotation"), &VoxelWorldData::mesh_voxel);
	ClassDB::bind_static_method("VoxelWorldData", D_METHOD("device_voxel""id"), &VoxelWorldData::device_voxel);

	ClassDB::add_property("VoxelWorldData", PropertyInfo(Variant::VECTOR3I, "chunk_size"), "set_chunk_size", "get_chunk_size");
	ClassDB::add_property("VoxelWorldData", PropertyInfo(Variant::VECTOR3I, "chunk_count"), "set_chunk_count", "get_chunk_count");

	ClassDB::add_property("VoxelWorldData", PropertyInfo(Variant::PACKED_BYTE_ARRAY, "voxels"), "set_voxels", "get_voxels");

	ClassDB::add_property("VoxelWorldData", PropertyInfo(Variant::ARRAY, "material_presets", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::OBJECT) + "/" + String::num_int64(PROPERTY_HINT_RESOURCE_TYPE) + ":MaterialPreset"), "set_material_presets", "get_material_presets");
	ClassDB::add_property("VoxelWorldData", PropertyInfo(Variant::ARRAY, "basics_presets", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::OBJECT) + "/" + String::num_int64(PROPERTY_HINT_RESOURCE_TYPE) + ":BasicsPreset"), "set_basics_presets", "get_basics_presets");
	ClassDB::add_property("VoxelWorldData", PropertyInfo(Variant::ARRAY, "mesh_presets", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::OBJECT) + "/" + String::num_int64(PROPERTY_HINT_RESOURCE_TYPE) + ":MeshPreset"), "set_mesh_presets", "get_mesh_presets");
	ClassDB::add_property("VoxelWorldData", PropertyInfo(Variant::ARRAY, "device_presets", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::OBJECT) + "/" + String::num_int64(PROPERTY_HINT_RESOURCE_TYPE) + ":DevicePreset"), "set_device_presets", "get_device_presets");

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
	this->chunk_size = value;
	world_size = chunk_count * chunk_size;
	voxels.resize(2 * world_size.x * world_size.y * world_size.z);
}

Vector3i VoxelWorldData::get_chunk_size() const {
	return chunk_size;
}

void VoxelWorldData::set_chunk_count(const Vector3i& value) {
	chunk_count = value;
	world_size = chunk_count * chunk_size;
	voxels.resize(2 * world_size.x * world_size.y * world_size.z);
}

Vector3i VoxelWorldData::get_chunk_count() const {
	return chunk_count;
}

Vector3i VoxelWorldData::get_world_size() const {
	return world_size;
}

void VoxelWorldData::set_voxels(const PackedByteArray& value)
{
	voxels = value;
}

PackedByteArray VoxelWorldData::get_voxels() const
{
	return voxels;
}

int VoxelWorldData::register_preset(const Ref<Preset>& value)
{
	String uuid = value->get_uuid();
	int index = -1;
	if (preset_map.get(uuid, nullptr).get_type() != Variant::NIL) {
		UtilityFunctions::printerr("This preset + " + value->get_name() + " + is already registered");
		return index;
	}
	String name = value->get_class();
	Array presets;
	if (name == StringName("MaterialPreset")) {
		presets = material_presets;
	}
	else if (name == StringName("BasicsPreset")) {
		presets = basics_presets;
	}
	else if (name == StringName("DevicePreset")) {
		presets = device_presets;
	}
	else {
		UtilityFunctions::printerr("This object + " + value->get_class() + " + is not a preset");
		return index;
	}
	for (index = 0; index < presets.size(); index++)
	{
		if (presets[index].get_type() == Variant::NIL) {
			preset_map[uuid] = index;
			presets[index] = value;
			return index;
		}
	}
	index = presets.size();
	presets.push_back(value);
	preset_map[uuid] = index;
	return index;
}

void VoxelWorldData::set_material_presets(const TypedArray <MaterialPreset>& value)
{
	material_presets = value;
}

TypedArray <MaterialPreset> VoxelWorldData::get_material_presets() {
	return material_presets;
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

void VoxelWorldData::set_voxel(const Vector3i& position, const Voxel& voxel)
{
	if (position.x < 0 || position.x >= world_size.x ||
		position.y < 0 || position.y >= world_size.y ||
		position.z < 0 || position.z >= world_size.z) {
		return;
	}
	int index = 2 * ((position.x * world_size.y * world_size.z) + (position.y * world_size.z) + position.z);
	voxels[index] = voxel >> 8;
	voxels[index + 1] = voxel;
}

Voxel VoxelWorldData::get_voxel(const Vector3i& position) const
{
	if (position.x < 0 || position.x >= world_size.x ||
		position.y < 0 || position.y >= world_size.y ||
		position.z < 0 || position.z >= world_size.z) {
		return 0;
	}
	int index = 2 * ((position.x * world_size.y * world_size.z) + (position.y * world_size.z) + position.z);
	return (voxels[index] << 8) | (voxels[index + 1]);
}

Vector3i VoxelWorldData::get_voxel_direction(const Vector3& direction, const Vector3i& rotation)
{
	Vector3 result = direction;
	result = result.rotated(Vector3(1, 0, 0), UtilityFunctions::deg_to_rad(rotation.x));
	result = result.rotated(Vector3(0, 1, 0), UtilityFunctions::deg_to_rad(rotation.y));
	result = result.rotated(Vector3(0, 0, 1), UtilityFunctions::deg_to_rad(rotation.z));
	return Vector3i(result);
}

//PackedByteArray VoxelWorldData::save()
//{
//	StreamPeerBuffer buffer;
//
//	buffer.put_var(chunk_size);
//	buffer.put_var(chunk_count);
//	buffer.put_var(voxels);
//	return buffer.get_data_array();
//}
//
//void VoxelWorldData::load(PackedByteArray value)
//{
//	StreamPeerBuffer buffer;
//	buffer.set_data_array(value);
//	chunk_size = buffer.get_var();
//	chunk_count = buffer.get_var();
//	voxels = buffer.get_var();
//}

int VoxelWorldData::get_voxel_type(const Voxel& voxel)
{
	return (voxel >> 6) & 0b00000011;
}

int VoxelWorldData::get_voxel_id(const Voxel& voxel)
{
	return voxel >> 8;
}

int VoxelWorldData::get_voxel_flag(const Voxel& voxel)
{
	return voxel & 0b00111111;
}

Vector3i VoxelWorldData::flag_to_rotation(const int& flag)
{
	return Vector3i((flag & 0b00110000) >> 4, (flag & 0b00001100) >> 2, (flag & 0b00000011));
}

Voxel VoxelWorldData::empty_voxel()
{
	return 0;
}

Voxel VoxelWorldData::basics_voxel(const int& id, const Vector3i& rotation)
{
	return (id << 8) | (BASICS << 6) | (rotation.x << 4) | (rotation.y << 2) | (rotation.z);
}

Voxel VoxelWorldData::mesh_voxel(const int& id, const Vector3i& rotation)
{
	return (id << 8) | (MESH << 6) | (rotation.x << 4) | (rotation.y << 2) | (rotation.z);
}

Voxel VoxelWorldData::device_voxel(const int& id)
{
	return (id << 8) | (DEVICE << 6);
}
