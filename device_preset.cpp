#include "device_preset.h"

void DevicePreset::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_packed_scene", "value"), &DevicePreset::set_packed_scene);
    ClassDB::bind_method(D_METHOD("get_packed_scene"), &DevicePreset::get_packed_scene);

    ClassDB::bind_static_method("DevicePreset", D_METHOD("instantiate", "uuid", "name", "packed_scene"), &DevicePreset::instantiate);

    ClassDB::add_property("DevicePreset", PropertyInfo(Variant::OBJECT, "packed_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_packed_scene", "get_packed_scene");
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

Ref<DevicePreset> DevicePreset::instantiate(const String& uuid, const String& name, const Ref<PackedScene>& packed_scene)
{
    Ref<DevicePreset> device_preset;
    device_preset.instantiate();
    device_preset->packed_scene = packed_scene;
    return device_preset;
}
