#include "voxel_world.h"

#include <godot_cpp/classes/editor_plugin.hpp>
void VoxelWorld::_on_timer_timeout()
{
	emit_signal("update");
}

void VoxelWorld::_notification(int p_what) {
	if (p_what == NOTIFICATION_ENTER_TREE)
	{
		add_child(timer);
	}
	if (p_what == NOTIFICATION_EXIT_TREE) {
		remove_child(timer);
	}
}

void VoxelWorld::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_voxel_world_data", "value"), &VoxelWorld::set_voxel_world_data);
	ClassDB::bind_method(D_METHOD("get_voxel_world_data"), &VoxelWorld::get_voxel_world_data);

	ClassDB::bind_method(D_METHOD("set_isolated", "value"), &VoxelWorld::set_isolated);
	ClassDB::bind_method(D_METHOD("get_isolated"), &VoxelWorld::get_isolated);

	ClassDB::bind_method(D_METHOD("set_step", "value"), &VoxelWorld::set_step);
	ClassDB::bind_method(D_METHOD("get_step"), &VoxelWorld::get_step);

	ClassDB::bind_method(D_METHOD("_on_timer_timeout"), &VoxelWorld::_on_timer_timeout);

	ClassDB::add_property("VoxelWorld", PropertyInfo(Variant::OBJECT, "voxel_world_data",PROPERTY_HINT_RESOURCE_TYPE,"VoxelWorldData"), "set_voxel_world_data", "get_voxel_world_data");
	ClassDB::add_property("VoxelWorld", PropertyInfo(Variant::BOOL, "isolated"), "set_isolated", "get_isolated");
	ClassDB::add_property("VoxelWorld", PropertyInfo(Variant::FLOAT, "step"), "set_step", "get_step");

	ADD_SIGNAL(MethodInfo("update"));
}

VoxelWorld::VoxelWorld()
{
	this->isolated = false;
	this->timer = memnew(Timer);
	this->timer->set_wait_time(0.1);
	this->timer->set_autostart(true);
	this->timer->connect("timeout", Callable(this, "_on_timer_timeout"));
}

VoxelWorld::~VoxelWorld()
{
}

void VoxelWorld::set_voxel_world_data(const Ref<VoxelWorldData>& value)
{
	voxel_world_data = value;
}

Ref<VoxelWorldData> VoxelWorld::get_voxel_world_data() const
{
	return voxel_world_data;
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
