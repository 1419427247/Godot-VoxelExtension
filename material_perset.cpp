#include "material_perset.h"

void MaterialPerset::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_uuid"), &MaterialPerset::get_uuid);

	ClassDB::bind_method(D_METHOD("set_name", "value"), &MaterialPerset::set_name);
	ClassDB::bind_method(D_METHOD("get_name"), &MaterialPerset::get_name);

	ClassDB::bind_method(D_METHOD("set_shader_parameter", "key", "value"), &MaterialPerset::set_shader_parameter);
	ClassDB::bind_method(D_METHOD("get_shader_material"), &MaterialPerset::get_shader_parameter_list);

	ClassDB::bind_method(D_METHOD("set_shader_material", "value"), &MaterialPerset::set_shader_material);
	ClassDB::bind_method(D_METHOD("get_shader_material"), &MaterialPerset::get_shader_material);

	ClassDB::bind_static_method("MaterialPerset", D_METHOD("instantiate", "uuid", "name", "shader", "parameter"), &MaterialPerset::instantiate);
}

MaterialPerset::MaterialPerset() {

}

MaterialPerset::~MaterialPerset() {

}

void MaterialPerset::set_shader_material(const Ref<ShaderMaterial>& value)
{
	shader_material = value;
}

Ref<ShaderMaterial> MaterialPerset::get_shader_material() const
{
	return shader_material;
}

Array MaterialPerset::get_shader_parameter_list() const
{
	return RenderingServer::get_singleton()->get_shader_parameter_list(shader_material->get_shader_material()->get_rid());
}

void MaterialPerset::set_shader_parameter(const String& key, const Variant& value)
{
	shader_material->set_shader_parameter(key, value);
}


Ref<MaterialPerset> MaterialPerset::instantiate(const String& uuid, const String& name, const Ref<ShaderMaterial>& shader_material, Dictionary parameter) {
	Ref<MaterialPerset> material_perset;
	material_perset.instantiate();
	material_perset->uuid = uuid;
	material_perset->name = name;

	material_perset->shader_material = shader_material;

	Array keys = parameter.keys();
	for (size_t i = 0; i < keys.size(); i++)
	{
		material_perset->shader_material->set_shader_parameter(keys[i], parameter[keys[i]]);
	}

	return material_perset;
}