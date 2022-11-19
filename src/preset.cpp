#include "preset.h"

void Preset::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_name", "value"), &Preset::set_name);
	ClassDB::bind_method(D_METHOD("get_name"), &Preset::get_name);

	ClassDB::bind_method(D_METHOD("set_script", "value"), &Preset::set_script);
	ClassDB::bind_method(D_METHOD("get_script"), &Preset::get_script);

	ClassDB::bind_method(D_METHOD("set_transparent", "value"), &Preset::set_transparent);
	ClassDB::bind_method(D_METHOD("get_transparent"), &Preset::get_transparent);

	ClassDB::bind_method(D_METHOD("set_filter", "value"), &Preset::set_filter);
	ClassDB::bind_method(D_METHOD("get_filter"), &Preset::get_filter);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "transparent"), "set_transparent", "get_transparent");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "filter",PROPERTY_HINT_LAYERS_3D_RENDER), "set_filter", "get_filter");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "script", PROPERTY_HINT_RESOURCE_TYPE, "Script"), "set_script", "get_script");
}

Preset::Preset()
{
	transparent = 0;
	filter = 0b0;
}

Preset::~Preset()
{
}

void Preset::set_name(const String& value)
{
	name = value;
}

String Preset::get_name() const
{
	return name;
}

void Preset::set_transparent(const int& value)
{
	transparent = value;
}

int Preset::get_transparent() const
{
	return transparent;
}

void Preset::set_filter(const int& value)
{
	filter = value;
}

int Preset::get_filter() const
{
	return filter;
}

void Preset::set_script(const Ref<Script>& value)
{
	script = value;
}

Ref<Script> Preset::get_script() const
{
	return script;
}