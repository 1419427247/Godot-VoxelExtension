#include "preset.h"

void Preset::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_uuid"), &Preset::set_uuid);
	ClassDB::bind_method(D_METHOD("get_uuid"), &Preset::get_uuid);

	ClassDB::bind_method(D_METHOD("set_name", "value"), &Preset::set_name);
	ClassDB::bind_method(D_METHOD("get_name"), &Preset::get_name);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "uuid"), "set_uuid", "get_uuid");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");
}

Preset::Preset()
{
}

Preset::~Preset()
{
}

void Preset::set_uuid(const String& value)
{
	uuid = value;
}

String Preset::get_uuid() const
{
	return uuid;
}

void Preset::set_name(const String& value)
{
	name = value;
}

String Preset::get_name() const
{
	return name;
}
