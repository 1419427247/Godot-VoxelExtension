#include "device_preset.h"


void DevicePreset::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_packed_scene", "value"), &DevicePreset::set_packed_scene);
    ClassDB::bind_method(D_METHOD("get_packed_scene"), &DevicePreset::get_packed_scene);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "packed_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_packed_scene", "get_packed_scene");
}

DevicePreset::DevicePreset()
{
}

DevicePreset::~DevicePreset()
{
}

void DevicePreset::set_packed_scene(const Ref<PackedScene>& packed_scene)
{
    this->packed_scene = packed_scene;
}

Ref<PackedScene> DevicePreset::get_packed_scene() const
{
    return packed_scene;
}