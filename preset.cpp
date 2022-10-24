#include "preset.h"
#include "voxel_world.h"

void Preset::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_uuid"), &Preset::set_uuid);
	ClassDB::bind_method(D_METHOD("get_uuid"), &Preset::get_uuid);

	ClassDB::bind_method(D_METHOD("set_name", "value"), &Preset::set_name);
	ClassDB::bind_method(D_METHOD("get_name"), &Preset::get_name);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "uuid"), "set_uuid", "get_uuid");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "script", PROPERTY_HINT_RESOURCE_TYPE, "Script"), "set_script", "get_script");
}

Preset::Preset()
{
}

Preset::~Preset()
{
}

void Preset::set_uuid(const String& value)
{
	uuid = value;
}

String Preset::get_uuid() const
{
	return uuid;
}

void Preset::set_name(const String& value)
{
	name = value;
}

String Preset::get_name() const
{
	return name;
}

void Preset::set_script(const Ref<Script>& value)
{
	script = value;
}

Ref<Script> Preset::get_script() const
{
	return script;
}

void Preset::_on_voxel_new(VoxelWorld* voxel_world, const Voxel& voxel, const Vector3i& position)
{
}

void Preset::_on_voxel_delete(VoxelWorld* voxel_world, const Voxel& voxel, const Vector3i& position)
{
}