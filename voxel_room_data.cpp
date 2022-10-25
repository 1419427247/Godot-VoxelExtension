#include "voxel_room_data.h"

void VoxelRoomData::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_chunk_size", "value"), &VoxelRoomData::set_chunk_size);
	ClassDB::bind_method(D_METHOD("get_chunk_size"), &VoxelRoomData::get_chunk_size);

	ClassDB::bind_method(D_METHOD("set_chunk_count", "value"), &VoxelRoomData::set_chunk_count);
	ClassDB::bind_method(D_METHOD("get_chunk_count"), &VoxelRoomData::get_chunk_count);

	ClassDB::bind_method(D_METHOD("get_room_size"), &VoxelRoomData::get_room_size);

	ClassDB::bind_method(D_METHOD("set_voxels", "value"), &VoxelRoomData::set_voxels);
	ClassDB::bind_method(D_METHOD("get_voxels"), &VoxelRoomData::get_voxels);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "chunk_size"), "set_chunk_size", "get_chunk_size");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "chunk_count"), "set_chunk_count", "get_chunk_count");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_BYTE_ARRAY, "voxels"), "set_voxels", "get_voxels");

	BIND_ENUM_CONSTANT(EMPTY);
	BIND_ENUM_CONSTANT(BASICS);
	BIND_ENUM_CONSTANT(MESH);
	BIND_ENUM_CONSTANT(DEVICE);
}

VoxelRoomData::VoxelRoomData()
{
	set_chunk_size(Vector3i(8, 8, 8));
	set_chunk_count(Vector3i(1, 1, 1));
}

VoxelRoomData::~VoxelRoomData()
{
}


void VoxelRoomData::set_chunk_size(const Vector3i& value) {
	if (value.x <= 0 || value.y <= 0 || value.z <= 0)
	{
		UtilityFunctions::printerr("Chunk size is an invalid value");
		return;
	}
	this->chunk_size = value;
	room_size = chunk_count * chunk_size;
	voxels.resize(room_size.x * room_size.y * room_size.z);
}

Vector3i VoxelRoomData::get_chunk_size() const {
	return chunk_size;
}

void VoxelRoomData::set_chunk_count(const Vector3i& value) {
	if (value.x <= 0 || value.y <= 0 || value.z <= 0)
	{
		UtilityFunctions::printerr("Chunk count is an invalid value");
		return;
	}
	chunk_count = value;
	room_size = chunk_count * chunk_size;
	voxels.resize(room_size.x * room_size.y * room_size.z);
}

Vector3i VoxelRoomData::get_chunk_count() const {
	return chunk_count;
}

Vector3i VoxelRoomData::get_room_size() const {
	return room_size;
}

void VoxelRoomData::set_voxels(const PackedByteArray& value)
{
	//Ref<StreamPeerBuffer> buffer;
	//buffer.instantiate();
	//buffer->put_var(room_size);
	//voxels = value.decompress(4096).to_int32_array();
	return;
}

PackedByteArray VoxelRoomData::get_voxels() const
{
	return voxels.to_byte_array().compress();
}

//int VoxelRoomData::register_preset(const Ref<Preset>& value)
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


