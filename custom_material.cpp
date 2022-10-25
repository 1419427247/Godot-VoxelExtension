#include "custom_material.h"

void CustomMaterial::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_shader_material", "value"), &CustomMaterial::set_shader_material);
	ClassDB::bind_method(D_METHOD("get_shader_material"), &CustomMaterial::get_shader_material);

	ClassDB::bind_method(D_METHOD("get_shader_parameter_list"), &CustomMaterial::get_shader_parameter_list);
	ClassDB::bind_method(D_METHOD("set_shader_parameter", "key", "value"), &CustomMaterial::set_shader_parameter);

	ClassDB::bind_static_method("CustomMaterial", D_METHOD("instantiate", "name", "shader", "parameter"), &CustomMaterial::instantiate);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "shader_material", PROPERTY_HINT_RESOURCE_TYPE, "ShaderMaterial"), "set_shader_material", "get_shader_material");
}

CustomMaterial::CustomMaterial() {

}

CustomMaterial::~CustomMaterial() {

}

void CustomMaterial::set_shader_material(const Ref<ShaderMaterial>& value)
{
	shader_material = value;
}

Ref<ShaderMaterial> CustomMaterial::get_shader_material() const
{
	return shader_material;
}

Array CustomMaterial::get_shader_parameter_list() const
{
	return RenderingServer::get_singleton()->get_shader_parameter_list(shader_material->get_shader()->get_rid());
}

void CustomMaterial::set_shader_parameter(const String& key, const Variant& value)
{
	shader_material->set_shader_parameter(key, value);
}


Ref<CustomMaterial> CustomMaterial::instantiate(const String& name, const Ref<ShaderMaterial>& shader_material, Dictionary parameter) {
	Ref<CustomMaterial> custom_material;
	custom_material.instantiate();
	custom_material->shader_material = shader_material;

	Array keys = parameter.keys();
	for (int i = 0; i < keys.size(); i++)
	{
		custom_material->shader_material->set_shader_parameter(keys[i], parameter[keys[i]]);
	}

	return custom_material;
}