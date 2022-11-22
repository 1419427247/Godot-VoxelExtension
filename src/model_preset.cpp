#include "model_preset.h"
#include "voxel_block_data.h"


void ModelPreset::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_use_mask", "value"), &ModelPreset::set_use_mask);
	ClassDB::bind_method(D_METHOD("is_use_mask"), &ModelPreset::is_use_mask);

	ClassDB::bind_method(D_METHOD("set_model_meshs", "value"), &ModelPreset::set_model_meshs);
	ClassDB::bind_method(D_METHOD("get_model_meshs"), &ModelPreset::get_model_meshs);

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_mask"), "set_use_mask", "is_use_mask");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "model_meshs", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::OBJECT) + "/" + String::num_int64(PROPERTY_HINT_RESOURCE_TYPE) + ":ModelMesh"), "set_model_meshs", "get_model_meshs");

}

ModelPreset::ModelPreset() {
	use_mask = false;
	model_meshs.resize(1);
}
ModelPreset::~ModelPreset() {

}

void ModelPreset::set_use_mask(const bool& value) {
	use_mask = value;
	if (use_mask == true)
	{
		model_meshs.resize(64);
	}
	else {
		model_meshs.resize(1);
	}
	notify_property_list_changed();
}

bool ModelPreset::is_use_mask() const {
	return use_mask;
}

void ModelPreset::set_model_meshs(const Array& value) {
	model_meshs = value;
	if (use_mask == true)
	{
		model_meshs.resize(64);
	}
	else {
		model_meshs.resize(1);
	}
	notify_property_list_changed();
}

Array ModelPreset::get_model_meshs() const {
	return model_meshs;
}