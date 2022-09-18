#ifndef DEVICE_H
#define DEVICE_H

#include <godot_cpp/classes/node3d.hpp>

using namespace godot;

class Device : public Node3D
{
	GDCLASS(Device, Node3D);
private:

public:

protected:
	static void _bind_methods();
};

#endif // !DEVICE_H
