#include "device.h"

#include "device_preset.h"
#include "voxel_block_data.h"

void Device::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_key"), &Device::set_key);
	ClassDB::bind_method(D_METHOD("get_key"), &Device::get_key);

	ClassDB::bind_method(D_METHOD("set_voxel_block_data"), &Device::set_voxel_block_data);
	ClassDB::bind_method(D_METHOD("get_voxel_block_data"), &Device::get_voxel_block_data);

	ClassDB::bind_method(D_METHOD("get_device_preset"), &Device::get_device_preset);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "key"), "set_key", "get_key");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "voxel_block_data", PROPERTY_HINT_RESOURCE_TYPE, "PresetsData"), "set_voxel_block_data", "get_voxel_block_data");
}

Device::Device()
{
	
}

Device::~Device()
{

}

void Device::set_key(const Vector3i& value) {
	key = value;
}

Vector3i Device::get_key() const {
	return key;
}

void Device::set_voxel_block_data(const Ref<VoxelBlockData>& value) {
	voxel_block_data = value;
}

Ref<VoxelBlockData> Device::get_voxel_block_data() const {
	return voxel_block_data;
}

void Device::set_device_preset(const Ref<DevicePreset>& value)
{
	device_preset = value;
}

Ref<DevicePreset> Device::get_device_preset()
{
	return device_preset;
}