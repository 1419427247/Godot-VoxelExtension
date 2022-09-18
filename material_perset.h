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

	float normal;
	Texture2D* normal_texture;

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

	int get_id() const;
	String get_name() const;
	Color get_albedo() const;
	Ref<Texture2D> get_albedo_texture() const;
	float get_normal() const;
	Ref<Texture2D> get_normal_texture() const;
	float get_metallic() const;
	Ref<Texture2D> get_metallic_texture() const;
	float get_roughness() const;
	Ref<Texture2D> get_roughness_texture() const;
	float get_height() const;
	Ref<Texture2D> get_height_texture() const;
	Vector2 get_uv() const;
	Vector2 get_offset() const;

	void set_id(const int value);
	void set_name(const String& value);
	void set_albedo(const Color& value);
	void set_albedo_texture(const Ref<Texture2D>& value);
	void set_normal(const float value);
	void set_normal_texture(const Ref<Texture2D>& value);
	void set_metallic(const float value);
	void set_metallic_texture(const Ref<Texture2D>& value);
	void set_roughness(const float value);
	void set_roughness_texture(const Ref<Texture2D>& value);
	void set_height(const float value);
	void set_height_texture(const Ref<Texture2D>& value);
	void set_uv(const Vector2& value);
	void set_offset(const Vector2& value);

	static Ref<MaterialPerset> instantiate(int id, String name, Ref<Shader> shader,Dictionary parameter);

protected:
	static void _bind_methods();
};

#endif // !MATERIAL_PERSET_H
