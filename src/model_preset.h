#ifndef MODEL_PRESET_H
#define MODEL_PRESET_H

#include "preset.h"
class ModelPreset : public Preset
{
	GDCLASS(ModelPreset, Preset);
protected:
	static void _bind_methods();
private:
	Ref<Mesh> mesh;
	TypedArray<int> materials;
	Array memorandum;
public:
	ModelPreset();
	~ModelPreset();

	void set_mesh(const Ref<Mesh>& value);
	Ref<Mesh> get_mesh() const;

	void set_materials(const TypedArray<int>& value);
	TypedArray<int> get_materials() const;

	void build_mesh(const Array& arrays, const int& surface_index, const Vector3& position, const Vector3& rotation);
	static Ref<ModelPreset> instantiate(const String& name, const Ref<Mesh>& mesh, Array materials);
};

#endif // !MODEL_PRESET_H
