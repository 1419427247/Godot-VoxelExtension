#include "voxel_world.h"

#include <godot_cpp/classes/editor_plugin.hpp>
void VoxelWorld::_on_timer_timeout()
{
	emit_signal("update");
}

void VoxelWorld::_notification(int p_what) {
	if (p_what == NOTIFICATION_ENTER_TREE)
	{
		set_chunk_count(chunk_count);
		add_child(timer);
	}
	if (p_what == NOTIFICATION_EXIT_TREE) {
		remove_child(timer);
	}
}

void VoxelWorld::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_chunk_size", "value"), &VoxelWorld::set_chunk_size);
	ClassDB::bind_method(D_METHOD("get_chunk_size"), &VoxelWorld::get_chunk_size);

	ClassDB::bind_method(D_METHOD("set_chunk_count", "value"), &VoxelWorld::set_chunk_count);
	ClassDB::bind_method(D_METHOD("get_chunk_count"), &VoxelWorld::get_chunk_count);

	ClassDB::bind_method(D_METHOD("get_world_size"), &VoxelWorld::get_world_size);

	ClassDB::bind_method(D_METHOD("set_isolated", "value"), &VoxelWorld::set_isolated);
	ClassDB::bind_method(D_METHOD("get_isolated"), &VoxelWorld::get_isolated);

	ClassDB::bind_method(D_METHOD("set_step", "value"), &VoxelWorld::set_step);
	ClassDB::bind_method(D_METHOD("get_step"), &VoxelWorld::get_step);

	ClassDB::bind_method(D_METHOD("register_perset"), &VoxelWorld::register_perset);
	ClassDB::bind_method(D_METHOD("get_material_persets"), &VoxelWorld::get_material_persets);
	ClassDB::bind_method(D_METHOD("get_basics_persets"), &VoxelWorld::get_basics_persets);
	ClassDB::bind_method(D_METHOD("get_mesh_persets"), &VoxelWorld::get_mesh_persets);
	ClassDB::bind_method(D_METHOD("get_device_persets"), &VoxelWorld::get_device_persets);

	ClassDB::bind_method(D_METHOD("set_voxel", "position", "voxel"), &VoxelWorld::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel", "position"), &VoxelWorld::get_voxel);

	ClassDB::bind_method(D_METHOD("get_voxel_direction", "direction", "rotation"), &VoxelWorld::get_voxel_direction);

	ClassDB::bind_method(D_METHOD("save"), &VoxelWorld::save);
	ClassDB::bind_method(D_METHOD("load"), &VoxelWorld::load);

	ClassDB::bind_static_method("VoxelWorld", D_METHOD("get_voxel_type", "voxel"), &VoxelWorld::get_voxel_type);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("get_voxel_id", "voxel"), &VoxelWorld::get_voxel_id);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("get_voxel_flag", "voxel"), &VoxelWorld::get_voxel_flag);
	
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("empty_voxel"), &VoxelWorld::empty_voxel);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("basics_voxel"), &VoxelWorld::basics_voxel);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("mesh_voxel"), &VoxelWorld::mesh_voxel);
	ClassDB::bind_static_method("VoxelWorld", D_METHOD("device_voxel"), &VoxelWorld::device_voxel);

	ClassDB::bind_method(D_METHOD("_on_timer_timeout"), &VoxelWorld::_on_timer_timeout);

	ClassDB::add_property("VoxelWorld", PropertyInfo(Variant::VECTOR3I, "chunk_size"), "set_chunk_size", "get_chunk_size");
	ClassDB::add_property("VoxelWorld", PropertyInfo(Variant::VECTOR3I, "chunk_count"), "set_chunk_count", "get_chunk_count");
	ClassDB::add_property("VoxelWorld", PropertyInfo(Variant::BOOL, "isolated"), "set_isolated", "get_isolated");
	ClassDB::add_property("VoxelWorld", PropertyInfo(Variant::FLOAT, "step"), "set_step", "get_step");

	ADD_SIGNAL(MethodInfo("update"));

	BIND_ENUM_CONSTANT(EMPTY);
	BIND_ENUM_CONSTANT(BASICS);
	BIND_ENUM_CONSTANT(MESH);
	BIND_ENUM_CONSTANT(DEVICE);
}

VoxelWorld::VoxelWorld()
{
	this->chunk_size = Vector3i(8,8,8);
	this->chunk_count = Vector3i(1, 1, 1);
	this->isolated = false;
	this->timer = memnew(Timer);
	this->timer->set_wait_time(0.1);
	this->timer->set_autostart(true);
	this->timer->connect("timeout", Callable(this, "_on_timer_timeout"));
}

VoxelWorld::~VoxelWorld()
{
}

void VoxelWorld::set_chunk_size(const Vector3i& value) {
	this->chunk_size = value;
	world_size = chunk_count * chunk_size;
	voxels.resize(2 * world_size.x * world_size.y * world_size.z);
}

Vector3i VoxelWorld::get_chunk_size() const {
	return chunk_size;
}

void VoxelWorld::set_chunk_count(const Vector3i& value) {
	chunk_count = value;
	world_size = chunk_count * chunk_size;
	voxels.resize(2 * world_size.x * world_size.y * world_size.z);
}

Vector3i VoxelWorld::get_chunk_count() const {
	return chunk_count;
}

Vector3i VoxelWorld::get_world_size() const {
	return world_size;
}

void VoxelWorld::set_isolated(const bool& value)
{
	isolated = value;
}

bool VoxelWorld::get_isolated() const
{
	return isolated;
}

void VoxelWorld::set_step(const double& value)
{
	timer->set_wait_time(value);
}

double VoxelWorld::get_step()
{
	return timer->get_wait_time();
}

int VoxelWorld::register_perset(const Ref<Perset>& value)
{
	String uuid = value->get_uuid();
	int index = -1;
	if (perset_map.get(uuid, nullptr).get_type() != Variant::NIL) {
		UtilityFunctions::printerr("This preset + " + value->get_name() + " + is already registered");
		return index;
	}
	String name = value->get_class();
	Array persets;
	if (name == StringName("MaterialPerset")) {
		persets = material_persets;
	}
	else if (name == StringName("BasicsPerset")) {
		persets = basics_persets;
	}
	else if (name == StringName("DevicePerset")) {
		persets = device_persets;
	}
	else {
		UtilityFunctions::printerr("This object + " + value->get_class() + " + is not a perset");
		return index;
	}
	for (index = 0; index < persets.size(); index++)
	{
		if (persets[index].get_type() == Variant::NIL) {
			perset_map[uuid] = index;
			persets[index] = value;
			return index;
		}
	}
	index = persets.size();
	persets.push_back(value);
	perset_map[uuid] = index;
	return index;
}

Array VoxelWorld::get_material_persets() {
	return material_persets;
}

Array VoxelWorld::get_basics_persets()
{
	return basics_persets;
}

Array VoxelWorld::get_mesh_persets()
{
	return mesh_persets;
}

Array VoxelWorld::get_device_persets() {
	return device_persets;
}

void VoxelWorld::set_voxel(const Vector3i& position, const Voxel& voxel)
{
	if (position.x < 0 || position.x >= world_size.x ||
		position.y < 0 || position.y >= world_size.y ||
		position.z < 0 || position.z >= world_size.z) {
		return;
	}
	int index = 2 * ((position.x * world_size.y * world_size.z) + (position.y * world_size.z) + position.z);
	voxels[index + 1] = voxel;
	voxels[index] = voxel << 8;
}

Voxel VoxelWorld::get_voxel(const Vector3i& position) const
{
	if (position.x < 0 || position.x >= world_size.x ||
		position.y < 0 || position.y >= world_size.y ||
		position.z < 0 || position.z >= world_size.z) {
		return 0;
	}
	int index = 2 * ((position.x * world_size.y * world_size.z) + (position.y * world_size.z) + position.z);
	return (voxels[index] << 8) | (voxels[index + 1]);
}

Vector3i VoxelWorld::get_voxel_direction(const Vector3& direction, const Vector3i& rotation) const
{
	Vector3 result = direction;
	result = result.rotated(Vector3(1, 0, 0), UtilityFunctions::deg_to_rad(rotation.x));
	result = result.rotated(Vector3(0, 1, 0), UtilityFunctions::deg_to_rad(rotation.y));
	result = result.rotated(Vector3(0, 0, 1), UtilityFunctions::deg_to_rad(rotation.z));
	return Vector3i(result);
}

PackedByteArray VoxelWorld::save()
{
	StreamPeerBuffer buffer;

	buffer.put_var(chunk_size);
	buffer.put_var(chunk_count);
	buffer.put_var(voxels);
	return buffer.get_data_array();
}

void VoxelWorld::load(PackedByteArray value)
{
	StreamPeerBuffer buffer;
	buffer.set_data_array(value);
	chunk_size = buffer.get_var();
	chunk_count = buffer.get_var();
	voxels = buffer.get_var();
}

int VoxelWorld::get_voxel_type(const Voxel& voxel)
{
	return (voxel >> 6) & 0b00000011;
}

int VoxelWorld::get_voxel_id(const Voxel& voxel)
{
	return voxel >> 8;
}

int VoxelWorld::get_voxel_flag(const Voxel& voxel)
{
	return voxel & 0b00111111;
}

Vector3i VoxelWorld::flag_to_rotation(const int& flag)
{
	return Vector3i((flag & 0b00110000) >> 4, (flag & 0b00001100) >> 2, (flag & 0b00000011));
}

Voxel VoxelWorld::empty_voxel()
{
	return 0;
}

Voxel VoxelWorld::basics_voxel(const int& id, const Vector3i& rotation)
{
	return (id << 8) | (BASICS << 6) | (rotation.x << 4) | (rotation.y << 2) | (rotation.z);
}

Voxel VoxelWorld::mesh_voxel(const int& id, const Vector3i& rotation)
{
	return (id << 8) | (MESH << 6) | (rotation.x << 4) | (rotation.y << 2) | (rotation.z);
}

Voxel VoxelWorld::device_voxel(const int& id)
{
	return (id << 8) | (DEVICE << 6);
}
