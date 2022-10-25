#ifndef CUSTOM_MATERIAL_H
#define CUSTOM_MATERIAL_H

#include "preset.h"

class CustomMaterial : public Resource
{
	GDCLASS(CustomMaterial, Resource);
private:
	Ref<ShaderMaterial> shader_material;
protected:
	static void _bind_methods();
public:
	CustomMaterial();
	~CustomMaterial();
	
	void set_shader_material(const Ref<ShaderMaterial>& value);
	Ref<ShaderMaterial> get_shader_material() const;

	Array get_shader_parameter_list() const;
	void set_shader_parameter(const String& key, const Variant& value);

	static Ref<CustomMaterial> instantiate(const String& name,const Ref<ShaderMaterial>& shader_material,Dictionary parameter);
};

#endif // !CUSTOM_MATERIAL_H
