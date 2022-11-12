#include "presets_data.h"

void PresetsData::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_materials"), &PresetsData::set_materials);
	ClassDB::bind_method(D_METHOD("get_materials"), &PresetsData::get_materials);

	ClassDB::bind_method(D_METHOD("set_basics_presets"), &PresetsData::set_basics_presets);
	ClassDB::bind_method(D_METHOD("get_basics_presets"), &PresetsData::get_basics_presets);

	ClassDB::bind_method(D_METHOD("set_mesh_presets"), &PresetsData::set_mesh_presets);
	ClassDB::bind_method(D_METHOD("get_mesh_presets"), &PresetsData::get_mesh_presets);

	ClassDB::bind_method(D_METHOD("set_device_presets"), &PresetsData::set_device_presets);
	ClassDB::bind_method(D_METHOD("get_device_presets"), &PresetsData::get_device_presets);

	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "materials", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::OBJECT) + "/" + String::num_int64(PROPERTY_HINT_RESOURCE_TYPE) + ":Material"), "set_materials", "get_materials");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "basics_presets", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::OBJECT) + "/" + String::num_int64(PROPERTY_HINT_RESOURCE_TYPE) + ":BasicsPreset"), "set_basics_presets", "get_basics_presets");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "mesh_presets", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::OBJECT) + "/" + String::num_int64(PROPERTY_HINT_RESOURCE_TYPE) + ":MeshPreset"), "set_mesh_presets", "get_mesh_presets");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "device_presets", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::OBJECT) + "/" + String::num_int64(PROPERTY_HINT_RESOURCE_TYPE) + ":DevicePreset"), "set_device_presets", "get_device_presets");

}

void PresetsData::set_materials(const TypedArray <Material>& value)
{
	materials = value;
}

TypedArray <Material> PresetsData::get_materials()const
{
	return materials;
}

void PresetsData::set_basics_presets(const TypedArray <BasicsPreset>& value)
{
	basics_presets = value;
}

TypedArray <BasicsPreset> PresetsData::get_basics_presets()const
{
	return basics_presets;
}

void PresetsData::set_mesh_presets(const TypedArray <MeshPreset>& value)
{
	mesh_presets = value;
}

TypedArray <MeshPreset> PresetsData::get_mesh_presets()const
{
	return mesh_presets;
}

void PresetsData::set_device_presets(const TypedArray <DevicePreset>& value)
{
	device_presets = value;
}

TypedArray <DevicePreset> PresetsData::get_device_presets() const
{
	return device_presets;
}
