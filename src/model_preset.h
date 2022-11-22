#ifndef MODEL_PRESET_H
#define MODEL_PRESET_H

#include "model_mesh.h"

class ModelPreset : public Preset
{
	GDCLASS(ModelPreset, Preset);
protected:
	static void _bind_methods();
private:
	bool use_mask;
	Array model_meshs;
public:
	ModelPreset();
	~ModelPreset();

	void set_use_mask(const bool& value);
	bool is_use_mask() const;

	void set_model_meshs(const Array& value);
	Array get_model_meshs() const;
};

#endif // !MODEL_PRESET_H
