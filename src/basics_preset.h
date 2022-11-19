#ifndef BASIC_PRESET_H
#define BASIC_PRESET_H

#include "preset.h"

static const Vector3i DIRCTIONS[6] = {
	Vector3i(0, 1, 0),
	Vector3i(0, -1, 0),
	Vector3i(0, 0, -1),
	Vector3i(0, 0, 1),
	Vector3i(-1, 0, 0),
	Vector3i(1, 0, 0),
};
class BasicsPreset : public Preset
{
	GDCLASS(BasicsPreset, Preset);
	enum Dirction {
		UP = 0,
		DOWN = 1,
		FRONT = 2,
		BACK = 3,
		LEFT = 4,
		RIGHT = 5,
	};
private:
	int materials[6];
protected:
	static void _bind_methods();
public:
	BasicsPreset();
	~BasicsPreset();

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

	int get_material_id(const int& value);

	static Ref<BasicsPreset> instantiate(const String& name, const Dictionary& materials);
};

VARIANT_ENUM_CAST(BasicsPreset, Dirction);

#endif // !BASIC_PRESET_H