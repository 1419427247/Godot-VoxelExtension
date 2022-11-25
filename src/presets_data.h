#ifndef PRESETS_DATA_H
#define PRESETS_DATA_H

#include "basics_preset.h"
#include "model_preset.h"
#include "device_preset.h"

class PresetsData : public Resource
{
	GDCLASS(PresetsData, Resource);
protected:
	static void _bind_methods();
public:
	List<Material> materials;
	List<BasicsPreset> basics_presets;
	List<ModelPreset> model_presets;
	List<DevicePreset> device_presets;
	
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