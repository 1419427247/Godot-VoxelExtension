#ifndef DEVICE_H
#define DEVICE_H

#include "device_preset.h"

class Device : public Node3D
{
	GDCLASS(Device, Node3D);
private:
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