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

//#define VOXEL(type,id,rotation,flag) ((type << 30) | (id << 20) | (abs(rotation.x % 360 / 15) << 15) | (abs(rotation.y % 360 / 15)) << 10 | (abs(rotation.z % 360 / 15) << 5) | (flag & 0b11111))
//
//#define EMPTY_VOXEL 0 
//#define BASICS_VOXEL(id,rotation,flag) VOXEL(VoxelContainer::BASICS, id, rotation, flag)
//#define MODEL_VOXEL(id,rotation,flag) VOXEL(VoxelContainer::MODEL, id, rotation, flag)
//#define DEVICE_VOXEL(id,rotation,flag) VOXEL(VoxelContainer::DEVICE, id, rotation, flag)

typedef uint64_t Voxel;

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
};


#endif // !PRESET_H
