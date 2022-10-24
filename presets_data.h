#ifndef PRESETS_DATA_H
#define PRESETS_DATA_H

#include "basics_preset.h"
#include "mesh_preset.h"
#include "device_preset.h"
#include "custom_material.h"

class PresetsData : public Resource
{
	GDCLASS(PresetsData, Resource);
private:
	TypedArray<CustomMaterial> custom_materials;
	TypedArray<BasicsPreset> basics_presets;
	TypedArray<MeshPreset> mesh_presets;
	TypedArray<DevicePreset> device_presets;
protected:
	static void _bind_methods();
public:
	void set_custom_materials(const TypedArray <CustomMaterial>& value);
	TypedArray <CustomMaterial> get_custom_materials();

	void set_basics_presets(const TypedArray <BasicsPreset>& value);
	TypedArray <BasicsPreset> get_basics_presets();

	void set_mesh_presets(const TypedArray <MeshPreset>& value);
	TypedArray <MeshPreset> get_mesh_presets();

	void set_device_presets(const TypedArray <DevicePreset>& value);
	TypedArray <DevicePreset> get_device_presets();
};


#endif // !PRESETS_DATA_H