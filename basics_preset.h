#ifndef BASIC_PRESET_H
#define BASIC_PRESET_H

#include "preset.h"

using namespace godot;

class BasicsPreset : public Preset
{
	GDCLASS(BasicsPreset, Preset);
	enum MeshKey {
		UP = 0,
		DOWN = 1,
		FRONT = 2,
		BACK = 3,
		LEFT = 4,
		RIGHT = 5,
	};
private:
	int up;
	int down;
	int front;
	int back;
	int left;
	int right;
protected:
	static void _bind_methods();
public:
	BasicsPreset();
	~BasicsPreset();

	void set_up(const int& value);
	int get_up() const;
	void set_down(const int& value);
	int get_down() const;
	void set_front(const int& value);
	int get_front() const;
	void set_back(const int& value);
	int get_back() const;
	void set_left(const int& value);
	int get_left() const;
	void set_right(const int& value);
	int get_right() const;

	static Ref<BasicsPreset> instantiate(const String& name, const Dictionary& materials);

	static Vector3 rotate_vertex(const Vector3& vertex, const Vector3i& rotation);
	static void build_mesh(const int& mesh_key, const Array& arrays, const Vector3& position, const Vector3& rotation);

	static void build_up_mesh(const Array& arrays, const Vector3& position, const Vector3& rotation);
	static void build_down_mesh(const Array& arrays, const Vector3& position, const Vector3& rotation);
	static void build_front_mesh(const Array& arrays, const Vector3& position, const Vector3& rotation);
	static void build_back_mesh(const Array& arrays, const Vector3& position, const Vector3& rotation);
	static void build_left_mesh(const Array& arrays, const Vector3& position, const Vector3& rotation);
	static void build_right_mesh(const Array& arrays, const Vector3& position, const Vector3& rotation);
};

#endif // !BASIC_PRESET_H