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
};


#endif // !PRESETS_DATA_H