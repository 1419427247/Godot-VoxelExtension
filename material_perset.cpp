#include "material_perset.h"

MaterialPerset::MaterialPerset() {

}

MaterialPerset::~MaterialPerset() {

}

int MaterialPerset::get_id() { return id; }
String MaterialPerset::get_name() { return name; }
Color MaterialPerset::get_albedo() { return albedo; }
Ref<Texture2D> MaterialPerset::get_albedo_texture() { return albedo_texture; }
float MaterialPerset::get_metallic() { return metallic; }
Ref<Texture2D> MaterialPerset::get_metallic_texture() { return metallic_texture; }
float MaterialPerset::get_roughness() { return roughness; }
Ref<Texture2D> MaterialPerset::get_roughness_texture() { return roughness_texture; }
float MaterialPerset::get_height() { return height; }
Ref<Texture2D> MaterialPerset::get_height_texture() { return height_texture; }
Vector2 MaterialPerset::get_uv() { return uv; }
Vector2 MaterialPerset::get_offset() { return offset; }

void MaterialPerset::set_id(int  value) {
	id = value;
}
void MaterialPerset::set_name(String  value) {
	name = value;
}

void MaterialPerset::set_albedo(Color  value) {
	albedo = value;
}
void MaterialPerset::set_albedo_texture(Ref<Texture2D> value) {
	value.reference_ptr(albedo_texture);
}
void MaterialPerset::set_metallic(float value) {
	metallic = value;
}
void MaterialPerset::set_metallic_texture(Ref<Texture2D> value) {
	value.reference_ptr(metallic_texture);
}
void MaterialPerset::set_roughness(float  value) {
	roughness = value;
}
void MaterialPerset::set_roughness_texture(Ref<Texture2D> value) {
	value.reference_ptr(roughness_texture);
}
void MaterialPerset::set_height(float  value) {
	height = value;
}
void MaterialPerset::set_height_texture(Ref<Texture2D> value) {
	value.reference_ptr(height_texture);
}
void MaterialPerset::set_uv(Vector2  value) {
	uv = value;
}
void MaterialPerset::set_offset(Vector2  value) {
	offset = value;
}

Ref<MaterialPerset> MaterialPerset::instantiate(int id, String name, Ref<Shader> shader, Dictionary parameter) {
	Ref<MaterialPerset> material_perset;
	material_perset.instantiate();
	material_perset->id = id;
	material_perset->name = name;

	material_perset->instance = memnew(ShaderMaterial());
	material_perset->instance->set_shader(shader);
	return material_perset;
}

void MaterialPerset::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_id", "value"), &MaterialPerset::set_id);
	ClassDB::bind_method(D_METHOD("set_name", "value"), &MaterialPerset::set_name);
	ClassDB::bind_method(D_METHOD("set_albedo", "value"), &MaterialPerset::set_albedo);
	ClassDB::bind_method(D_METHOD("set_albedo_texture", "value"), &MaterialPerset::set_albedo_texture);
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