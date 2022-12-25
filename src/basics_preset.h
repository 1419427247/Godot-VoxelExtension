#ifndef BASIC_PRESET_H
#define BASIC_PRESET_H

#include "mesh_preset.h"

class BasicsPreset : public Preset
{
	GDCLASS(BasicsPreset, Preset);
private:
	Ref<MeshPreset> mesh_preset;
	TypedArray<int> materials;

	TypedArray<Vector2> uvs[6];
protected:
	static void _bind_methods();
public:
	BasicsPreset();
	~BasicsPreset();

	void set_basics_mesh(const Ref<MeshPreset>& mesh_preset);
	Ref<MeshPreset> get_basics_mesh() const;

	void set_up_material_id(const int& value);
	int get_up_material_id() const;
	void set_down_material_id(const int& value);
	int get_down_material_id() const;
	void set_front_material_id(const int& value);
	int get_front_material_id() const;
	void set_back_material_id(const int& value);
	int get_back_material_id() const;
	void set_left_material_id(const int& value);
	int get_left_material_id() const;
	void set_right_material_id(const int& value);
	int get_right_material_id() const;

	int get_material_id(const int& value) const;


	void set_up_material_uv(const TypedArray<Vector2>& value);
	TypedArray<Vector2> get_up_material_uv() const;
	void set_down_material_uv(const TypedArray<Vector2>& value);
	TypedArray<Vector2> get_down_material_uv() const;
	void set_front_material_uv(const TypedArray<Vector2>& value);
	TypedArray<Vector2> get_front_material_uv() const;
	void set_back_material_uv(const TypedArray<Vector2>& value);
	TypedArray<Vector2> get_back_material_uv() const;
	void set_left_material_uv(const TypedArray<Vector2>& value);
	TypedArray<Vector2> get_left_material_uv() const;
	void set_right_material_uv(const TypedArray<Vector2>& value);
	TypedArray<Vector2> get_right_material_uv() const;

	Vector2 get_material_uv(const int& direction,const int& index) const;
};


#endif // !BASIC_PRESET_H