#ifndef DEVICE_H
#define DEVICE_H

#include "voxel_container_data.h"

class VoxelBlock;
class Device : public Node3D
{
	GDCLASS(Device, Node3D);
private:
	Vector3i key;
	Ref<DevicePreset> device_preset;
protected:
	static void _bind_methods();
public:
	Device();
	~Device();

	void set_device_preset(const Ref<DevicePreset>& value);
	Ref<DevicePreset> get_device_preset();
};


#endif // !DEVICE_H