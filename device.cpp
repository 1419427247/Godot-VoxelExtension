#include "device.h"

void Device::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_device_preset"), &Device::get_device_preset);
}

Device::Device()
{
}

Device::~Device()
{
}

void Device::set_device_preset(const Ref<DevicePreset>& value)
{
	device_preset = value;
}

Ref<DevicePreset> Device::get_device_preset()
{
	return device_preset;
}
