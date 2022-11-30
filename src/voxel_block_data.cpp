#include "voxel_block_data.h"

void VoxelBlockData::_bind_methods()
{
	//ClassDB::bind_method(D_METHOD("set_size", "value"), &VoxelBlockData::set_key);
	ClassDB::bind_method(D_METHOD("get_key"), &VoxelBlockData::get_key);

	ClassDB::bind_method(D_METHOD("set_size", "value"), &VoxelBlockData::set_size);
	ClassDB::bind_method(D_METHOD("get_size"), &VoxelBlockData::get_size);

	ClassDB::bind_method(D_METHOD("set_presets_data", "value"), &VoxelBlockData::set_presets_data);
	ClassDB::bind_method(D_METHOD("get_presets_data"), &VoxelBlockData::get_presets_data);

	ClassDB::bind_method(D_METHOD("get_voxel_container"), &VoxelBlockData::get_voxel_container);

	ClassDB::bind_method(D_METHOD("set_use_custom_datas"), &VoxelBlockData::set_use_custom_datas);
	ClassDB::bind_method(D_METHOD("is_use_custom_datas"), &VoxelBlockData::is_use_custom_datas);

	ClassDB::bind_method(D_METHOD("set_custom_datas"), &VoxelBlockData::set_custom_datas);
	ClassDB::bind_method(D_METHOD("get_custom_datas"), &VoxelBlockData::get_custom_datas);

	ClassDB::bind_method(D_METHOD("get_devices"), &VoxelBlockData::get_devices);

	ClassDB::bind_method(D_METHOD("set_voxels", "value"), &VoxelBlockData::set_voxels);
	ClassDB::bind_method(D_METHOD("get_voxels"), &VoxelBlockData::get_voxels);

	ClassDB::bind_method(D_METHOD("set_voxel", "position", "value"), &VoxelBlockData::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel", "position"), &VoxelBlockData::get_voxel);

	ClassDB::bind_method(D_METHOD("fill", "voxel"), &VoxelBlockData::fill);
	ClassDB::bind_method(D_METHOD("is_filled"), &VoxelBlockData::is_filled);

	ClassDB::bind_method(D_METHOD("generate_mesh", "filter"), &VoxelBlockData::generate_mesh, 0b1);
	ClassDB::bind_method(D_METHOD("generate_collider", "filter"), &VoxelBlockData::generate_collider, 0b1);
	ClassDB::bind_method(D_METHOD("generate_device"), &VoxelBlockData::generate_device, 0b1);

	ClassDB::bind_static_method("VoxelBlockData", D_METHOD("translate_point_to_voxel_block_coordinatet", "global_transform", "point"), &VoxelBlockData::translate_point_to_voxel_block_coordinatet);
	ClassDB::bind_static_method("VoxelBlockData", D_METHOD("translate_normal_to_voxel_block_coordinatet", "global_transform", "normal"), &VoxelBlockData::translate_normal_to_voxel_block_coordinatet);
	ClassDB::bind_static_method("VoxelBlockData", D_METHOD("get_voxel_position", "global_transform", "point", "normal"), &VoxelBlockData::get_voxel_position);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "size"), "set_size", "get_size");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "presets_data", PROPERTY_HINT_RESOURCE_TYPE, "PresetsData"), "set_presets_data", "get_presets_data");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "use_custom_datas"), "set_use_custom_datas", "is_use_custom_datas");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "custom_datas"), "set_custom_datas", "get_custom_datas");
	//ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "custom_datas", PROPERTY_HINT_ARRAY_TYPE, String::num_int64(Variant::OBJECT) + "/" + String::num_int64(PROPERTY_HINT_RESOURCE_TYPE) + ":Resource"), "set_custom_datas", "get_custom_datas");

	BIND_ENUM_CONSTANT(EMPTY);
	BIND_ENUM_CONSTANT(BASICS);
	BIND_ENUM_CONSTANT(MODEL);
	BIND_ENUM_CONSTANT(DEVICE);
}

void VoxelBlockData::_build_basics_mesh(const Ref<PresetsData>& presets_data, const Ref<BasicsPreset>& basics_preset, const Voxel& voxel, const Array& mesh_arrays, const Vector3i& position) {

}

void VoxelBlockData::_build_model_mesh(const Ref<PresetsData>& presets_data, const Ref<ModelPreset>& model_preset, const Voxel& voxel, const Array& mesh_arrays, const Vector3i& position) {

}

Variant VoxelBlockData::_build_device(const Ref<DevicePreset>& device_preset, const Vector3i& position, const Voxel& voxel)
{
	return nullptr;
}

int VoxelBlockData::_get_voxel_type(const Voxel& value)
{
	return 0;
}

int VoxelBlockData::_get_voxel_id(const Voxel& value)
{
	return 0;
}

VoxelBlockData::VoxelBlockData()
{
	voxel_container = nullptr;
	set_key(Vector3i(0, 0, 0));
	set_size(Vector3i(8, 8, 8));
	set_use_custom_datas(false);
}

VoxelBlockData::~VoxelBlockData()
{
	TypedArray<Device> device_array = get_devices();
	for (int i = 0; i < device_array.size(); i++)
	{
		cast_to<Device>(device_array[i])->queue_free();
	}
}

void VoxelBlockData::set_key(const Vector3i& value) {
	key = value;
}

Vector3i VoxelBlockData::get_key() const {
	return key;
}

void VoxelBlockData::set_size(const Vector3i& value) {
	ERR_FAIL_COND_MSG(value.x <= 0 || value.y <= 0 || value.z <= 0, "The container size is an invalid value");
	if (voxel_container != nullptr)
	{
		return;
	}
	size = value;
}

Vector3i VoxelBlockData::get_size() const {
	return size;
}

void VoxelBlockData::set_presets_data(const Ref<PresetsData>& value) {
	presets_data = value;
}

Ref<PresetsData> VoxelBlockData::get_presets_data() const {
	if (presets_data.is_null())
	{
		if (voxel_container != nullptr)
		{
			return voxel_container->get_presets_data();
		}
	}
	return presets_data;
}

void VoxelBlockData::set_voxel_container(Variant value)
{
	voxel_container = cast_to<VoxelContainer>(value);
}

Variant VoxelBlockData::get_voxel_container() const
{
	return voxel_container;
}

void VoxelBlockData::set_use_custom_datas(const bool& value) {
	use_custom_datas = value;
	if (use_custom_datas == true)
	{
		custom_datas.resize(size.x * size.y * size.z);
	}
	else {
		custom_datas.clear();
	}
	notify_property_list_changed();
}
bool VoxelBlockData::is_use_custom_datas() {
	return use_custom_datas;
}

void VoxelBlockData::set_custom_datas(const Array& value) {
	if (use_custom_datas == true)
	{
		custom_datas = value;
		custom_datas.resize(size.x * size.y * size.z);
	}
}

Array VoxelBlockData::get_custom_datas() const {
	return custom_datas;
}

TypedArray<Device> VoxelBlockData::get_devices() const {
	return devices.values();
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

void VoxelBlockData::set_custom_data(const Vector3i& position, const Variant& value) {
	if (use_custom_datas == false) {
		return;
	}
	if (position.x >= 0 && position.x < size.x &&
		position.y >= 0 && position.y < size.y &&
		position.z >= 0 && position.z < size.z)
	{
		int index = ((position.x * size.y * size.z) + (position.y * size.z) + position.z);
		custom_datas[index] = value;
	}
	else {
		if (voxel_container != nullptr)
		{
			if (voxel_container->is_isolated() == false) {
				voxel_container->set_custom_data(position + key * size, value);
			}
		}
	}
}


Variant VoxelBlockData::get_custom_data(const Vector3i& position)
{
	if (use_custom_datas == false) {
		return nullptr;
	}
	if (position.x >= 0 && position.x < size.x &&
		position.y >= 0 && position.y < size.y &&
		position.z >= 0 && position.z < size.z)
	{
		int index = ((position.x * size.y * size.z) + (position.y * size.z) + position.z);
		return custom_datas[index];
	}
	if (voxel_container != nullptr)
	{
		if (voxel_container->is_isolated() == false) {
			return voxel_container->get_custom_data(position + key * size);
		}
	}
	return nullptr;
}

void VoxelBlockData::fill(const Voxel& voxel) {

}


bool VoxelBlockData::is_filled(const Voxel& voxel) const {
	return false;
}

ArrayMesh* VoxelBlockData::generate_mesh(const int& filter)
{
	Array mesh_arrays;
	Ref<PresetsData> presets_data = get_presets_data();
	ERR_FAIL_NULL_V(presets_data, nullptr);

	TypedArray<Material> materials = presets_data->get_materials();
	TypedArray<BasicsPreset> basics_presets = presets_data->get_basics_presets();
	TypedArray<ModelPreset> model_presets = presets_data->get_model_presets();

	mesh_arrays.resize(materials.size());
	for (int i = 0; i < mesh_arrays.size(); i++)
	{
		Array arrays;
		arrays.resize(Mesh::ARRAY_MAX);
		arrays[Mesh::ARRAY_VERTEX] = Array();
		arrays[Mesh::ARRAY_TEX_UV] = Array();
		arrays[Mesh::ARRAY_NORMAL] = Array();
		mesh_arrays[i] = arrays;
	}

	for (int x = 0; x < size.x; x++)
	{
		for (int y = 0; y < size.y; y++)
		{
			for (int z = 0; z < size.z; z++)
			{
				Vector3i position = Vector3i(x, y, z);
				Voxel voxel = get_voxel(position);

				int type = _get_voxel_type(voxel);
				int id = _get_voxel_id(voxel);

				switch (type)
				{
				case VoxelBlockData::BASICS: {
					ERR_FAIL_INDEX_V(id, basics_presets.size(), nullptr);
					Ref<BasicsPreset> basics_preset = basics_presets[id];
					if ((filter & basics_preset->get_filter()) == 0)
					{
						continue;
					}
					_build_basics_mesh(presets_data, basics_preset, voxel, mesh_arrays, position);
					break;
				}
				case VoxelBlockData::MODEL:
				{
					ERR_FAIL_INDEX_V(id, model_presets.size(), nullptr);
					Ref<ModelPreset> model_preset = model_presets[id];
					if ((filter & model_preset->get_filter()) == 0)
					{
						continue;
					}
					_build_model_mesh(presets_data, model_preset, voxel, mesh_arrays, position);
					break;
				}
				}
			}
		}
	}
	ArrayMesh* result = memnew(ArrayMesh);
	for (int i = 0; i < mesh_arrays.size(); i++)
	{
		Array arrays = mesh_arrays[i];
		Array vertex_array = (Array)arrays[ArrayMesh::ARRAY_VERTEX];
		Array normal_array = (Array)arrays[ArrayMesh::ARRAY_NORMAL];
		Array tex_uv_array = (Array)arrays[ArrayMesh::ARRAY_TEX_UV];
		if (vertex_array.size() > 0) {
			arrays[ArrayMesh::ARRAY_VERTEX] = PackedVector3Array(vertex_array);
			arrays[ArrayMesh::ARRAY_NORMAL] = PackedVector3Array(normal_array);
			arrays[ArrayMesh::ARRAY_TEX_UV] = PackedVector2Array(tex_uv_array);
			result->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, arrays);
			result->surface_set_material(result->get_surface_count() - 1, materials[i]);
		}
	}
	return result;
}

ConcavePolygonShape3D* VoxelBlockData::generate_collider(const int& filter)
{
	Ref<PresetsData> presets_data = get_presets_data();
	ERR_FAIL_NULL_V(presets_data, nullptr);

	Array basics_presets = presets_data->get_basics_presets();
	Array model_presets = presets_data->get_model_presets();
	Array device_presets = presets_data->get_device_presets();

	PackedVector3Array collider_faces;
	class Area
	{
	private:
		bool* flags;
	public:
		Vector3i size;
		Area(Vector3i size) {

			this->flags = new bool[(size.x + 1) * (size.y + 1) * (size.z + 1)]();
			this->size = size + Vector3i(1, 1, 1);
		}
		~Area() {
			delete[] this->flags;
		}
		void set_flag(int x, int y, int z, bool v) {
			flags[((x * size.y * size.z) + (y * size.z) + z)] = v;
		}
		bool get_flag(int x, int y, int z) const {
			return flags[((x * size.y * size.z) + (y * size.z) + z)];
		}
	};

	class Box
	{
		Area* area;
	public:
		Vector3i from;
		Vector3i to;
		Box() {

		}
		Box(const Vector3i& from, const Vector3i& to, Area* area) {
			this->from = from;
			this->to = to;
			this->area = area;
		}
		void increase() {
			for (int i = from.x; i < area->size.x; i++)
			{
				Box box = Box(Vector3i(to.x + 1, from.y, from.z), Vector3i(to.x + 1, to.y, to.z), area);
				if (box.is_full() == false)
				{
					break;
				}
				box.set_flag(false);
				to.x++;
			}
			for (int i = from.y; i < area->size.y; i++)
			{
				Box box(Vector3i(from.x, to.y + 1, from.z), Vector3i(to.x, to.y + 1, to.z), area);
				if (box.is_full() == false)
				{
					break;
				}
				box.set_flag(false);
				to.y++;
			}
			for (int i = from.z; i < area->size.z; i++)
			{
				Box box(Vector3i(from.x, from.y, to.z + 1), Vector3i(to.x, to.y, to.z + 1), area);
				if (box.is_full() == false)
				{
					break;
				}
				box.set_flag(false);
				to.z++;
			}
		}

		void set_flag(const bool& value) {
			for (int x = from.x; x <= to.x; x++)
			{
				for (int y = from.y; y <= to.y; y++)
				{
					for (int z = from.z; z <= to.z; z++)
					{
						area->set_flag(x, y, z, value);
					}
				}
			}
		}

		bool is_full() {
			for (int x = from.x; x <= to.x; x++)
			{
				for (int y = from.y; y <= to.y; y++)
				{
					for (int z = from.z; z <= to.z; z++)
					{
						if (area->get_flag(x, y, z) == false)
						{
							return false;
						}
					}
				}
			}
			return true;
		}
	};

	Area area = Area(size);
	List<Box> boxs;

	for (int x = 0; x < size.x; x++)
	{
		for (int y = 0; y < size.y; y++)
		{
			for (int z = 0; z < size.z; z++)
			{
				Vector3i position = Vector3i(x, y, z);
				Voxel voxel = get_voxel(position);
				int type = _get_voxel_type(voxel);
				int id = _get_voxel_id(voxel);
				Ref<Preset> preset;
				switch (type)
				{
				case VoxelBlockData::EMPTY:
				{
					continue;
				}
				case VoxelBlockData::BASICS:
				{
					ERR_FAIL_INDEX_V(id, basics_presets.size(), nullptr);
					preset = basics_presets[id];
					break;
				}
				case VoxelBlockData::MODEL:
				{
					ERR_FAIL_INDEX_V(id, model_presets.size(), nullptr);
					preset = model_presets[id];
					break;
				}
				case VoxelBlockData::DEVICE:
				{
					ERR_FAIL_INDEX_V(id, device_presets.size(), nullptr);
					preset = device_presets[id];
				}
				}
				ERR_FAIL_NULL_V_MSG(preset, nullptr, "The preset is null [type = " + String::num_int64(type) + ",id = " + String::num_int64(id) + "]");
				if ((filter & preset->get_filter()) == 0)
				{
					continue;
				}
				area.set_flag(x, y, z, true);
			}
		}
	}
	for (int x = 0; x < size.x; x++)
	{
		for (int y = 0; y < size.y; y++)
		{
			for (int z = 0; z < size.z; z++)
			{
				if (area.get_flag(x, y, z) == false)
				{
					continue;
				}
				Box box = Box(Vector3i(x, y, z), Vector3i(x, y, z), &area);
				box.increase();
				boxs.push_back(box);
			}
		}
	}

	for (int i = 0; i < boxs.size(); i++)
	{
		Box box = boxs[i];

		Vector3 vertexs[] = {
			Vector3(box.to.x + 0.5,box.from.y + -0.5,box.from.z + -0.5),
			Vector3(box.to.x + 0.5,box.to.y + 0.5,box.from.z + -0.5),
			Vector3(box.from.x + -0.5,box.to.y + 0.5,box.from.z + -0.5),
			Vector3(box.from.x + -0.5,box.from.y + -0.5,box.from.z + -0.5),
			Vector3(box.to.x + 0.5,box.from.y + -0.5,box.to.z + 0.5),
			Vector3(box.to.x + 0.5,box.to.y + 0.5,box.to.z + 0.5),
			Vector3(box.from.x + -0.5,box.to.y + 0.5,box.to.z + 0.5),
			Vector3(box.from.x + -0.5,box.from.y + -0.5, box.to.z + 0.5),
		};
		collider_faces.push_back(vertexs[2]);
		collider_faces.push_back(vertexs[1]);
		collider_faces.push_back(vertexs[5]);
		collider_faces.push_back(vertexs[2]);
		collider_faces.push_back(vertexs[5]);
		collider_faces.push_back(vertexs[6]);

		collider_faces.push_back(vertexs[0]);
		collider_faces.push_back(vertexs[3]);
		collider_faces.push_back(vertexs[7]);
		collider_faces.push_back(vertexs[0]);
		collider_faces.push_back(vertexs[7]);
		collider_faces.push_back(vertexs[4]);

		collider_faces.push_back(vertexs[1]);
		collider_faces.push_back(vertexs[2]);
		collider_faces.push_back(vertexs[3]);
		collider_faces.push_back(vertexs[1]);
		collider_faces.push_back(vertexs[3]);
		collider_faces.push_back(vertexs[0]);

		collider_faces.push_back(vertexs[6]);
		collider_faces.push_back(vertexs[5]);
		collider_faces.push_back(vertexs[4]);
		collider_faces.push_back(vertexs[6]);
		collider_faces.push_back(vertexs[4]);
		collider_faces.push_back(vertexs[7]);

		collider_faces.push_back(vertexs[2]);
		collider_faces.push_back(vertexs[6]);
		collider_faces.push_back(vertexs[7]);
		collider_faces.push_back(vertexs[2]);
		collider_faces.push_back(vertexs[7]);
		collider_faces.push_back(vertexs[3]);

		collider_faces.push_back(vertexs[5]);
		collider_faces.push_back(vertexs[1]);
		collider_faces.push_back(vertexs[0]);
		collider_faces.push_back(vertexs[5]);
		collider_faces.push_back(vertexs[0]);
		collider_faces.push_back(vertexs[4]);
	}

	ConcavePolygonShape3D* result = memnew(ConcavePolygonShape3D);
	if (collider_faces.size() > 0) {
		result->set_faces(collider_faces);
	}
	return result;
}

TypedArray<Device> VoxelBlockData::generate_device(const int& filter)
{
	TypedArray<Device>  result;
	Ref<PresetsData> presets_data = get_presets_data();
	ERR_FAIL_NULL_V(presets_data, result);

	TypedArray<DevicePreset> device_presets = presets_data->get_device_presets();
	for (int x = 0; x < size.x; x++)
	{
		for (int y = 0; y < size.y; y++)
		{
			for (int z = 0; z < size.z; z++)
			{
				Vector3i position = Vector3i(x, y, z);
				Voxel voxel = get_voxel(position);
				int type = _get_voxel_type(voxel);
				int id = _get_voxel_id(voxel);

				ERR_FAIL_INDEX_V(id, device_presets.size(), result);
				Ref<DevicePreset> device_preset = device_presets[id];
				Device* device = cast_to<Device>(devices[position]);
				if (type == VoxelBlockData::DEVICE)
				{
					if (device != nullptr) {
						if (device->get_device_preset() != device_preset) {
							devices.erase(position);
							device->call_deferred("queue_free");
							device = nullptr;
						}
					}
					if (device == nullptr)
					{
						device = cast_to<Device>(_build_device(device_preset, position, voxel));
						devices[position] = device;
						device->set_key(position);
						result.push_back(device);
					}
				}
				else {
					if (device != nullptr) {
						devices.erase(position);
						device->call_deferred("queue_free");
					}
				}
			}
		}
	}
	return result;
}


Vector3 VoxelBlockData::translate_point_to_voxel_block_coordinatet(const Transform3D& global_transform, const Vector3& point) {
	return (
		global_transform.affine_inverse() *
		Transform3D(global_transform.basis, point)
		).origin;
}

Vector3 VoxelBlockData::translate_normal_to_voxel_block_coordinatet(const Transform3D& global_transform, const Vector3& normal) {
	return (
		Transform3D(global_transform.basis, Vector3()).affine_inverse() *
		Transform3D(global_transform.basis, normal)
		).origin.normalized();
}

Vector3i VoxelBlockData::get_voxel_position(const Transform3D& global_transform, const Vector3& point, const Vector3& normal)
{
	Vector3 _point = translate_point_to_voxel_block_coordinatet(global_transform, point);
	Vector3 _normal = translate_normal_to_voxel_block_coordinatet(global_transform, normal);
	if (_normal.y == 1) {
		_point.y -= 0.05;
	}
	else if (_normal.y == -1) {
		_point.y += 0.05;
	}
	else if (_normal.x == 1) {
		_point.x -= 0.05;
	}
	else if (_normal.x == -1) {
		_point.x += 0.05;
	}
	else if (_normal.z == 1) {
		_point.z -= 0.05;
	}
	else if (_normal.z == -1) {
		_point.z += 0.05;
	}
	return Vector3i(_point.round());
}