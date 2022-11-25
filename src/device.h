#ifndef DEVICE_H
#define DEVICE_H

#include "preset.h"

class VoxelBlockData;
class DevicePreset;

class Device : public Node3D
{
	GDCLASS(Device, Node3D);
private:
	Vector3i key;
	Ref<VoxelBlockData> voxel_block_data;
	Ref<DevicePreset> device_preset;
protected:
	static void _bind_methods();
public:
	Device();
	~Device();

	void set_key(const Vector3i& value);
	Vector3i get_key() const;

	void set_voxel_block_data(const Ref<VoxelBlockData>& value);
	Ref<VoxelBlockData> get_voxel_block_data() const;

	void set_device_preset(const Ref<DevicePreset>& value);
	Ref<DevicePreset> get_device_preset();
};


#endif // !DEVICE_H