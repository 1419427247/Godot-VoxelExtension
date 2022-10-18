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
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/godot.hpp>
#include <godot/gdnative_interface.h>
using namespace godot;

class Preset : public Resource
{
	GDCLASS(Preset, Resource);
private:

protected:
	String uuid;
	String name;
	static void _bind_methods();
public:
	Preset();
	~Preset();
	void set_uuid(const String& value);
	String get_uuid() const;

	void set_name(const String& value);
	String get_name() const;
};

#endif // !PRESET_H
