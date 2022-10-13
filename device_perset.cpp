#include "device_perset.h"

void DevicePerset::_bind_methods()
{
}

DevicePerset::DevicePerset()
{
}

DevicePerset::~DevicePerset()
{
}

void DevicePerset::set_packed_scene(const Ref<PackedScene>& packed_scene)
{
    this->packed_scene = packed_scene;
}

Ref<PackedScene> DevicePerset::get_packed_scene() const
{
    return packed_scene;
}

Ref<DevicePerset> DevicePerset::instantiate(const String& uuid, const String& name, const Ref<PackedScene>& packed_scene)
{
    Ref<DevicePerset> device_perset;
    device_perset.instantiate();
    device_perset->packed_scene = packed_scene;
    return device_perset;
}
