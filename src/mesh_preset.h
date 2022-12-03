#ifndef MESH_PRESET_H
#define MESH_PRESET_H

#include "preset.h"

class MeshPreset : public Resource
{
	GDCLASS(MeshPreset, Resource);
private:
	Ref<Mesh> mesh;
	TypedArray<int> materials;
	mutable Array prototype;
	mutable TypedArray<Array> memorandum;
protected:
	static void _bind_methods();
public:
	MeshPreset();
	~MeshPreset();
	void set_mesh(const Ref<Mesh>& value);
	Ref<Mesh> get_mesh() const;

	void set_materials(const TypedArray<int>& value);
	TypedArray<int> get_materials() const;

	void build_mesh(const Array& arrays, const int& surface_index, const Vector3& position, const Vector3& rotation) const;


	static Vector3 rotate_vertex(const Vector3& vertex, const Vector3i& rotation);
	static void get_tbn(Vector3 vertexs[3], Vector2 uvs[3], Vector3* tangent, Vector3* binormal, Vector3* normal);
};

#endif // !MESH_PRESET_H
