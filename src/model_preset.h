#ifndef MODEL_PRESET_H
#define MODEL_PRESET_H

#include "mesh_preset.h"

class ModelPreset : public Preset
{
	GDCLASS(ModelPreset, Preset);
protected:
	static void _bind_methods();
private:
	bool use_mask;
	TypedArray<MeshPreset> mesh_presets;
public:
	ModelPreset();
	~ModelPreset();

	void set_use_mask(const bool& value);
	bool is_use_mask() const;

	void set_mesh_preset(const TypedArray<MeshPreset>& value);
	TypedArray<MeshPreset> get_mesh_preset() const;
};

#endif // !MODEL_PRESET_H
