#include "material_perset.h"

MaterialPerset::MaterialPerset() {

}

MaterialPerset::~MaterialPerset() {

}

int MaterialPerset::get_id() const { return id; }
String MaterialPerset::get_name() const { return name; }
Color MaterialPerset::get_albedo() const { return albedo; }
Ref<Texture2D> MaterialPerset::get_albedo_texture() const { return albedo_texture; }
float MaterialPerset::get_normal() const {
	return normal;
}
Ref<Texture2D> MaterialPerset::get_normal_texture() const {
	return normal_texture;
}
float MaterialPerset::get_metallic() const { return metallic; }
Ref<Texture2D> MaterialPerset::get_metallic_texture() const { return metallic_texture; }
float MaterialPerset::get_roughness() const { return roughness; }
Ref<Texture2D> MaterialPerset::get_roughness_texture() const { return roughness_texture; }
float MaterialPerset::get_height() const { return height; }
Ref<Texture2D> MaterialPerset::get_height_texture() const { return height_texture; }
Vector2 MaterialPerset::get_uv() const { return uv; }
Vector2 MaterialPerset::get_offset() const { return offset; }

void MaterialPerset::set_id(const int value) {
	id = value;
}
void MaterialPerset::set_name(const String& value) {
	name = value;
}
void MaterialPerset::set_albedo(const Color& value) {
	albedo = value;
	instance->set_shader_parameter(StringName("albedo"), value);
}
void MaterialPerset::set_albedo_texture(const Ref<Texture2D>& value) {
	albedo_texture = (Texture2D*)value.ptr();
	instance->set_shader_parameter(StringName("albedo_texture"), value);
}
void MaterialPerset::set_normal(const float value) {
	normal = value;
	instance->set_shader_parameter(StringName("normal"), value);
}
void MaterialPerset::set_normal_texture(const Ref<Texture2D>& value) {
	normal_texture = (Texture2D*)value.ptr();
	instance->set_shader_parameter(StringName("normal_texture"), value);
}
void MaterialPerset::set_metallic(const float value) {
	metallic = value;
	instance->set_shader_parameter(StringName("metallic"), value);
}
void MaterialPerset::set_metallic_texture(const Ref<Texture2D>& value) {
	metallic_texture = (Texture2D*)value.ptr();
	instance->set_shader_parameter(StringName("metallic_texture"), value);
}
void MaterialPerset::set_roughness(const float  value) {
	roughness = value;
	instance->set_shader_parameter(StringName("roughness"), value);
}
void MaterialPerset::set_roughness_texture(const Ref<Texture2D>& value) {
	roughness_texture = (Texture2D*)value.ptr();
	instance->set_shader_parameter(StringName("roughness_texture"), value);
}
void MaterialPerset::set_height(const float  value) {
	height = value;
	instance->set_shader_parameter(StringName("height"), value);
}
void MaterialPerset::set_height_texture(const Ref<Texture2D>& value) {
	height_texture = (Texture2D*)value.ptr();
	instance->set_shader_parameter(StringName("height_texture"), value);
}
void MaterialPerset::set_uv(const Vector2& value) {
	uv = value;
	instance->set_shader_parameter(StringName("uv"), value);
}
void MaterialPerset::set_offset(const Vector2& value) {
	offset = value;
	instance->set_shader_parameter(StringName("offset"), value);
}

Ref<MaterialPerset> MaterialPerset::instantiate(int id, String name, Ref<Shader> shader, Dictionary parameter) {
	Ref<MaterialPerset> material_perset;
	material_perset.instantiate();
	material_perset->id = id;
	material_perset->name = name;

	material_perset->instance = memnew(ShaderMaterial());
	material_perset->instance->set_shader(shader);

	material_perset->set_albedo((Color)parameter.get("albedo", 0));
	material_perset->set_albedo_texture((Ref<Texture2D>)parameter.get("albedo_texture", nullptr));
	material_perset->set_metallic(parameter.get("metallic", 0));
	material_perset->set_metallic_texture(parameter.get("metallic_texture", nullptr));
	material_perset->set_roughness(parameter.get("roughness", 0));
	material_perset->set_roughness_texture(parameter.get("roughness_texture", nullptr));
	material_perset->set_height(parameter.get("height", 0));
	material_perset->set_height_texture(parameter.get("height_texture", nullptr));
	material_perset->set_uv(parameter.get("uv", Vector2(1, 1)));
	material_perset->set_offset(parameter.get("offset", Vector2(1, 1)));
	return material_perset;
}

void MaterialPerset::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_id", "value"), &MaterialPerset::set_id);
	ClassDB::bind_method(D_METHOD("set_name", "value"), &MaterialPerset::set_name);
	ClassDB::bind_method(D_METHOD("set_albedo", "value"), &MaterialPerset::set_albedo);
	ClassDB::bind_method(D_METHOD("set_albedo_texture", "value"), &MaterialPerset::set_albedo_texture);
	ClassDB::bind_method(D_METHOD("set_normal"), &MaterialPerset::set_normal);
	ClassDB::bind_method(D_METHOD("set_normal_texture"), &MaterialPerset::set_normal_texture);
	ClassDB::bind_method(D_METHOD("set_metallic", "value"), &MaterialPerset::set_metallic);
	ClassDB::bind_method(D_METHOD("set_metallic_texture", "value"), &MaterialPerset::set_metallic_texture);
	ClassDB::bind_method(D_METHOD("set_roughness", "value"), &MaterialPerset::set_roughness);
	ClassDB::bind_method(D_METHOD("set_roughness_texture", "value"), &MaterialPerset::set_roughness_texture);
	ClassDB::bind_method(D_METHOD("set_height", "value"), &MaterialPerset::set_height);
	ClassDB::bind_method(D_METHOD("set_height_texture", "value"), &MaterialPerset::set_height_texture);
	ClassDB::bind_method(D_METHOD("set_uv", "value"), &MaterialPerset::set_uv);
	ClassDB::bind_method(D_METHOD("set_offset", "value"), &MaterialPerset::set_offset);

	ClassDB::bind_method(D_METHOD("get_id"), &MaterialPerset::get_id);
	ClassDB::bind_method(D_METHOD("get_name"), &MaterialPerset::get_name);
	ClassDB::bind_method(D_METHOD("get_albedo"), &MaterialPerset::get_albedo);
	ClassDB::bind_method(D_METHOD("get_albedo_texture"), &MaterialPerset::get_albedo_texture);
	ClassDB::bind_method(D_METHOD("get_normal"), &MaterialPerset::get_normal);
	ClassDB::bind_method(D_METHOD("get_normal_texture"), &MaterialPerset::get_normal_texture);
	ClassDB::bind_method(D_METHOD("get_metallic"), &MaterialPerset::get_metallic);
	ClassDB::bind_method(D_METHOD("get_metallic_texture"), &MaterialPerset::get_metallic_texture);
	ClassDB::bind_method(D_METHOD("get_roughness"), &MaterialPerset::get_roughness);
	ClassDB::bind_method(D_METHOD("get_roughness_texture"), &MaterialPerset::get_roughness_texture);
	ClassDB::bind_method(D_METHOD("get_height"), &MaterialPerset::get_height);
	ClassDB::bind_method(D_METHOD("get_height_texture"), &MaterialPerset::get_height_texture);
	ClassDB::bind_method(D_METHOD("get_uv"), &MaterialPerset::get_uv);
	ClassDB::bind_method(D_METHOD("get_offset"), &MaterialPerset::get_offset);

	ClassDB::bind_static_method("MaterialPerset", D_METHOD("instantiate", "id", "name", "shader", "parameter"), &MaterialPerset::instantiate);
}