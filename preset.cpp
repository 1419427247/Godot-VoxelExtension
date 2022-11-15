#include "preset.h"
#include "voxel_container.h"

void Preset::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_name", "value"), &Preset::set_name);
	ClassDB::bind_method(D_METHOD("get_name"), &Preset::get_name);

	ClassDB::bind_method(D_METHOD("set_script", "value"), &Preset::set_script);
	ClassDB::bind_method(D_METHOD("get_script"), &Preset::get_script);

	ClassDB::bind_method(D_METHOD("set_transparent", "value"), &Preset::set_transparent);
	ClassDB::bind_method(D_METHOD("get_transparent"), &Preset::get_transparent);

	ClassDB::bind_method(D_METHOD("set_filter", "value"), &Preset::set_filter);
	ClassDB::bind_method(D_METHOD("get_filter"), &Preset::get_filter);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "transparent"), "set_transparent", "get_transparent");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "filter",PROPERTY_HINT_LAYERS_3D_RENDER), "set_filter", "get_filter");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "script", PROPERTY_HINT_RESOURCE_TYPE, "Script"), "set_script", "get_script");
}

Preset::Preset()
{
	transparent = 0;
	filter = 0b0;
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

void Preset::set_transparent(const int& value)
{
	transparent = value;
}

int Preset::get_transparent() const
{
	return transparent;
}

void Preset::set_filter(const int& value)
{
	filter = value;
}

int Preset::get_filter() const
{
	return filter;
}

void Preset::set_script(const Ref<Script>& value)
{
	script = value;
}

Ref<Script> Preset::get_script() const
{
	return script;
}

void Preset::_on_voxel_new(VoxelContainer* voxel_container, const Voxel& voxel, const Vector3i& position)
{
}

void Preset::_on_voxel_delete(VoxelContainer* voxel_container, const Voxel& voxel, const Vector3i& position)
{
}


Vector3 Preset::rotate_vertex(const Vector3& vertex, const Vector3i& rotation)
{
	Vector3 result = vertex;
	result = result.rotated(Vector3(0, 1, 0), UtilityFunctions::deg_to_rad(rotation.y));
	result = result.rotated(Vector3(1, 0, 0), UtilityFunctions::deg_to_rad(rotation.x));
	result = result.rotated(Vector3(0, 0, 1), UtilityFunctions::deg_to_rad(rotation.z));
	return result;
}

Vector3 Preset::get_triangle_normal(const Vector3& a, const Vector3& b, const Vector3& c)
{
	return (c - a).cross(b - a);
}
