#ifndef DEVICE_PRESET_H
#define DEVICE_PRESET_H

#include "preset.h"

class DevicePreset : public Preset
{
	GDCLASS(DevicePreset, Preset);
private:
	Ref<PackedScene> packed_scene;
protected:
	static void _bind_methods();
public:
	DevicePreset();
	~DevicePreset();

	void set_packed_scene(const Ref<PackedScene>& packed_scene);
	Ref<PackedScene> get_packed_scene() const;
};

#endif // !DEVICE_PRESET_H