#include "voxel_world.h"



VoxelWorld::VoxelWorld()
{
	this->chunk_size = 8;
	this->chunk_count = Vector3i(1, 1, 1);
}

VoxelWorld::~VoxelWorld()
{

}

int VoxelWorld::get_chunk_size() {
	return chunk_size;
}
Vector3i VoxelWorld::get_chunk_count() {
	return chunk_count;
}
Vector3i VoxelWorld::get_world_size() {
	return world_size;
}
void VoxelWorld::set_chunk_size(int value) {
	this->chunk_size = value;
}
void VoxelWorld::set_chunk_count(Vector3i value) {
	this->chunk_count = value;
}


Array VoxelWorld::get_material_persets() {
	return material_persets;
}

Array VoxelWorld::get_basics_persets() {
	return basics_persets;
}

Array VoxelWorld::get_device_persets() {
	return device_persets;
}
void VoxelWorld::set_material_persets(Array value) {
	material_persets = value;
}

void VoxelWorld::set_basics_persets(Array value) {
	basics_persets = value;
}

void VoxelWorld::set_device_persets(Array value) {
	device_persets = value;
}

void VoxelWorld::set_voxel(const int type, const int id, const Vector3i& position, const Vector3i& rotation)
{
	if (position.x < 0 || position.x >= world_size.x ||
		position.y < 0 || position.y >= world_size.y ||
		position.z < 0 || position.z >= world_size.z) {
		return;
	}
	int index = 2 * ((position.x * world_size.y * world_size.z) + (position.y * world_size.z) + position.z);
	voxels[index] = id;
	voxels[index + 1] = (type << 6) | ((rotation.x / 90) << 4) | ((rotation.y / 90) << 2) | ((rotation.z / 90));
}

int VoxelWorld::get_voxel_type(const Vector3i& position) const
{
	if (position.x < 0 || position.x >= world_size.x ||
		position.y < 0 || position.y >= world_size.y ||
		position.z < 0 || position.z >= world_size.z) {
		return EMPTY;
	}
	int index = 2 * ((position.x * world_size.y * world_size.z) + (position.y * world_size.z) + position.z);
	return voxels[index + 1] >> 6;
}

int VoxelWorld::get_voxel_id(const Vector3i& position) const
{
	int index = 2 * ((position.x * world_size.y * world_size.z) + (position.y * world_size.z) + position.z);
	return voxels[index];
}

Vector3i VoxelWorld::get_voxel_rotation(const Vector3i& position) const
{
	int index = 2 * ((position.x * world_size.y * world_size.z) + (position.y * world_size.z) + position.z);
	return 90 * Vector3i((voxels[index + 1] >> 4) & 0b00000011, (voxels[index + 1] >> 2) & 0b00000011, (voxels[index + 1]) & 0b00000011);
}

Vector3i VoxelWorld::get_voxel_position_by_point(const Vector3& position, const Vector3& normal) const
{
	Vector3 _position = position;
	if (normal.y == 1) {
		_position.y -= 0.05;
	}
	else if (normal.y == -1) {
		_position.y += 0.05;
	}
	else if (normal.x == 1) {
		_position.x -= 0.05;
	}
	else if (normal.x == -1) {
		_position.x += 0.05;
	}
	else if (normal.z == 1) {
		_position.z -= 0.05;
	}
	else if (normal.z == -1) {
		_position.z += 0.05;
	}
	return Vector3i(_position.round());
}

Vector3i VoxelWorld::get_voxel_relative_position(const Vector3i& position, const Vector3i& direction, const Vector3i& rotation) const
{
	static Vector3i memorandum[] = {
		Vector3i(-1, -1, -1), Vector3i(0, -1, -1),
		Vector3i(1, -1, -1), Vector3i(-1, 0, -1),
		Vector3i(0, 0, -1), Vector3i(1, 0, -1),
		Vector3i(-1, 1, -1), Vector3i(0, 1, -1),
		Vector3i(1, 1, -1), Vector3i(-1, -1, 0),
		Vector3i(0, -1, 0), Vector3i(1, -1, 0),
		Vector3i(-1, 0, 0), Vector3i(0, 0, 0),
		Vector3i(1, 0, 0), Vector3i(-1, 1, 0),
		Vector3i(0, 1, 0), Vector3i(1, 1, 0),
		Vector3i(-1, -1, 1), Vector3i(0, -1, 1),
		Vector3i(1, -1, 1), Vector3i(-1, 0, 1),
		Vector3i(0, 0, 1), Vector3i(1, 0, 1),
		Vector3i(-1, 1, 1), Vector3i(0, 1, 1),
		Vector3i(1, 1, 1),
	};
	return position + memorandum[(direction.x + 1) + (direction.y + 1) * 3 + (direction.z + 1) * 9];
}




void VoxelWorld::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_chunk_size"), &VoxelWorld::get_chunk_size);
	ClassDB::bind_method(D_METHOD("get_chunk_count"), &VoxelWorld::get_chunk_count);
	ClassDB::bind_method(D_METHOD("get_world_size"), &VoxelWorld::get_world_size);

	ClassDB::bind_method(D_METHOD("set_chunk_size", "value"), &VoxelWorld::set_chunk_size);
	ClassDB::bind_method(D_METHOD("set_chunk_count", "value"), &VoxelWorld::set_chunk_count);

	ClassDB::bind_method(D_METHOD("set_material_persets", "value"), &VoxelWorld::set_material_persets);
	ClassDB::bind_method(D_METHOD("set_basics_persets", "value"), &VoxelWorld::set_basics_persets);
	ClassDB::bind_method(D_METHOD("set_device_persets", "value"), &VoxelWorld::set_device_persets);

	ClassDB::bind_method(D_METHOD("get_material_persets"), &VoxelWorld::get_material_persets);
	ClassDB::bind_method(D_METHOD("get_basics_persets"), &VoxelWorld::get_basics_persets);
	ClassDB::bind_method(D_METHOD("get_device_persets"), &VoxelWorld::get_device_persets);

	ClassDB::bind_method(D_METHOD("set_voxel", "type", "id", "position", "rotation"), &VoxelWorld::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel_type", "position"), &VoxelWorld::get_voxel_type);
	ClassDB::bind_method(D_METHOD("get_voxel_id", "position"), &VoxelWorld::get_voxel_id);
	ClassDB::bind_method(D_METHOD("get_voxel_rotation", "position"), &VoxelWorld::get_voxel_rotation);
	ClassDB::bind_method(D_METHOD("get_voxel_position_by_point", "position", "normal"), &VoxelWorld::get_voxel_position_by_point);
	ClassDB::bind_method(D_METHOD("get_voxel_relative_position", "position", "direction", "rotation"), &VoxelWorld::get_voxel_relative_position);

	ClassDB::add_property("VoxelWorld", PropertyInfo(Variant::INT, "chunk_size"), "set_chunk_size", "get_chunk_size");
	ClassDB::add_property("VoxelWorld", PropertyInfo(Variant::VECTOR3I, "chunk_count"), "set_chunk_count", "get_chunk_count");
	
	ClassDB::add_property("VoxelWorld", PropertyInfo(Variant::ARRAY, "material_persets"), "set_material_persets", "get_material_persets");
	ClassDB::add_property("VoxelWorld", PropertyInfo(Variant::ARRAY, "basics_persets"), "set_basics_persets", "get_basics_persets");
	ClassDB::add_property("VoxelWorld", PropertyInfo(Variant::ARRAY, "device_persets"), "set_device_persets", "get_device_persets");
}

void add(Array& arr) {
	
	//PackedVector3Array pack = arr[0];
	//pack.push_back(Vector3i(1, 2, 3));
}

void VoxelWorld::_notification(int p_what) {
	if (p_what == NOTIFICATION_ENTER_TREE)
	{
		Array kkk;
		kkk.resize(1);
		kkk[0] = PackedVector3Array();
		((PackedVector3Array*)(&kkk[0]))->push_back(Vector3i(1, 2, 3));
		UtilityFunctions::print(kkk);
		((PackedVector3Array)(kkk[0])).push_back(Vector3i(1, 2, 3));
		UtilityFunctions::print(kkk);
		PackedVector3Array packed_vector3_array = kkk[0];
		packed_vector3_array.push_back(Vector3i(1, 2, 3));
		UtilityFunctions::print(kkk);

		this->world_size = chunk_count * chunk_size;
		this->voxels.resize(2 * world_size.x * world_size.y * world_size.z);
	}
}
