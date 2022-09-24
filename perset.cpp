#include "perset.h"

void Perset::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_uuid"), &Perset::get_uuid);

	ClassDB::bind_method(D_METHOD("set_name", "value"), &Perset::set_name);
	ClassDB::bind_method(D_METHOD("get_name"), &Perset::get_name);

	ClassDB::add_property("BasicsPerset", PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");
}

String Perset::get_uuid() const
{
	return uuid;
}

String Perset::get_name() const
{
	return name;
}

void Perset::set_name(const String& value)
{
	name = value;
}
