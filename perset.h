#ifndef PERSET_H
#define PERSET_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/shader_material.hpp>
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
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class Perset : public RefCounted
{
	GDCLASS(Perset, RefCounted);
private:

protected:
	String uuid;
	String name;
	static void _bind_methods();
public:
	String get_uuid() const;
	String get_name() const;
	void set_name(const String& value);
};

#endif // !PERSET_H
