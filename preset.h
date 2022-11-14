#ifndef PRESET_H
#define PRESET_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/static_body3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/concave_polygon_shape3d.hpp>
#include <godot_cpp/classes/stream_peer_buffer.hpp>
#include <godot_cpp/classes/shader_material.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/mutex.hpp>
#include <godot_cpp/classes/script.hpp>
#include <godot_cpp/classes/stream_peer_buffer.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/plane.hpp>
#include <godot_cpp/godot.hpp>
#include <godot/gdnative_interface.h>
#include <godot_cpp/templates/hash_map.hpp>

using namespace godot;

typedef unsigned int Voxel;
class VoxelRoom;

class Preset : public Resource
{
	GDCLASS(Preset, Resource);
private:

protected:
	String name;
	int transparent;
	int filter;
	Ref<Script> script;
	static void _bind_methods();
public:
	Preset();
	~Preset();
	void set_name(const String& value);
	String get_name() const;

	void set_transparent(const int& value);
	int get_transparent() const;

	void set_filter(const int& value);
	int get_filter() const;

	void set_script(const Ref<Script>& value);
	Ref<Script> get_script() const;

	static Vector3 rotate_vertex(const Vector3& vertex, const Vector3i& rotation);
	static Vector3 get_triangle_normal(const Vector3& a, const Vector3& b, const Vector3& c);

	virtual void _on_voxel_new(VoxelRoom * voxel_room, const Voxel & voxel, const Vector3i & position);
	virtual void _on_voxel_delete(VoxelRoom* voxel_room, const Voxel& voxel, const Vector3i& position);
};


#endif // !PRESET_H
