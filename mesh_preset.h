#ifndef MESH_PRESET_H
#define MESH_PRESET_H

#include "preset.h"
class MeshPreset : public Preset
{
	GDCLASS(MeshPreset, Preset);
protected:
	static void _bind_methods();
private:
	Ref<Mesh> mesh;
	TypedArray<int> materials;

	Array mesh_arrays;
public:
	MeshPreset();
	~MeshPreset();

	void set_mesh(const Ref<Mesh>& value);
	Ref<Mesh> get_mesh() const;

	void set_materials(const TypedArray<int>& value);
	TypedArray<int> get_materials();

	void build_mesh(const Array& arrays, const int& surface_index, const Vector3& position, const Vector3& rotation);

	static Ref<MeshPreset> instantiate(const String& uuid, const String& name, const Ref<Mesh>& mesh, Array materials);
};

#endif // !MESH_PRESET_H
