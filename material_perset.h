#ifndef MATERIAL_PERSET_H
#define MATERIAL_PERSET_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/texture2d.hpp>

using namespace godot;

class MaterialPerset : public RefCounted
{
	friend class Chunk;
	GDCLASS(MaterialPerset, RefCounted);
private:
	int id;
	String name;
	ShaderMaterial* instance;

	Color albedo;
	Texture2D* albedo_texture;

	float metallic;
	Texture2D* metallic_texture;

	float roughness;
	Texture2D* roughness_texture;

	float height;
	Texture2D* height_texture;

	Vector2 uv;
	Vector2 offset;
public:
	MaterialPerset();
	~MaterialPerset();

	int get_id();
	String get_name();
	Color get_albedo();
	Ref<Texture2D> get_albedo_texture();
	float get_metallic();
	Ref<Texture2D> get_metallic_texture();
	float get_roughness();
	Ref<Texture2D> get_roughness_texture();
	float get_height();
	Ref<Texture2D> get_height_texture();
	Vector2 get_uv();
	Vector2 get_offset();

	void set_id(int value);
	void set_name(String value);
	void set_albedo(Color value);
	void set_albedo_texture(Ref<Texture2D> value);
	void set_metallic(float value);
	void set_metallic_texture(Ref<Texture2D> value);
	void set_roughness(float value);
	void set_roughness_texture(Ref<Texture2D> value);
	void set_height(float value);
	void set_height_texture(Ref<Texture2D> value);
	void set_uv(Vector2 value);
	void set_offset(Vector2 value);

	static Ref<MaterialPerset> instantiate(int id, String name, Ref<Shader> shader,Dictionary parameter);

protected:
	static void _bind_methods();
};

#endif // !MATERIAL_PERSET_H
