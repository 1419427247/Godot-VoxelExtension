#include "model_preset.h"
#include "voxel_block_data.h"


void ModelPreset::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_use_mask", "value"), &ModelPreset::set_use_mask);
	ClassDB::bind_method(D_METHOD("is_use_mask"), &ModelPreset::is_use_mask);

	ClassDB::bind_method(D_METHOD("set_mesh_preset", "value"), &ModelPreset::set_mesh_preset);
	ClassDB::bind_method(D_METHOD("get_mesh_preset"), &ModelPreset::get_mesh_preset);

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_mask"), "set_use_mask", "is_use_mask");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "mesh_presets", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::OBJECT) + "/" + String::num_int64(PROPERTY_HINT_RESOURCE_TYPE) + ":MeshPreset"), "set_mesh_preset", "get_mesh_preset");

}

ModelPreset::ModelPreset() {
	use_mask = false;
	mesh_presets.resize(1);
}
ModelPreset::~ModelPreset() {
}

void ModelPreset::set_use_mask(const bool& value) {
	use_mask = value;
	if (use_mask == true)
	{
		mesh_presets.resize(64);
	}
	else {
		mesh_presets.resize(1);
	}
	notify_property_list_changed();
}

bool ModelPreset::is_use_mask() const {
	return use_mask;
}

void ModelPreset::set_mesh_preset(const TypedArray<MeshPreset>& value) {
	mesh_presets = value;
	if (use_mask == true)
	{
		mesh_presets.resize(64);
	}
	else {
		mesh_presets.resize(1);
	}
	notify_property_list_changed();
}

TypedArray<MeshPreset> ModelPreset::get_mesh_preset() const {
	return mesh_presets;
}