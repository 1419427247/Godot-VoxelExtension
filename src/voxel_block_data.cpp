#include "voxel_block_data.h"

void VoxelBlockData::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_size", "value"), &VoxelBlockData::set_size);
	ClassDB::bind_method(D_METHOD("get_size"), &VoxelBlockData::get_size);

	//ClassDB::bind_method(D_METHOD("set_voxels", "value"), &VoxelBlockData::set_voxel);
	//ClassDB::bind_method(D_METHOD("get_voxels"), &VoxelBlockData::get_voxels);

	//ClassDB::bind_method(D_METHOD("fill", "voxel"), &VoxelBlockData::fill);
	//ClassDB::bind_method(D_METHOD("is_filled"), &VoxelBlockData::is_filled);

	//ClassDB::bind_method(D_METHOD("build_mesh", "presets_data", "mesh_arrays", "position", "voxel"), &VoxelBlockData::build_mesh);
	//ClassDB::bind_method(D_METHOD("build_device", "device_preset", "position", "voxel"), &VoxelBlockData::build_device);

	//ClassDB::bind_method(D_METHOD("get_voxel_type", "value"), &VoxelBlockData::get_voxel_type);
	//ClassDB::bind_method(D_METHOD("get_voxel_id"), &VoxelBlockData::get_voxel_id);

	//BIND_VIRTUAL_METHOD(VoxelBlockData, set_size);
	//BIND_VIRTUAL_METHOD(VoxelBlockData, get_size);

	//BIND_VIRTUAL_METHOD(VoxelBlockData, set_voxels);
	//BIND_VIRTUAL_METHOD(VoxelBlockData, get_voxels);

	//BIND_VIRTUAL_METHOD(VoxelBlockData, set_voxel);
	//BIND_VIRTUAL_METHOD(VoxelBlockData, get_voxel);

	//BIND_VIRTUAL_METHOD(VoxelBlockData, fill);
	//BIND_VIRTUAL_METHOD(VoxelBlockData, is_filled);
	//
	//BIND_VIRTUAL_METHOD(VoxelBlockData, build_mesh);
	//BIND_VIRTUAL_METHOD(VoxelBlockData, build_device);

	//BIND_VIRTUAL_METHOD(VoxelBlockData, get_voxel_type);
	//BIND_VIRTUAL_METHOD(VoxelBlockData, get_voxel_id);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "size"), "set_size", "get_size");

	BIND_ENUM_CONSTANT(EMPTY);
	BIND_ENUM_CONSTANT(BASICS);
	BIND_ENUM_CONSTANT(MODEL);
	BIND_ENUM_CONSTANT(DEVICE);
}

VoxelBlockData::VoxelBlockData()
{
}

VoxelBlockData::~VoxelBlockData()
{
}

void VoxelBlockData::set_size(const Vector3i& value) {
	ERR_FAIL_COND_MSG(value.x <= 0 || value.y <= 0 || value.z <= 0, "The container size is an invalid value");
	size = value;
}

Vector3i VoxelBlockData::get_size() const {
	return size;
}

void VoxelBlockData::set_voxels(const PackedByteArray& value)
{

}

PackedByteArray VoxelBlockData::get_voxels() const
{
	return PackedByteArray();
}

void VoxelBlockData::set_voxel(const Vector3i& position, const Voxel& value)
{

}

Voxel VoxelBlockData::get_voxel(const Vector3i& position) const
{
	return EMPTY_VOXEL;
}

void VoxelBlockData::fill(const Voxel& voxel) {

}


bool VoxelBlockData::is_filled(const Voxel& voxel) const {
	return false;
}

void VoxelBlockData::build_mesh(const Ref<PresetsData>& presets_data, const Array& mesh_arrays, const Vector3i& position, const Voxel& voxel)
{
}

Variant VoxelBlockData::build_device(const Ref<DevicePreset>& device_preset, Vector3i& position, const Voxel& voxel)
{
	return nullptr;
}

int VoxelBlockData::get_voxel_type(const Voxel& value)
{
	return 0;
}

int VoxelBlockData::get_voxel_id(const Voxel& value)
{
	return 0;
}

Vector3 VoxelBlockData::rotate_vertex(const Vector3& vertex, const Vector3i& rotation)
{
	Vector3 result = vertex;
	result = result.rotated(Vector3(0, 1, 0), UtilityFunctions::deg_to_rad(rotation.y));
	result = result.rotated(Vector3(1, 0, 0), UtilityFunctions::deg_to_rad(rotation.x));
	result = result.rotated(Vector3(0, 0, 1), UtilityFunctions::deg_to_rad(rotation.z));
	return result;
}

Vector3 VoxelBlockData::get_triangle_normal(const Vector3& a, const Vector3& b, const Vector3& c)
{
	return (c - a).cross(b - a);
}
