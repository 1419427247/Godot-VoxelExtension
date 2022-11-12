#include "chunk.h"

void Chunk::build_basics(const Ref<PresetsData>& presets_data, Ref<BasicsPreset>& basics_preset, const Vector3i& position, const Vector3i& rotation) {

#define BUILD_MESH_NO_CONDITION(direction)\
	do{\
		int material_id = basics_preset->get_##direction();\
		ERR_FAIL_INDEX(material_id, mesh_arrays.size());\
		Array arrays = mesh_arrays[material_id];\
		BasicsPreset::build_##direction##_mesh(arrays, position, rotation);\
	} while (false)

#define BUILD_MESH(direction,axis)\
	do{\
		Voxel direction##voxel = get_voxel(position + VoxelContainer::get_voxel_direction(axis, rotation));\
		int direction##voxel_type = VoxelContainer::get_voxel_type(direction##voxel);\
		int direction##voxel_id = VoxelContainer::get_voxel_id(direction##voxel);\
		if (direction##voxel_type != VoxelContainerData::BASICS) {\
			int material_id = basics_preset->get_##direction();\
			ERR_FAIL_INDEX(material_id, mesh_arrays.size());\
			Array arrays = mesh_arrays[material_id];\
			BasicsPreset::build_##direction####_mesh(arrays, position, rotation);\
		}else{\
			Vector3i direction##voxel_rotation = VoxelContainer::get_voxel_rotation(direction##voxel);\
			Ref<BasicsPreset> direction##preset = basics_presets[direction##voxel_id];\
			if(direction##preset->get_transparent() != basics_preset->get_transparent() || direction##voxel_rotation.x % 90 != 0 || direction##voxel_rotation.y % 90 != 0 || direction##voxel_rotation.z % 90 != 0){\
				int material_id = basics_preset->get_##direction();\
				ERR_FAIL_INDEX(material_id, mesh_arrays.size());\
				Array arrays = mesh_arrays[material_id];\
				BasicsPreset::build_##direction####_mesh(arrays, position, rotation);\
			}\
		}\
	}while(false)

	Array basics_presets = presets_data->get_basics_presets();
	if (rotation.x % 90 != 0 || rotation.y % 90 != 0 || rotation.z % 90 != 0)
	{
		BUILD_MESH_NO_CONDITION(up);
		BUILD_MESH_NO_CONDITION(down);
		BUILD_MESH_NO_CONDITION(front);
		BUILD_MESH_NO_CONDITION(back);
		BUILD_MESH_NO_CONDITION(left);
		BUILD_MESH_NO_CONDITION(right);
	}
	else {
		BUILD_MESH(up, Vector3i(0, 1, 0));
		BUILD_MESH(down, Vector3i(0, -1, 0));
		BUILD_MESH(front, Vector3i(0, 0, -1));
		BUILD_MESH(back, Vector3i(0, 0, 1));
		BUILD_MESH(left, Vector3i(-1, 0, 0));
		BUILD_MESH(right, Vector3i(1, 0, 0));
	}
#undef BUILD_MESH_NO_CONDITION
#undef BUILD_MESH
}

void Chunk::build_mesh(Ref<MeshPreset>& mesh_preset, const Vector3i& position, const Vector3i& rotation)
{
	Ref<Mesh> mesh = mesh_preset->get_mesh();
	ERR_FAIL_NULL(mesh);
	TypedArray<int> materials = mesh_preset->get_materials();
	for (int i = 0; i < mesh->get_surface_count(); i++)
	{
		int material_id = materials[i];
		ERR_FAIL_INDEX(material_id, mesh_arrays.size());
		Array arrays = mesh_arrays[material_id];
		mesh_preset->build_mesh(arrays, i, position, rotation);
	}
}

void Chunk::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_chunk_key", "value"), &Chunk::set_chunk_key);
	ClassDB::bind_method(D_METHOD("get_chunk_key"), &Chunk::get_chunk_key);

	ClassDB::bind_method(D_METHOD("set_voxel", "position", "value"), &Chunk::set_voxel);
	ClassDB::bind_method(D_METHOD("get_voxel", "position"), &Chunk::get_voxel);

	ClassDB::bind_method(D_METHOD("point_converted_to_chunk", "point"), &Chunk::point_converted_to_chunk);
	ClassDB::bind_method(D_METHOD("normal_converted_to_chunk", "normal"), &Chunk::normal_converted_to_chunk);

	ClassDB::bind_method(D_METHOD("get_voxel_local_position", "point", "normal"), &Chunk::get_voxel_local_position);

	ClassDB::bind_method(D_METHOD("generate_mesh", "filter"), &Chunk::generate_mesh, BASICS_FILTER | MESH_FILTER | COLLIDER_TRUE_FILTER);
	ClassDB::bind_method(D_METHOD("generate_collider", "filter"), &Chunk::generate_collider, BASICS_FILTER | MESH_FILTER | COLLIDER_TRUE_FILTER);
	ClassDB::bind_method(D_METHOD("generate_device"), &Chunk::generate_device);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "chunk_key"), "set_chunk_key", "get_chunk_key");

	BIND_ENUM_CONSTANT(EMPTY_FILTER);
	BIND_ENUM_CONSTANT(BASICS_FILTER);
	BIND_ENUM_CONSTANT(MESH_FILTER);
	BIND_ENUM_CONSTANT(DEVICE_FILTER);
	BIND_ENUM_CONSTANT(TRANSPARENT_TRUE_FILTER);
	BIND_ENUM_CONSTANT(TRANSPARENT_FALSE_FILTER);
	BIND_ENUM_CONSTANT(COLLIDER_TRUE_FILTER);
	BIND_ENUM_CONSTANT(COLLIDER_FALSE_FILTER);
}

Chunk::Chunk() {
	this->chunk_key = Vector3i(0, 0, 0);
}

Chunk::~Chunk() {

}

VoxelContainer* Chunk::get_voxel_container() const
{
	return cast_to<VoxelContainer>(get_parent());
}

void Chunk::set_chunk_key(const Vector3i& value) {
	chunk_key = value;
}

Vector3i Chunk::get_chunk_key() const {
	return chunk_key;
}


Dictionary Chunk::get_devices() const
{
	return devices;
}

/// <summary>
/// 设置体素信息
/// </summary>
/// <param name="position">本地坐标</param>
/// <param name="value"></param>
void Chunk::set_voxel(const Vector3i& position, const Voxel& value)
{
	VoxelContainer* voxel_container = get_voxel_container();
	ERR_FAIL_NULL_MSG(voxel_container, "Chunk node must be a direct child of VoxelVontainer");

	Vector3i chunk_size = voxel_container->get_chunk_size();
	if (voxel_container->is_isolated() == true) {
		if (position.x < 0 || position.x >= chunk_size.x ||
			position.y < 0 || position.y >= chunk_size.y ||
			position.z < 0 || position.z >= chunk_size.z) {
			return;
		}
	}
	voxel_container->set_voxel(position + chunk_key * chunk_size, value);
}

/// <summary>
/// 获取体素信息(在本地坐标中)
/// </summary>
/// <param name="position">本地坐标</param>
/// <returns></returns>
Voxel Chunk::get_voxel(const Vector3i& position) const
{
	VoxelContainer* voxel_container = get_voxel_container();
	ERR_FAIL_NULL_V_MSG(voxel_container, EMPTY_VOXEL, "Chunk node must be a direct child of VoxelVontainer");

	Vector3i chunk_size = voxel_container->get_chunk_size();
	if (voxel_container->is_isolated() == true) {
		if (position.x < 0 || position.x >= chunk_size.x ||
			position.y < 0 || position.y >= chunk_size.y ||
			position.z < 0 || position.z >= chunk_size.z) {
			return EMPTY_VOXEL;
		}
	}
	return voxel_container->get_voxel(position + chunk_key * chunk_size);
}

Vector3 Chunk::point_converted_to_chunk(const Vector3& point) const {
	return (
		get_global_transform().affine_inverse() *
		Transform3D(get_global_transform().basis, point)
		).origin;
}

Vector3 Chunk::normal_converted_to_chunk(const Vector3& normal) const {
	return (
		Transform3D(get_global_transform().basis, Vector3()).affine_inverse() *
		Transform3D(get_global_transform().basis, normal)
		).origin.normalized();
}

Vector3i Chunk::get_voxel_local_position(const Vector3& point, const Vector3& normal) const
{
	Vector3 _point = point_converted_to_chunk(point);
	Vector3 _normal = normal_converted_to_chunk(normal);
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

/// <summary>
/// 生成区块内所有可渲染网格
/// </summary>
/// <returns></returns>
ArrayMesh* Chunk::generate_mesh(const int& filter)
{
	VoxelContainer* voxel_container = get_voxel_container();
	ERR_FAIL_NULL_V_MSG(voxel_container, nullptr, "Chunk node must be a direct child of VoxelVontainer");

	Ref<PresetsData> presets_data = voxel_container->get_presets_data();
	ERR_FAIL_NULL_V(presets_data, nullptr);


	bool is_generate_basics = (filter & BASICS_FILTER) != 0;
	bool is_generate_mesh = (filter & MESH_FILTER) != 0;

	bool is_generate_transparent_true = (filter & TRANSPARENT_TRUE_FILTER) != 0;
	bool is_generate_transparent_false = (filter & TRANSPARENT_FALSE_FILTER) != 0;
	bool is_generate_transparent_all = is_generate_transparent_true == is_generate_transparent_false;

	bool is_generate_collider_true = (filter & COLLIDER_TRUE_FILTER) != 0;
	bool is_generate_collider_false = (filter & COLLIDER_FALSE_FILTER) != 0;
	bool is_generate_collider_all = is_generate_collider_true == is_generate_collider_false;


	Array materials = presets_data->get_materials();
	Array basics_presets = presets_data->get_basics_presets();
	Array mesh_presets = presets_data->get_mesh_presets();

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

	Vector3i chunk_size = voxel_container->get_chunk_size();
	for (int x = 0; x < chunk_size.x; x++)
	{
		for (int y = 0; y < chunk_size.y; y++)
		{
			for (int z = 0; z < chunk_size.z; z++)
			{
				Vector3i local_position = Vector3i(x, y, z);
				Voxel voxel = get_voxel(local_position);
				int type = VoxelRoom::get_voxel_type(voxel);
				int id = VoxelRoom::get_voxel_id(voxel);
				int flag = VoxelRoom::get_voxel_flag(voxel);
				switch (type)
				{
				case VoxelContainerData::BASICS: {
					Vector3i rotation = VoxelRoom::get_voxel_rotation(voxel);

					ERR_FAIL_INDEX_V(id, basics_presets.size(), nullptr);
					Ref<BasicsPreset> basics_preset = basics_presets[id];
					ERR_FAIL_NULL_V_MSG(basics_preset, nullptr, "The basics_preset with id " + String::num_int64(id) + " is null");

					if (is_generate_basics == false)
					{
						continue;
					}
					if (is_generate_transparent_all == false)
					{
						if (is_generate_transparent_true == true && basics_preset->get_transparent() == false)
						{
							continue;
						}
						if (is_generate_transparent_false == true && basics_preset->get_transparent() == true)
						{
							continue;
						}
					}
					if (is_generate_collider_all == false)
					{
						if (is_generate_collider_true == true && basics_preset->get_collider() == false)
						{
							continue;
						}
						if (is_generate_collider_false == true && basics_preset->get_collider() == true)
						{
							continue;
						}
					}
					build_basics(presets_data, basics_preset, local_position, rotation);
					break;
				}
				case VoxelContainerData::MESH: {

					ERR_FAIL_INDEX_V(id, mesh_presets.size(), nullptr);
					Ref<MeshPreset> mesh_preset = mesh_presets[id];
					ERR_FAIL_NULL_V_MSG(mesh_preset, nullptr, "The mesh_preset with id " + String::num_int64(id) + " is null");

					if (is_generate_mesh == false)
					{
						continue;
					}
					if (is_generate_transparent_all == false)
					{
						if (is_generate_transparent_true == true && mesh_preset->get_transparent() == false)
						{
							continue;
						}
						if (is_generate_transparent_false == true && mesh_preset->get_transparent() == true)
						{
							continue;
						}
					}
					if (is_generate_collider_all == false)
					{
						if (is_generate_collider_true == true && mesh_preset->get_collider() == false)
						{
							continue;
						}
						if (is_generate_collider_false == true && mesh_preset->get_collider() == true)
						{
							continue;
						}
					}
					Vector3i rotation = VoxelRoom::get_voxel_rotation(voxel);
					build_mesh(mesh_preset, local_position, rotation);
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
/// <summary>
/// 将每个体素视作正方体，以生成区块的碰撞网格
/// </summary>
/// <returns></returns>
ConcavePolygonShape3D* Chunk::generate_collider(const int& filter)
{
	VoxelContainer* voxel_container = get_voxel_container();
	ERR_FAIL_NULL_V_MSG(voxel_container, nullptr, "Chunk node must be a direct child of VoxelVontainer");

	Ref<PresetsData> presets_data = voxel_container->get_presets_data();
	ERR_FAIL_NULL_V(presets_data, nullptr);

	Array basics_presets = presets_data->get_basics_presets();
	Array mesh_presets = presets_data->get_mesh_presets();
	Array device_presets = presets_data->get_device_presets();

	bool is_generate_basics = (filter & BASICS_FILTER) != 0;
	bool is_generate_mesh = (filter & MESH_FILTER) != 0;
	bool is_generate_device = (filter & DEVICE_FILTER) != 0;

	bool is_generate_transparent_true = (filter & TRANSPARENT_TRUE_FILTER) != 0;
	bool is_generate_transparent_false = (filter & TRANSPARENT_FALSE_FILTER) != 0;
	bool is_generate_transparent_all = is_generate_transparent_true == is_generate_transparent_false;

	bool is_generate_collider_true = (filter & COLLIDER_TRUE_FILTER) != 0;
	bool is_generate_collider_false = (filter & COLLIDER_FALSE_FILTER) != 0;
	bool is_generate_collider_all = is_generate_collider_true == is_generate_collider_false;

	PackedVector3Array collider_faces;
	Vector3i chunk_size = voxel_container->get_chunk_size();

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

	Area area = Area(chunk_size);
	List<Box> boxs;

	for (int x = 0; x < chunk_size.x; x++)
	{
		for (int y = 0; y < chunk_size.y; y++)
		{
			for (int z = 0; z < chunk_size.z; z++)
			{
				Vector3i position = Vector3i(x, y, z);
				Voxel voxel = get_voxel(position);
				int type = VoxelContainer::get_voxel_type(voxel);
				int id = VoxelContainer::get_voxel_id(voxel);
				Ref<Preset> preset;
				switch (type)
				{
				case VoxelContainerData::EMPTY:
					continue;
					break;
				case VoxelContainerData::BASICS:
				{
					if (is_generate_basics == false)
					{
						continue;
					}
					ERR_FAIL_INDEX_V(id, basics_presets.size(), nullptr);
					preset = basics_presets[id];
					break;
				}
				case VoxelContainerData::MESH:
				{
					if (is_generate_mesh == false)
					{
						continue;
					}
					ERR_FAIL_INDEX_V(id, mesh_presets.size(), nullptr);
					preset = mesh_presets[id];
					break;
				}
				case VoxelContainerData::DEVICE:
				{
					if (is_generate_device == false)
					{
						continue;
					}
					ERR_FAIL_INDEX_V(id, device_presets.size(), nullptr);
					preset = device_presets[id];
				}
				}
				ERR_FAIL_NULL_V_MSG(preset, nullptr, "The preset is null [type = " + String::num_int64(type) + ",id = " + String::num_int64(id) + "]");
				if (is_generate_transparent_all == false)
				{
					if (is_generate_transparent_true == true && preset->get_transparent() == false)
					{
						continue;
					}
					if (is_generate_transparent_false == true && preset->get_transparent() == true)
					{
						continue;
					}
				}
				if (is_generate_collider_all == false)
				{
					if (is_generate_collider_true == true && preset->get_collider() == false)
					{
						continue;
					}
					if (is_generate_collider_false == true && preset->get_collider() == true)
					{
						continue;
					}
				}
				area.set_flag(x, y, z, true);
			}
		}
	}
	for (int x = 0; x < chunk_size.x; x++)
	{
		for (int y = 0; y < chunk_size.y; y++)
		{
			for (int z = 0; z < chunk_size.z; z++)
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

void Chunk::generate_device()
{
	VoxelContainer* voxel_container = get_voxel_container();
	ERR_FAIL_NULL_MSG(voxel_container, "Chunk node must be a direct child of VoxelVontainer");

	Ref<PresetsData> presets_data = voxel_container->get_presets_data();
	Array device_presets = presets_data->get_device_presets();

	Vector3i chunk_size = voxel_container->get_chunk_size();
	for (int x = 0; x < chunk_size.x; x++)
	{
		for (int y = 0; y < chunk_size.y; y++)
		{
			for (int z = 0; z < chunk_size.z; z++)
			{
				Vector3i position = Vector3i(x, y, z);
				Voxel voxel = get_voxel(position);
				int type = VoxelRoom::get_voxel_type(voxel);
				int id = VoxelRoom::get_voxel_id(voxel);
				Vector3i rotation = VoxelRoom::get_voxel_rotation(voxel);

				Device* device = cast_to<Device>(devices[position]);

				if (type == VoxelContainerData::DEVICE)
				{
					Ref<DevicePreset> device_preset = device_presets[id];
					if (device != nullptr) {
						if (device->get_device_preset() != device_preset) {
							devices.erase(position);
							device->queue_free();
							device = nullptr;
						}
					}
					if (device == nullptr) {
						Node* node = device_preset->get_packed_scene()->instantiate();
						device = cast_to<Device>(node);
						if (unlikely(device == nullptr))
						{
							node->queue_free();
							ERR_FAIL_MSG("The DevicePreset with id " + String::num_int64(id) + " cannot be instantiated");
						}
						device->set_device_preset(device_preset);
						devices[position] = device;

						device->set_position(position);
						device->set_rotation(rotation);
						add_child(device);
					}
				}
				else {
					if (device != nullptr) {
						devices.erase(position);
						device->queue_free();
					}
				}
			}
		}
	}
}