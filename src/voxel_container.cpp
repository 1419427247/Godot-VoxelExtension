#include "voxel_container.h"
#include "voxel_block_data.h"

void VoxelContainer::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_presets_data", "value"), &VoxelContainer::set_presets_data);
	ClassDB::bind_method(D_METHOD("get_presets_data"), &VoxelContainer::get_presets_data);

	ClassDB::bind_method(D_METHOD("set_voxel_block_size", "value"), &VoxelContainer::set_voxel_block_size);
	ClassDB::bind_method(D_METHOD("get_voxel_block_size"), &VoxelContainer::get_voxel_block_size);

	ClassDB::bind_method(D_METHOD("set_isolated", "value"), &VoxelContainer::set_isolated);
	ClassDB::bind_method(D_METHOD("is_isolated"), &VoxelContainer::is_isolated);

	ClassDB::bind_method(D_METHOD("set_voxel_block_data", "key", "value"), &VoxelContainer::set_voxel_block_data);
	ClassDB::bind_method(D_METHOD("get_voxel_block_data", "key"), &VoxelContainer::get_voxel_block_data);

	ClassDB::bind_method(D_METHOD("set_voxel", "position", "value"), &VoxelContainer::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel", "position"), &VoxelContainer::get_voxel);

	ClassDB::bind_method(D_METHOD("set_custom_data", "position", "value"), &VoxelContainer::set_custom_data);
	ClassDB::bind_method(D_METHOD("get_custom_data", "position"), &VoxelContainer::get_custom_data);

	ClassDB::bind_method(D_METHOD("get_voxel_block_key", "position"), &VoxelContainer::get_voxel_block_key);

	//ClassDB::bind_method(D_METHOD("copy", "from", "to"), &VoxelContainer::copy);
	//ClassDB::bind_method(D_METHOD("paste", "voxel_block_data", "position", "direction"), &VoxelContainer::paste);
	ClassDB::bind_method(D_METHOD("fill", "voxel", "from", "to"), &VoxelContainer::fill);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "presets_data", PROPERTY_HINT_RESOURCE_TYPE, "PresetsData"), "set_presets_data", "get_presets_data");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "voxel_block_size"), "set_voxel_block_size", "get_voxel_block_size");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "isolated"), "set_isolated", "is_isolated");
}

VoxelContainer::VoxelContainer()
{
	set_voxel_block_size(Vector3i(8, 8, 8));
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

void VoxelContainer::set_voxel_block_size(const Vector3i& value)
{
	ERR_FAIL_COND_MSG(value.x <= 0 || value.y <= 0 || value.z <= 0, "The chunk size is an invalid value");
	voxel_block_size = value;
}

Vector3i VoxelContainer::get_voxel_block_size() const
{
	return voxel_block_size;
}

void VoxelContainer::set_isolated(const bool& value)
{
	isolated = value;
}

bool VoxelContainer::is_isolated() const
{
	return isolated;
}

void VoxelContainer::set_voxel_block_data(const Vector3i& key, const Ref<VoxelBlockData>& value) {
	Ref<VoxelBlockData> voxel_block_data;
	if (voxel_block_datas.has(key) == true)
	{
		voxel_block_data = voxel_block_datas.get(key, nullptr);
		voxel_block_data->set_voxel_container(nullptr);
	}
	if (value.is_null() == false)
	{
		voxel_block_data = value;
		voxel_block_data->set_voxel_container(this);
		ERR_FAIL_COND_MSG(voxel_block_data->get_size() != voxel_block_size, "The VoxelBlockData.size() is different from the VoxelContainer setting");
	}
	voxel_block_data->set_key(key);
	voxel_block_datas[key] = value;
}

Ref<VoxelBlockData> VoxelContainer::get_voxel_block_data(const Vector3i& key) const {
	return voxel_block_datas.get(key, nullptr);
}

void VoxelContainer::set_voxel(const Vector3i& position, const Voxel& value)
{
	Vector3i key = get_voxel_block_key(position);
	Ref<VoxelBlockData> voxel_block_data = voxel_block_datas.get(key, nullptr);
	if (voxel_block_data != nullptr)
	{
		voxel_block_data->set_voxel({
			position.x < 0 ? voxel_block_size.x - ((-1 * position.x - 1) % voxel_block_size.x) - 1 : (position.x % voxel_block_size.x),
			position.y < 0 ? voxel_block_size.y - ((-1 * position.y - 1) % voxel_block_size.y) - 1 : (position.y % voxel_block_size.y),
			position.z < 0 ? voxel_block_size.z - ((-1 * position.z - 1) % voxel_block_size.z) - 1 : (position.z % voxel_block_size.z)
			}, value);
	}
}

Voxel VoxelContainer::get_voxel(const Vector3i& position) const
{
	Vector3i key = get_voxel_block_key(position);
	Ref<VoxelBlockData> voxel_block_data = voxel_block_datas.get(key, nullptr);
	if (voxel_block_data != nullptr)
	{
		return voxel_block_data->get_voxel({
			position.x < 0 ? voxel_block_size.x - ((-1 * position.x - 1) % voxel_block_size.x) - 1 : (position.x % voxel_block_size.x),
			position.y < 0 ? voxel_block_size.y - ((-1 * position.y - 1) % voxel_block_size.y) - 1 : (position.y % voxel_block_size.y),
			position.z < 0 ? voxel_block_size.z - ((-1 * position.z - 1) % voxel_block_size.z) - 1 : (position.z % voxel_block_size.z)
			});
	}
	return EMPTY_VOXEL;
}

void VoxelContainer::set_custom_data(const Vector3i& position, const Variant& value)
{
	Vector3i key = get_voxel_block_key(position);
	Ref<VoxelBlockData> voxel_block_data = voxel_block_datas.get(key, nullptr);
	if (voxel_block_data != nullptr)
	{
		voxel_block_data->set_custom_data({
			position.x < 0 ? voxel_block_size.x - ((-1 * position.x - 1) % voxel_block_size.x) - 1 : (position.x % voxel_block_size.x),
			position.y < 0 ? voxel_block_size.y - ((-1 * position.y - 1) % voxel_block_size.y) - 1 : (position.y % voxel_block_size.y),
			position.z < 0 ? voxel_block_size.z - ((-1 * position.z - 1) % voxel_block_size.z) - 1 : (position.z % voxel_block_size.z)
			}, value);
	}
}

Variant VoxelContainer::get_custom_data(const Vector3i& position)
{
	Vector3i key = get_voxel_block_key(position);
	Ref<VoxelBlockData> voxel_block_data = voxel_block_datas.get(key, nullptr);
	if (voxel_block_data != nullptr)
	{
		return voxel_block_data->get_custom_data({
			position.x < 0 ? voxel_block_size.x - ((-1 * position.x - 1) % voxel_block_size.x) - 1 : (position.x % voxel_block_size.x),
			position.y < 0 ? voxel_block_size.y - ((-1 * position.y - 1) % voxel_block_size.y) - 1 : (position.y % voxel_block_size.y),
			position.z < 0 ? voxel_block_size.z - ((-1 * position.z - 1) % voxel_block_size.z) - 1 : (position.z % voxel_block_size.z)
			});
	}
	return nullptr;
}

Vector3i VoxelContainer::get_voxel_block_key(const Vector3i& position) const
{
	return Vector3i(
		position.x < 0 ? (position.x + 1) / voxel_block_size.x - 1 : position.x / voxel_block_size.x,
		position.y < 0 ? (position.y + 1) / voxel_block_size.y - 1 : position.y / voxel_block_size.y,
		position.z < 0 ? (position.z + 1) / voxel_block_size.z - 1 : position.z / voxel_block_size.z
	);
}

VoxelBlockData* VoxelContainer::copy(const Vector3i& from, const Vector3i& to)
{
	VoxelBlockData* replica_voxel_data = memnew(VoxelBlockData);
	Vector3i block_size = Vector3i(abs(from.x - to.x) + 1, abs(from.y - to.y) + 1, abs(from.z - to.z) + 1);
	replica_voxel_data->set_size(block_size);
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

void VoxelContainer::paste(const Ref<VoxelBlockData>& voxel_block_data, const Vector3i& position, const Vector3i& direction)
{
	ERR_FAIL_COND_MSG((direction.x != 1 && direction.x == -1) || (direction.y != 1 && direction.y == -1) || (direction.z != 1 && direction.z == -1), "Invalid direction");
	for (int x = position.x; x != position.x + voxel_block_data->get_size().x * direction.x; x += direction.x)
	{
		for (int y = position.y; y != position.y + voxel_block_data->get_size().y * direction.y; y += direction.y)
		{
			for (int z = position.z; z != position.z + voxel_block_data->get_size().z * direction.z; z += direction.z)
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