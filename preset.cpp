#include "preset.h"
#include "voxel_room.h"

void Preset::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_name", "value"), &Preset::set_name);
	ClassDB::bind_method(D_METHOD("get_name"), &Preset::get_name);

	ClassDB::bind_method(D_METHOD("set_script", "value"), &Preset::set_script);
	ClassDB::bind_method(D_METHOD("get_script"), &Preset::get_script);

	ClassDB::bind_method(D_METHOD("set_transparent", "value"), &Preset::set_transparent);
	ClassDB::bind_method(D_METHOD("get_transparent"), &Preset::get_transparent);

	ClassDB::bind_method(D_METHOD("set_collider", "value"), &Preset::set_collider);
	ClassDB::bind_method(D_METHOD("get_collider"), &Preset::get_collider);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "transparent"), "set_transparent", "get_transparent");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "collider"), "set_collider", "get_collider");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "script", PROPERTY_HINT_RESOURCE_TYPE, "Script"), "set_script", "get_script");
}

Preset::Preset()
{
	transparent = false;
	collider = true;
}

Preset::~Preset()
{
}

void Preset::set_name(const String& value)
{
	name = value;
}

String Preset::get_name() const
{
	return name;
}

void Preset::set_transparent(const bool& value)
{
	transparent = value;
}

bool Preset::get_transparent() const
{
	return transparent;
}

void Preset::set_collider(const bool& value)
{
	collider = value;
}

bool Preset::get_collider() const
{
	return collider;
}

void Preset::set_script(const Ref<Script>& value)
{
	script = value;
}

Ref<Script> Preset::get_script() const
{
	return script;
}

void Preset::_on_voxel_new(VoxelRoom* voxel_room, const Voxel& voxel, const Vector3i& position)
{
}

void Preset::_on_voxel_delete(VoxelRoom* voxel_room, const Voxel& voxel, const Vector3i& position)
{
}