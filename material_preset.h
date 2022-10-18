#ifndef MATERIAL_PRESET_H
#define MATERIAL_PRESET_H
#include "preset.h"

class MaterialPreset : public Preset
{
	GDCLASS(MaterialPreset, Preset);
private:
	Ref<ShaderMaterial> shader_material;
protected:
	static void _bind_methods();
public:
	MaterialPreset();
	~MaterialPreset();
	
	void set_shader_material(const Ref<ShaderMaterial>& value);
	Ref<ShaderMaterial> get_shader_material() const;

	Array get_shader_parameter_list() const;
	void set_shader_parameter(const String& key, const Variant& value);

	static Ref<MaterialPreset> instantiate(const String& uuid,const String& name,const Ref<ShaderMaterial>& shader_material,Dictionary parameter);
};

#endif // !MATERIAL_PRESET_H
