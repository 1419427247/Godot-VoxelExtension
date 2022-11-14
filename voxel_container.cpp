#include "voxel_container.h"

void VoxelContainer::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_presets_data", "value"), &VoxelContainer::set_presets_data);
	ClassDB::bind_method(D_METHOD("get_presets_data"), &VoxelContainer::get_presets_data);

	ClassDB::bind_method(D_METHOD("set_block_size", "value"), &VoxelContainer::set_block_size);
	ClassDB::bind_method(D_METHOD("get_block_size"), &VoxelContainer::get_block_size);

	ClassDB::bind_method(D_METHOD("set_isolated", "value"), &VoxelContainer::set_isolated);
	ClassDB::bind_method(D_METHOD("is_isolated"), &VoxelContainer::is_isolated);

	ClassDB::bind_method(D_METHOD("copy", "from", "to"), &VoxelContainer::copy);
	ClassDB::bind_method(D_METHOD("paste", "voxel_container_data", "position", "direction"), &VoxelContainer::paste);
	ClassDB::bind_method(D_METHOD("fill", "voxel", "from", "to"), &VoxelContainer::fill);

	ClassDB::bind_static_method("VoxelContainer", D_METHOD("get_voxel_direction", "direction", "rotation"), &VoxelContainer::get_voxel_direction);
	ClassDB::bind_static_method("VoxelContainer", D_METHOD("get_voxel_type", "value"), &VoxelContainer::get_voxel_type);
	ClassDB::bind_static_method("VoxelContainer", D_METHOD("get_voxel_id", "value"), &VoxelContainer::get_voxel_id);
	ClassDB::bind_static_method("VoxelContainer", D_METHOD("get_voxel_rotation", "value"), &VoxelContainer::get_voxel_rotation);
	ClassDB::bind_static_method("VoxelContainer", D_METHOD("get_voxel_flag", "value"), &VoxelContainer::get_voxel_flag);

	ClassDB::bind_static_method("VoxelContainer", D_METHOD("empty_voxel"), &VoxelContainer::empty_voxel);
	ClassDB::bind_static_method("VoxelContainer", D_METHOD("basics_voxel", "id", "rotation", "flag"), &VoxelContainer::basics_voxel, Vector3i(), 0);
	ClassDB::bind_static_method("VoxelContainer", D_METHOD("model_voxel", "id", "rotation", "flag"), &VoxelContainer::model_voxel, Vector3i(), 0);
	ClassDB::bind_static_method("VoxelContainer", D_METHOD("device_voxel", "id", "rotation", "flag"), &VoxelContainer::device_voxel, Vector3i(), 0);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "presets_data", PROPERTY_HINT_RESOURCE_TYPE, "PresetsData"), "set_presets_data", "get_presets_data");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "block_size"), "set_block_size", "get_block_size");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "isolated"), "set_isolated", "is_isolated");
}

VoxelContainer::VoxelContainer()
{
	block_size = Vector3i(8, 8, 8);
	isolated = false;
}

VoxelContainer::~VoxelContainer()
{
}

void VoxelContainer::set_presets_data(const Ref<PresetsData>& value)
{
	presets_data = value;
}

Ref<PresetsData> VoxelContainer::get_presets_data() const
{
	return presets_data;
}

void VoxelContainer::set_block_size(const Vector3i& value)
{
	ERR_FAIL_COND_MSG(value.x <= 0 || value.y <= 0 || value.z <= 0, "The chunk size is an invalid value");
	block_size = value;
}

Vector3i VoxelContainer::get_block_size() const
{
	return block_size;
}


void VoxelContainer::set_isolated(const bool& value)
{
	isolated = value;
}

bool VoxelContainer::is_isolated() const
{
	return isolated;
}

void VoxelContainer::set_voxel(const Vector3i& position, const Voxel& value)
{
}

Voxel VoxelContainer::get_voxel(const Vector3i& position) const
{
	return EMPTY_VOXEL;
}

Vector3i VoxelContainer::get_block_key(const Vector3i& position) const
{
	return Vector3i();
}

VoxelContainerData* VoxelContainer::copy(const Vector3i& from, const Vector3i& to)
{
	VoxelContainerData* replica_voxel_data = memnew(VoxelContainerData);
	Vector3i block_size = Vector3i(abs(from.x - to.x) + 1, abs(from.y - to.y) + 1, abs(from.z - to.z) + 1);
	replica_voxel_data->set_container_size(block_size);
	int step_x = from.x > to.x ? -1 : 1;
	int step_y = from.y > to.y ? -1 : 1;
	int step_z = from.z > to.z ? -1 : 1;
	for (int x = from.x; x != to.x + step_x; x += step_x)
	{
		for (int y = from.y; y != to.y + step_y; y += step_y)
		{
			for (int z = from.z; z != to.z + step_z; z += step_z)
			{
				Vector3i position = Vector3i(x, y, z);
				Vector3i replica_position = Vector3i(abs(x - from.x), abs(y - from.y), abs(z - from.z));
				Voxel voxel = get_voxel(position);
				replica_voxel_data->set_voxel(replica_position, voxel);
			}
		}
	}
	return replica_voxel_data;
}

void VoxelContainer::paste(const Ref<VoxelContainerData>& voxel_container_data, const Vector3i& position, const Vector3i& direction)
{
	ERR_FAIL_COND_MSG((direction.x != 1 && direction.x == -1) || (direction.y != 1 && direction.y == -1) || (direction.z != 1 && direction.z == -1), "Invalid direction");
	for (int x = position.x; x != position.x + voxel_container_data->get_container_size().x * direction.x; x += direction.x)
	{
		for (int y = position.y; y != position.y + voxel_container_data->get_container_size().y * direction.y; y += direction.y)
		{
			for (int z = position.z; z != position.z + voxel_container_data->get_container_size().z * direction.z; z += direction.z)
			{
				Vector3i position = Vector3i(x, y, z);
				set_voxel(position, get_voxel(Vector3i(abs(x - position.x), abs(y - position.y), abs(z - position.z))));
			}
		}
	}
}

void VoxelContainer::fill(const Voxel& voxel, const Vector3i& from, const Vector3i& to) {
	int step_x = from.x > to.x ? -1 : 1;
	int step_y = from.y > to.y ? -1 : 1;
	int step_z = from.z > to.z ? -1 : 1;
	for (int x = from.x; x != to.x + step_x; x += step_x)
	{
		for (int y = from.y; y != to.y + step_y; y += step_y)
		{
			for (int z = from.z; z != to.z + step_z; z += step_z)
			{
				Vector3i position = Vector3i(x, y, z);
				Voxel voxel = get_voxel(position);
				set_voxel(position, voxel);
			}
		}
	}
}


Vector3i VoxelContainer::get_voxel_direction(const int& direction, const Vector3i& rotation)
{
	static Vector3 memorandum[6][24 * 24 * 24] = { Vector3() };
	Vector3* result = &memorandum[direction][rotation.x / 15 * 24 * 24 + rotation.y / 15 * 24 + rotation.z / 15];
	if (*result == Vector3i())
	{
		*result = DIRCTIONS[direction];
		result->rotate(Vector3(0, 1, 0), UtilityFunctions::deg_to_rad(rotation.y));
		result->rotate(Vector3(1, 0, 0), UtilityFunctions::deg_to_rad(rotation.x));
		result->rotate(Vector3(0, 0, 1), UtilityFunctions::deg_to_rad(rotation.z));
	}
	return Vector3i(*result);
}

//Vector3i VoxelContainer::get_voxel_direction(const Vector3i& direction, const Vector3i& rotation)
//{
//	Vector3 result = direction;
//	result = result.rotated(Vector3(0, 1, 0), UtilityFunctions::deg_to_rad(rotation.y));
//	result = result.rotated(Vector3(1, 0, 0), UtilityFunctions::deg_to_rad(rotation.x));
//	result = result.rotated(Vector3(0, 0, 1), UtilityFunctions::deg_to_rad(rotation.z));
//	return Vector3i(result);
//}

int VoxelContainer::get_voxel_type(const Voxel& value)
{
	return value >> 30;
}

int VoxelContainer::get_voxel_id(const Voxel& value)
{
	return (value << 2) >> 22;
}

Vector3i VoxelContainer::get_voxel_rotation(const Voxel& value)
{
	return Vector3i((value << 12) >> 27, (value << 17) >> 27, (value & (0b11111 << 22) >> 27)) * 15;
}

int VoxelContainer::get_voxel_flag(const Voxel& value)
{
	return (value << 27) >> 27;
}

Voxel VoxelContainer::empty_voxel()
{
	return EMPTY_VOXEL;
}

Voxel VoxelContainer::basics_voxel(const int& id, const Vector3i& rotation, const int& flag)
{
	return BASICS_VOXEL(id, rotation, flag);
}

Voxel VoxelContainer::model_voxel(const int& id, const Vector3i& rotation, const int& flag)
{
	return MODEL_VOXEL(id, rotation, flag);
}

Voxel VoxelContainer::device_voxel(const int& id, const Vector3i& rotation, const int& flag)
{
	return DEVICE_VOXEL(id, rotation, flag);
}