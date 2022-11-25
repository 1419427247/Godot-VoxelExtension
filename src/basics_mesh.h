#ifndef BASICS_MESH_H
#define BASICS_MESH_H

#include "preset.h"

class BasicsMesh : public Resource
{
	GDCLASS(BasicsMesh, Resource);
private:
	Ref<Mesh> mesh;
	mutable TypedArray<Array> memorandum;
protected:
	static void _bind_methods();
public:
	BasicsMesh();
	~BasicsMesh();

	void set_mesh(const Ref<Mesh>& value);
	Ref<Mesh> get_mesh() const;

	void build_mesh(const Array& arrays, const int& direction, const Vector3& position, const Vector3& rotation) const;
};

#endif // !MESH_PRESET_H
