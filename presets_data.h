#ifndef PRESETS_DATA_H
#define PRESETS_DATA_H

#include "basics_preset.h"
#include "model_preset.h"
#include "device_preset.h"
#include "device.h"

class PresetsData : public Resource
{
	GDCLASS(PresetsData, Resource);
private:
	TypedArray<Material> materials;
	TypedArray<BasicsPreset> basics_presets;
	TypedArray<ModelPreset> model_presets;
	TypedArray<DevicePreset> device_presets;
protected:
	static void _bind_methods();
public:
	void set_materials(const TypedArray <Material>& value);
	TypedArray <Material> get_materials() const;

	void set_basics_presets(const TypedArray <BasicsPreset>& value);
	TypedArray <BasicsPreset> get_basics_presets() const;

	void set_model_presets(const TypedArray <ModelPreset>& value);
	TypedArray <ModelPreset> get_model_presets() const;

	void set_device_presets(const TypedArray <DevicePreset>& value);
	TypedArray <DevicePreset> get_device_presets() const;
};


#endif // !PRESETS_DATA_H