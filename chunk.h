#ifndef CHUNK_H
#define CHUNK_H

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/static_body3d.hpp>


using namespace godot;

class VoxelWorld;
class BasicsPerset;

class Chunk : public Node3D
{
	GDCLASS(Chunk, Node3D);

	enum State {
		NONE,
		GENERATING,
		COMPLETED,
	};

private:
	VoxelWorld* woxel_world;

	int state;
	Vector3i chunk_position;

	MeshInstance3D* mesh_instance;

	StaticBody3D* collision;
	CollisionShape3D* collision_shap;

	Area3D* trigger;
	CollisionShape3D* trigger_shap;

	Array mesh_arrays;
	PackedVector3Array trigger_faces;

	void instantiate_mesh_array(int index);
	void generate_brick_mesh(Ref<BasicsPerset> basics_perset,const Vector3i& relative_position, const Vector3i& rotation);
public:
	Chunk();
	~Chunk();

	void set_chunk_position(Vector3i value);
	Vector3i get_chunk_position();

	void set_voxel(const int type, const int id, const Vector3i& position, const Vector3i& rotation);
	int get_voxel_type(const Vector3i& position) const;
	int get_voxel_id(const Vector3i& position) const;
	Vector3i get_voxel_rotation(const Vector3i& position) const;

	void generate_mesh();
	void generate_collider();
	void generate_trigger();

protected:
	static void _bind_methods();
	void _notification(int p_what);
};

#endif

