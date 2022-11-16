#include "voxel_block.h"

void VoxelBlock::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_key", "value"), &VoxelBlock::set_key);
	ClassDB::bind_method(D_METHOD("get_key"), &VoxelBlock::get_key);

	ClassDB::bind_method(D_METHOD("set_voxel", "position", "value"), &VoxelBlock::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel", "position"), &VoxelBlock::get_voxel);

	ClassDB::bind_method(D_METHOD("point_converted_to_voxel_block", "point"), &VoxelBlock::point_converted_to_block);
	ClassDB::bind_method(D_METHOD("normal_converted_to_voxel_block", "normal"), &VoxelBlock::normal_converted_to_block);

	ClassDB::bind_method(D_METHOD("get_voxel_local_position", "point", "normal"), &VoxelBlock::get_voxel_local_position);
	ClassDB::bind_method(D_METHOD("is_filled", "voxel"), &VoxelBlock::is_filled);

	ClassDB::bind_method(D_METHOD("generate_mesh", "filter"), &VoxelBlock::generate_mesh, 0b1);
	ClassDB::bind_method(D_METHOD("generate_collider", "filter"), &VoxelBlock::generate_collider, 0b1);
	ClassDB::bind_method(D_METHOD("generate_device"), &VoxelBlock::generate_device, 0b1);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "key"), "set_key", "get_key");
}

VoxelBlock::VoxelBlock() {
	voxel_container = nullptr;
	set_key(Vector3i(0, 0, 0));
}

VoxelBlock::~VoxelBlock() {

}


void VoxelBlock::set_key(const Vector3i& value) {
	key = value;
	if (voxel_container != nullptr)
	{
		voxel_container_data = voxel_container->get_voxel_container_data(key);
	}
}

Vector3i VoxelBlock::get_key() const {
	return key;
}


Dictionary VoxelBlock::get_devices() const
{
	return devices;
}

void VoxelBlock::set_voxel(const Vector3i& position, const Voxel& value)
{
	ERR_FAIL_NULL_MSG(voxel_container, "VoxelBlock node must be a direct child of VoxelVontainer");
	Vector3i voxel_block_size = voxel_container->get_voxel_block_size();
	if (voxel_container->is_isolated() == true) {
		voxel_container_data->set_voxel(position, value);
	}
	else {
		voxel_container->set_voxel(position + key * voxel_block_size, value);
	}

	if (position.x < 0 || position.x >= voxel_block_size.x ||
		position.y < 0 || position.y >= voxel_block_size.y ||
		position.z < 0 || position.z >= voxel_block_size.z)
	{
		if (voxel_container->is_isolated() == true) {
			return;
		}
		return voxel_container->set_voxel(position + key * voxel_block_size, value);
	}
	return voxel_container_data->set_voxel(position, value);
}

Voxel VoxelBlock::get_voxel(const Vector3i& position)
{
	ERR_FAIL_NULL_V_MSG(voxel_container, EMPTY_VOXEL, "VoxelBlock node must be a direct child of VoxelVontainer");
	Vector3i voxel_block_size = voxel_container->get_voxel_block_size();
	if (position.x < 0 || position.x >= voxel_block_size.x ||
		position.y < 0 || position.y >= voxel_block_size.y ||
		position.z < 0 || position.z >= voxel_block_size.z)
	{
		if (voxel_container->is_isolated() == true) {
			return EMPTY_VOXEL;
		}
		return voxel_container->get_voxel(position + key * voxel_block_size);
	}
	return voxel_container_data->get_voxel(position);
}

Vector3 VoxelBlock::point_converted_to_block(const Vector3& point) const {
	return (
		get_global_transform().affine_inverse() *
		Transform3D(get_global_transform().basis, point)
		).origin;
}

Vector3 VoxelBlock::normal_converted_to_block(const Vector3& normal) const {
	return (
		Transform3D(get_global_transform().basis, Vector3()).affine_inverse() *
		Transform3D(get_global_transform().basis, normal)
		).origin.normalized();
}

Vector3i VoxelBlock::get_voxel_local_position(const Vector3& point, const Vector3& normal) const
{
	Vector3 _point = point_converted_to_block(point);
	Vector3 _normal = normal_converted_to_block(normal);
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

ArrayMesh* VoxelBlock::generate_mesh(const int& filter)
{

	ERR_FAIL_NULL_V_MSG(voxel_container, nullptr, "VoxelBlock node must be a direct child of VoxelVontainer");

	Ref<PresetsData> presets_data = voxel_container->get_presets_data();
	ERR_FAIL_NULL_V(presets_data, nullptr);

	Array materials = presets_data->get_materials();
	Array basics_presets = presets_data->get_basics_presets();
	Array model_presets = presets_data->get_model_presets();

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

	Vector3i voxel_block_size = voxel_container->get_voxel_block_size();
	for (int x = 0; x < voxel_block_size.x; x++)
	{
		for (int y = 0; y < voxel_block_size.y; y++)
		{
			for (int z = 0; z < voxel_block_size.z; z++)
			{
				Vector3i position = Vector3i(x, y, z);
				Voxel voxel = get_voxel(position);
				int type = VoxelContainer::get_voxel_type(voxel);
				int id = VoxelContainer::get_voxel_id(voxel);
				int flag = VoxelContainer::get_voxel_flag(voxel);
				switch (type)
				{
				case VoxelContainer::BASICS: {
					ERR_FAIL_INDEX_V(id, basics_presets.size(), nullptr);
					Ref<BasicsPreset> basics_preset = basics_presets[id];
					ERR_FAIL_NULL_V_MSG(basics_preset, nullptr, "The basics_preset with id " + String::num_int64(id) + " is null");
					if ((filter & basics_preset->get_filter()) == 0)
					{
						continue;
					}
					Vector3i rotation = VoxelContainer::get_voxel_rotation(voxel);
					Array basics_presets = presets_data->get_basics_presets();
					if (rotation.x % 90 != 0 || rotation.y % 90 != 0 || rotation.z % 90 != 0)
					{
						for (int direction = 0; direction < 6; direction++)
						{
							int material_id = basics_preset->get_material_id(direction);
							ERR_FAIL_INDEX_V(material_id, mesh_arrays.size(), nullptr);
							Array arrays = mesh_arrays[material_id];
							BasicsPreset::build_mesh(direction, arrays, position, rotation);
						}
					}
					else {
						for (int direction = 0; direction < 6; direction++) {
							Voxel voxel = get_voxel(position + VoxelContainer::get_voxel_direction(direction, rotation));
							int voxel_type = VoxelContainer::get_voxel_type(voxel);
							int voxel_id = VoxelContainer::get_voxel_id(voxel);

							if (voxel_type != VoxelContainer::BASICS) {
								int material_id = basics_preset->get_material_id(direction);
								ERR_FAIL_INDEX_V(material_id, mesh_arrays.size(), nullptr);
								Array arrays = mesh_arrays[material_id];
								BasicsPreset::build_mesh(direction, arrays, position, rotation);
							}
							else {
								Vector3i voxel_rotation = VoxelContainer::get_voxel_rotation(voxel);
								Ref<BasicsPreset> preset = basics_presets[voxel_id];
								if (preset->get_transparent() != basics_preset->get_transparent() || voxel_rotation.x % 90 != 0 || voxel_rotation.y % 90 != 0 || voxel_rotation.z % 90 != 0) {

									int material_id = basics_preset->get_material_id(direction);
									ERR_FAIL_INDEX_V(material_id, mesh_arrays.size(), nullptr);
									Array arrays = mesh_arrays[material_id];
									BasicsPreset::build_mesh(direction, arrays, position, rotation);
								}
							}
						}
					}
					break;
				}
				case VoxelContainer::MODEL: {
					ERR_FAIL_INDEX_V(id, model_presets.size(), nullptr);
					Ref<ModelPreset> model_preset = model_presets[id];
					ERR_FAIL_NULL_V_MSG(model_preset, nullptr, "The model_preset with id " + String::num_int64(id) + " is null");
					if ((filter & model_preset->get_filter()) == 0)
					{
						continue;
					}
					Vector3i rotation = VoxelContainer::get_voxel_rotation(voxel);
					Ref<Mesh> mesh = model_preset->get_mesh();
					ERR_FAIL_NULL_V(mesh, nullptr);
					TypedArray<int> materials = model_preset->get_materials();
					for (int i = 0; i < mesh->get_surface_count(); i++)
					{
						int material_id = materials[i];
						ERR_FAIL_INDEX_V(material_id, mesh_arrays.size(), nullptr);
						Array arrays = mesh_arrays[material_id];
						model_preset->build_mesh(arrays, i, position, rotation);
					}
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

ConcavePolygonShape3D* VoxelBlock::generate_collider(const int& filter)
{

	ERR_FAIL_NULL_V_MSG(voxel_container, nullptr, "VoxelBlock node must be a direct child of VoxelVontainer");

	Ref<PresetsData> presets_data = voxel_container->get_presets_data();
	ERR_FAIL_NULL_V(presets_data, nullptr);

	Array basics_presets = presets_data->get_basics_presets();
	Array model_presets = presets_data->get_model_presets();
	Array device_presets = presets_data->get_device_presets();

	PackedVector3Array collider_faces;
	Vector3i voxel_block_size = voxel_container->get_voxel_block_size();

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

	Area area = Area(voxel_block_size);
	List<Box> boxs;

	for (int x = 0; x < voxel_block_size.x; x++)
	{
		for (int y = 0; y < voxel_block_size.y; y++)
		{
			for (int z = 0; z < voxel_block_size.z; z++)
			{
				Vector3i position = Vector3i(x, y, z);
				Voxel voxel = get_voxel(position);
				int type = VoxelContainer::get_voxel_type(voxel);
				int id = VoxelContainer::get_voxel_id(voxel);
				Ref<Preset> preset;
				switch (type)
				{
				case VoxelContainer::EMPTY:
					continue;
				case VoxelContainer::BASICS:
				{
					ERR_FAIL_INDEX_V(id, basics_presets.size(), nullptr);
					preset = basics_presets[id];
					break;
				}
				case VoxelContainer::MODEL:
				{
					ERR_FAIL_INDEX_V(id, model_presets.size(), nullptr);
					preset = model_presets[id];
					break;
				}
				case VoxelContainer::DEVICE:
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
	for (int x = 0; x < voxel_block_size.x; x++)
	{
		for (int y = 0; y < voxel_block_size.y; y++)
		{
			for (int z = 0; z < voxel_block_size.z; z++)
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

void VoxelBlock::generate_device(const int& filter)
{
	ERR_FAIL_NULL_MSG(voxel_container, "VoxelBlock node must be a direct child of VoxelVontainer");

	Ref<PresetsData> presets_data = voxel_container->get_presets_data();
	Array device_presets = presets_data->get_device_presets();

	Vector3i voxel_block_size = voxel_container->get_voxel_block_size();
	for (int x = 0; x < voxel_block_size.x; x++)
	{
		for (int y = 0; y < voxel_block_size.y; y++)
		{
			for (int z = 0; z < voxel_block_size.z; z++)
			{
				Vector3i position = Vector3i(x, y, z);
				Voxel voxel = get_voxel(position);
				int type = VoxelContainer::get_voxel_type(voxel);
				int id = VoxelContainer::get_voxel_id(voxel);
				Vector3i rotation = VoxelContainer::get_voxel_rotation(voxel);
				Device* device = cast_to<Device>(devices[position]);

				if (type == VoxelContainer::DEVICE)
				{
					Ref<DevicePreset> device_preset = device_presets[id];
					if (device != nullptr) {
						if (device->get_device_preset() != device_preset) {
							devices.erase(position);
							device->call_deferred("queue_free");
							device = nullptr;
						}
					}
					if (device == nullptr) {
						Node* node = device_preset->get_packed_scene()->instantiate();
						device = cast_to<Device>(node);
						if (device == nullptr)
						{
							node->queue_free();
							ERR_FAIL_MSG("The DevicePreset with id " + String::num_int64(id) + " cannot be instantiated");
						}
						device->set_device_preset(device_preset);
						devices[position] = device;

						device->set_position(position);
						device->set_rotation(rotation);
						call_deferred("add_child", device);
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
}

bool VoxelBlock::is_filled(const Voxel& voxel) {

	ERR_FAIL_NULL_V_MSG(voxel_container, "VoxelBlock node must be a direct child of VoxelVontainer", true);
	return voxel_container_data->is_filled(voxel);
}

void VoxelBlock::_enter_tree()
{
	voxel_container = cast_to<VoxelContainer>(get_parent());
	if (voxel_container != nullptr)
	{
		voxel_container_data = voxel_container->get_voxel_container_data(key);
	}
}

void VoxelBlock::_exit_tree()
{
	voxel_container = nullptr;
}
