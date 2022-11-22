#include "preset.h"

void Preset::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_name", "value"), &Preset::set_name);
	ClassDB::bind_method(D_METHOD("get_name"), &Preset::get_name);

	ClassDB::bind_method(D_METHOD("set_script", "value"), &Preset::set_script);
	ClassDB::bind_method(D_METHOD("get_script"), &Preset::get_script);

	ClassDB::bind_method(D_METHOD("set_layer", "value"), &Preset::set_layer);
	ClassDB::bind_method(D_METHOD("get_layer"), &Preset::get_layer);

	ClassDB::bind_method(D_METHOD("set_filter", "value"), &Preset::set_filter);
	ClassDB::bind_method(D_METHOD("get_filter"), &Preset::get_filter);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name"), "set_name", "get_name");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "transparent"), "set_layer", "get_layer");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "filter",PROPERTY_HINT_LAYERS_3D_RENDER), "set_filter", "get_filter");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "script", PROPERTY_HINT_RESOURCE_TYPE, "Script"), "set_script", "get_script");
}

Preset::Preset()
{
	layer = 0;
	filter = 0b1;
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

void Preset::set_layer(const int& value)
{
	layer = value;
}

int Preset::get_layer() const
{
	return layer;
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