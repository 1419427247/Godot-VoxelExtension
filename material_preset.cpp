#include "material_preset.h"

void MaterialPreset::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_shader_material", "value"), &MaterialPreset::set_shader_material);
	ClassDB::bind_method(D_METHOD("get_shader_material"), &MaterialPreset::get_shader_material);

	ClassDB::bind_method(D_METHOD("get_shader_parameter_list"), &MaterialPreset::get_shader_parameter_list);
	ClassDB::bind_method(D_METHOD("set_shader_parameter", "key", "value"), &MaterialPreset::set_shader_parameter);

	ClassDB::bind_static_method("MaterialPreset", D_METHOD("instantiate", "uuid", "name", "shader", "parameter"), &MaterialPreset::instantiate);

	ClassDB::add_property("MaterialPreset", PropertyInfo(Variant::OBJECT, "shader_material", PROPERTY_HINT_RESOURCE_TYPE, "ShaderMaterial"), "set_shader_material", "get_shader_material");
}

MaterialPreset::MaterialPreset() {

}

MaterialPreset::~MaterialPreset() {

}

void MaterialPreset::set_shader_material(const Ref<ShaderMaterial>& value)
{
	shader_material = value;
}

Ref<ShaderMaterial> MaterialPreset::get_shader_material() const
{
	return shader_material;
}

Array MaterialPreset::get_shader_parameter_list() const
{
	return RenderingServer::get_singleton()->get_shader_parameter_list(shader_material->get_shader()->get_rid());
}

void MaterialPreset::set_shader_parameter(const String& key, const Variant& value)
{
	shader_material->set_shader_parameter(key, value);
}


Ref<MaterialPreset> MaterialPreset::instantiate(const String& uuid, const String& name, const Ref<ShaderMaterial>& shader_material, Dictionary parameter) {
	Ref<MaterialPreset> material_preset;
	material_preset.instantiate();
	material_preset->uuid = uuid;
	material_preset->name = name;
	material_preset->shader_material = shader_material;

	Array keys = parameter.keys();
	for (int i = 0; i < keys.size(); i++)
	{
		material_preset->shader_material->set_shader_parameter(keys[i], parameter[keys[i]]);
	}

	return material_preset;
}