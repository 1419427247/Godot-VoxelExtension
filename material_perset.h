#ifndef MATERIAL_PERSET_H
#define MATERIAL_PERSET_H
#include "perset.h"

class MaterialPerset : public Perset
{
	GDCLASS(MaterialPerset, Perset);
private:
	Ref<ShaderMaterial> shader_material;
protected:
	static void _bind_methods();
public:
	MaterialPerset();
	~MaterialPerset();
	
	void set_shader_material(const Ref<ShaderMaterial>& value);
	Ref<ShaderMaterial> get_shader_material() const;

	Array get_shader_parameter_list() const;
	void set_shader_parameter(const String& key, const Variant& value);

	static Ref<MaterialPerset> instantiate(const String& uuid,const String& name,const Ref<ShaderMaterial>& shader_material,Dictionary parameter);
};

#endif // !MATERIAL_PERSET_H
