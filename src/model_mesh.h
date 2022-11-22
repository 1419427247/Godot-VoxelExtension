#ifndef MODEL_MESH_H
#define MODEL_MESH_H

#include "preset.h"

class ModelMesh : public Resource
{
	GDCLASS(ModelMesh, Resource);
private:
	Ref<Mesh> mesh;
	TypedArray<int> materials;
	TypedArray<Array> memorandum;
protected:
	static void _bind_methods();
public:
	ModelMesh();
	~ModelMesh();
	void set_mesh(const Ref<Mesh>& value);
	Ref<Mesh> get_mesh() const;

	void set_materials(const TypedArray<int>& value);
	TypedArray<int> get_materials() const;

	void build_mesh(const Array& arrays, const int& surface_index, const Vector3& position, const Vector3& rotation);
};

#endif // !MESH_PRESET_H
