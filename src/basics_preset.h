#ifndef BASIC_PRESET_H
#define BASIC_PRESET_H

#include "preset.h"

class BasicsPreset : public Preset
{
	GDCLASS(BasicsPreset, Preset);
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

};

VARIANT_ENUM_CAST(BasicsPreset, Dirction);

#endif // !BASIC_PRESET_H