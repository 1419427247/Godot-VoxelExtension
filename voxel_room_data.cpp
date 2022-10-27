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

	ClassDB::bind_method(D_METHOD("copy", "from", "to"), &VoxelRoomData::copy);
	ClassDB::bind_method(D_METHOD("paste", "voxel_room_data", "position", "direction"), &VoxelRoomData::paste);

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
	ERR_FAIL_COND_MSG(value.x <= 0 || value.y <= 0 || value.z <= 0, "Chunk size is an invalid value");

	this->chunk_size = value;
	room_size = chunk_count * chunk_size;

	voxels.resize(room_size.x * room_size.y * room_size.z);
	voxels.fill(0);
}

Vector3i VoxelRoomData::get_chunk_size() const {
	return chunk_size;
}

void VoxelRoomData::set_chunk_count(const Vector3i& value) {
	ERR_FAIL_COND_MSG(value.x <= 0 || value.y <= 0 || value.z <= 0, "Chunk count is an invalid value");

	chunk_count = value;
	room_size = chunk_count * chunk_size;

	voxels.resize(room_size.x * room_size.y * room_size.z);
	voxels.fill(0);
}

Vector3i VoxelRoomData::get_chunk_count() const {
	return chunk_count;
}

Vector3i VoxelRoomData::get_room_size() const {
	return room_size;
}

void VoxelRoomData::set_voxels(const PackedByteArray& value)
{
	voxels = value.decompress(4096).to_int32_array();
}

PackedByteArray VoxelRoomData::get_voxels() const
{
	return voxels.to_byte_array().compress();
}

void VoxelRoomData::set_voxel(const Vector3i& position, const Voxel& value)
{
	if (position.x < 0 || position.x >= room_size.x ||
		position.y < 0 || position.y >= room_size.y ||
		position.z < 0 || position.z >= room_size.z) {
		return;
	}
	int index = ((position.x * room_size.y * room_size.z) + (position.y * room_size.z) + position.z);
	voxels[index] = value;
}

Voxel VoxelRoomData::get_voxel(const Vector3i& position) const
{
	if (position.x < 0 || position.x >= room_size.x ||
		position.y < 0 || position.y >= room_size.y ||
		position.z < 0 || position.z >= room_size.z) {
		return EMPTY_VOXEL;
	}
	int index = ((position.x * room_size.y * room_size.z) + (position.y * room_size.z) + position.z);
	return voxels[index];
}

Ref<VoxelRoomData> VoxelRoomData::copy(const Vector3i& from, const Vector3i& to)
{
	Ref<VoxelRoomData> replica_voxel_data;
	replica_voxel_data.instantiate();

	replica_voxel_data->set_chunk_count(Vector3i(1, 1, 1));
	Vector3i chunk_size = Vector3i(abs(from.x - to.x) + 1, abs(from.y - to.y) + 1, abs(from.z - to.z) + 1);
	replica_voxel_data->set_chunk_size(chunk_size);
	int step_x = from.x > to.x ? -1 : 1;
	int step_y = from.y > to.y ? -1 : 1;
	int step_z = from.z > to.z ? -1 : 1;
	for (int x = from.x; x != to.x + step_x; x += step_x)
	{
		for (int y = from.y; y != to.y + step_y; y += step_y)
		{
			for (int z = from.z; z != to.z + step_z; z += step_z)
			{
				Vector3i position = Vector3i(x, y, z);
				Vector3i replica_position = Vector3i(abs(x - from.x), abs(y - from.y), abs(z - from.z));
				replica_voxel_data->set_voxel(replica_position, get_voxel(position));
			}
		}
	}
	return replica_voxel_data;
}

void VoxelRoomData::paste(const Ref<VoxelRoomData>& voxel_room_data, const Vector3i& position, const Vector3i& direction)
{
	ERR_FAIL_COND_MSG((direction.x != 1 && direction.x == -1) || (direction.y != 1 && direction.y == -1) || (direction.z != 1 && direction.z == -1), "Invalid direction");
	for (int x = position.x; x != position.x + voxel_room_data->room_size.x * direction.x; x += direction.x)
	{
		for (int y = position.y; y != position.y + voxel_room_data->room_size.y * direction.y; y += direction.y)
		{
			for (int z = position.z; z != position.z + voxel_room_data->room_size.z * direction.z; z += direction.z)
			{
				Vector3i position = Vector3i(x, y, z);
				set_voxel(position, get_voxel(Vector3i(abs(x - position.x), abs(y - position.y), abs(z - position.z))));
			}
		}
	}
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