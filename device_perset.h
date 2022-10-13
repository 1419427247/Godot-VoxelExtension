#ifndef DEVICE_PERSET_H
#define DEVICE_PERSET_H

#include "perset.h"
class DevicePerset : public Perset
{
private:
	Ref<PackedScene> packed_scene;
protected:
	static void _bind_methods();
public:
	DevicePerset();
	~DevicePerset();

	void set_packed_scene(const Ref<PackedScene>& packed_scene);
	Ref<PackedScene> get_packed_scene() const;

	static Ref<DevicePerset> instantiate(const String& uuid, const String& name, const Ref<PackedScene>& packed_scene);
};

#endif // !DEVICE_PERSET_H