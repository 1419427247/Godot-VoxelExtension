#include "chunk.h"

Array Chunk::get_mesh_array(const int& index) {
	Array result;
	if (index >= mesh_arrays.size())
	{
		UtilityFunctions::printerr("Material[" + String::num_int64(index) + "] does not exist");
		result = Array();
		result.resize(Mesh::ARRAY_MAX);
		result[Mesh::ARRAY_VERTEX] = Array();
		result[Mesh::ARRAY_TEX_UV] = Array();
		result[Mesh::ARRAY_NORMAL] = Array();
		return result;
	}
	if (mesh_arrays[index].get_type() == Variant::NIL) {
		result = Array();
		result.resize(Mesh::ARRAY_MAX);
		result[Mesh::ARRAY_VERTEX] = Array();
		result[Mesh::ARRAY_TEX_UV] = Array();
		result[Mesh::ARRAY_NORMAL] = Array();
		mesh_arrays[index] = result;
	}
	else {
		result = mesh_arrays[index];
	}
	return result;
}

void Chunk::build_basics(const Ref<VoxelWorldData>& voxel_world_data, Ref<BasicsPreset>& basics_preset, const Vector3i& local_position, const Vector3i& rotation) {

#define BUILD_MESH_NO_CONDITION(direction)\
	do{\
		int material_id = basics_preset->get_##direction();\
		Array arrays = get_mesh_array(material_id);\
		BasicsPreset::build_##direction##_mesh(arrays, local_position, rotation);\
	} while (false)

#define BUILD_MESH(direction,axis)\
	do{\
		int voxel_type = VoxelWorld::get_voxel_type(get_voxel(local_position + VoxelWorld::get_voxel_direction(axis, rotation)));\
		if (voxel_type != VoxelWorldData::BASICS) {\
			int material_id = basics_preset->get_##direction();\
			Array arrays = get_mesh_array(material_id);\
			BasicsPreset::build_##direction####_mesh(arrays, local_position, rotation);\
		}\
	}while(false)

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
		BUILD_MESH(up,Vector3i(0, 1, 0));
		BUILD_MESH(down,Vector3i(0, -1, 0));
		BUILD_MESH(front,Vector3i(0, 0, -1));
		BUILD_MESH(back,Vector3i(0, 0, 1));
		BUILD_MESH(left,Vector3i(-1, 0, 0));
		BUILD_MESH(right,Vector3i(1, 0, 0));
	}
#undef BUILD_MESH_NO_CONDITION
#undef BUILD_MESH
}

void Chunk::build_mesh(const Ref<VoxelWorldData>& voxel_world_data, Ref<MeshPreset>& mesh_preset, const Vector3i& local_position, const Vector3i& rotation)
{
	Ref<Mesh> mesh = mesh_preset->get_mesh();
	if (mesh.is_null())
	{
		UtilityFunctions::printerr("Cannot build mesh at Chunk" + chunk_position + "-" + local_position);
		return;
	}
	TypedArray<int> materials = mesh_preset->get_materials();
	for (int i = 0; i < mesh->get_surface_count(); i++)
	{
		int material_id = materials[i];
		Array arrays = get_mesh_array(material_id);
		mesh_preset->build_mesh(arrays, i, local_position, rotation);
	}
}

void Chunk::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_chunk_position", "value"), &Chunk::set_chunk_position);
	ClassDB::bind_method(D_METHOD("get_chunk_position"), &Chunk::get_chunk_position);

	ClassDB::bind_method(D_METHOD("get_voxel_local_position", "position", "normal"), &Chunk::get_voxel_local_position);

	ClassDB::bind_method(D_METHOD("generate_mesh"), &Chunk::generate_mesh);
	ClassDB::bind_method(D_METHOD("generate_collider"), &Chunk::generate_collider);
	ClassDB::bind_method(D_METHOD("generate_device"), &Chunk::generate_device);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR3I, "chunk_position"), "set_chunk_position", "get_chunk_position");
}

void Chunk::_notification(int p_what) {
	if (p_what == NOTIFICATION_ENTER_TREE)
	{
		voxel_world = static_cast<VoxelWorld*>(get_parent());
	}
	else if (p_what == NOTIFICATION_EXIT_TREE) {
		voxel_world = nullptr;
	}
}

Chunk::Chunk() {
	this->voxel_world = nullptr;
	this->chunk_position = Vector3i(0, 0, 0);
}

Chunk::~Chunk() {
	//UtilityFunctions::print("~Chunk");
	//UtilityFunctions::print(Engine::get_singleton()->is_editor_hint());
}

void Chunk::set_chunk_position(const Vector3i& value) {
	if (value.x <= 0 || value.y <= 0 || value.z <= 0)
	{
		UtilityFunctions::printerr("Chunk position is an invalid value");
		return;
	}
	chunk_position = value;
}

Vector3i Chunk::get_chunk_position() const {
	return chunk_position;
}


Dictionary Chunk::get_devices() const
{
	return devices;
}

/// <summary>
/// 设置体素信息
/// </summary>
/// <param name="local_position">本地坐标</param>
/// <param name="value"></param>
void Chunk::set_voxel(const Vector3i& local_position, const Voxel& value)
{
	Ref<VoxelWorldData> voxel_world_data = voxel_world->get_voxel_world_data();
	if (voxel_world_data.is_null())
	{
		UtilityFunctions::printerr("voxel_world_data is null");
		return;
	}
	Vector3i chunk_size = voxel_world_data->get_chunk_size();
	if (voxel_world->get_isolated() == true) {
		if (local_position.x < 0 || local_position.x >= chunk_size.x ||
			local_position.y < 0 || local_position.y >= chunk_size.y ||
			local_position.z < 0 || local_position.z >= chunk_size.z) {
			return;
		}
	}
	voxel_world->set_voxel(local_position + chunk_position * voxel_world_data->get_chunk_size(), value);
}

/// <summary>
/// 获取体素信息(在本地坐标中)
/// </summary>
/// <param name="local_position">本地坐标</param>
/// <returns></returns>
Voxel Chunk::get_voxel(const Vector3i& local_position) const
{
	Ref<VoxelWorldData> voxel_world_data = voxel_world->get_voxel_world_data();
	if (voxel_world_data.is_null())
	{
		UtilityFunctions::printerr("voxel_world_data is null");
		return VoxelWorld::empty_voxel();
	}
	Vector3i chunk_size = voxel_world_data->get_chunk_size();
	if (voxel_world->get_isolated() == true) {
		if (local_position.x < 0 || local_position.x >= chunk_size.x ||
			local_position.y < 0 || local_position.y >= chunk_size.y ||
			local_position.z < 0 || local_position.z >= chunk_size.z) {
			return VoxelWorld::empty_voxel();
		}
	}
	return voxel_world->get_voxel(local_position + chunk_position * voxel_world_data->get_chunk_size());
}

Vector3i Chunk::get_voxel_local_position(const Vector3& point, const Vector3& normal) const
{
	Vector3 voxel_position = point - get_position();
	if (normal.y == 1) {
		voxel_position.y -= 0.05;
	}
	else if (normal.y == -1) {
		voxel_position.y += 0.05;
	}
	else if (normal.x == 1) {
		voxel_position.x -= 0.05;
	}
	else if (normal.x == -1) {
		voxel_position.x += 0.05;
	}
	else if (normal.z == 1) {
		voxel_position.z -= 0.05;
	}
	else if (normal.z == -1) {
		voxel_position.z += 0.05;
	}
	return Vector3i(voxel_position.round());
}

/// <summary>
/// 生成区块内所有类型为[Basics or Mesh]合并后的可渲染网格
/// </summary>
/// <returns></returns>
Ref<ArrayMesh> Chunk::generate_mesh()
{
	Ref<VoxelWorldData> voxel_world_data = voxel_world->get_voxel_world_data();
	if (voxel_world_data.is_null())
	{
		UtilityFunctions::printerr(UtilityFunctions::str("The voxel_world_data is null"));
		return Ref<Mesh>();
	}
	Ref<PresetsData> presets_data = voxel_world->get_presets_data();

	Array custom_materials = presets_data->get_custom_materials();
	Array basics_presets = presets_data->get_basics_presets();
	Array mesh_presets = presets_data->get_mesh_presets();
	mesh_arrays.clear();
	mesh_arrays.resize(custom_materials.size());

	Vector3i chunk_size = voxel_world_data->get_chunk_size();
	for (int x = 0; x < chunk_size.x; x++)
	{
		for (int y = 0; y < chunk_size.y; y++)
		{
			for (int z = 0; z < chunk_size.z; z++)
			{
				Vector3i local_position = Vector3i(x, y, z);
				Voxel voxel = get_voxel(local_position);
				int type = VoxelWorld::get_voxel_type(voxel);
				int id = VoxelWorld::get_voxel_id(voxel);
				int flag = VoxelWorld::get_voxel_flag(voxel);
				switch (type)
				{
				case VoxelWorldData::BASICS: {
					Vector3i rotation = VoxelWorld::get_voxel_rotation(voxel);
					if (id >= basics_presets.size())
					{
						UtilityFunctions::printerr("BasicsPreset[" + String::num_int64(id) + "] does not exist");
						continue;
					}
					Ref<BasicsPreset> basics_preset = basics_presets[id];
					build_basics(voxel_world_data, basics_preset, local_position, rotation);
					break;
				}
				case VoxelWorldData::MESH: {
					Vector3i rotation = VoxelWorld::get_voxel_rotation(voxel);
					if (id >= mesh_presets.size())
					{
						UtilityFunctions::printerr("MeshPreset[" + String::num_int64(id) + "] does not exist");
						continue;
					}
					Ref<MeshPreset> mesh_preset = mesh_presets[id];
					build_mesh(voxel_world_data, mesh_preset, local_position, rotation);
					break;
				}
				}
			}
		}
	}
	Ref<ArrayMesh> result;
	result.instantiate();
	result->reference();
	for (int i = 0; i < mesh_arrays.size(); i++)
	{
		if (mesh_arrays[i].get_type() != Variant::NIL) {
			Array arrays = mesh_arrays[i];
			arrays[ArrayMesh::ARRAY_VERTEX] = PackedVector3Array((Array)arrays[ArrayMesh::ARRAY_VERTEX]);
			arrays[ArrayMesh::ARRAY_NORMAL] = PackedVector3Array((Array)arrays[ArrayMesh::ARRAY_NORMAL]);
			arrays[ArrayMesh::ARRAY_TEX_UV] = PackedVector2Array((Array)arrays[ArrayMesh::ARRAY_TEX_UV]);
			Ref<ShaderMaterial> material = cast_to<CustomMaterial>(custom_materials[i])->get_shader_material();
			result->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, arrays);
			result->surface_set_material(result->get_surface_count() - 1, material);
		}
	}
	return result;
}
/// <summary>
/// 将每个体素视作正方体，以生成区块的碰撞网格
/// </summary>
/// <returns></returns>
Ref<ConcavePolygonShape3D> Chunk::generate_collider()
{
	Ref<VoxelWorldData> voxel_world_data = voxel_world->get_voxel_world_data();
	if (voxel_world_data.is_null())
	{
		UtilityFunctions::printerr(UtilityFunctions::str("The voxel_world_data is null"));
		return Ref<ConcavePolygonShape3D>();
	}
	PackedVector3Array trigger_faces;

	Vector3i chunk_size = voxel_world_data->get_chunk_size();
	for (int x = 0; x < chunk_size.x; x++)
	{
		for (int y = 0; y < chunk_size.y; y++)
		{
			for (int z = 0; z < chunk_size.z; z++)
			{
				Vector3i local_position = Vector3i(x, y, z);
				int type = VoxelWorld::get_voxel_type(get_voxel(local_position));
				if (type == VoxelWorldData::EMPTY) {
					continue;
				}
				Vector3 vertexs[] = {
					Vector3(0.5, -0.5, -0.5) + Vector3(local_position),
					Vector3(0.5, 0.5, -0.5) + Vector3(local_position),
					Vector3(-0.5, 0.5, -0.5) + Vector3(local_position),
					Vector3(-0.5, -0.5, -0.5) + Vector3(local_position),
					Vector3(0.5, -0.5, 0.5) + Vector3(local_position),
					Vector3(0.5, 0.5, 0.5) + Vector3(local_position),
					Vector3(-0.5, 0.5, 0.5) + Vector3(local_position),
					Vector3(-0.5, -0.5, 0.5) + Vector3(local_position),
				};
				int up_voxel_type = VoxelWorld::get_voxel_type(get_voxel(local_position + Vector3i(0, 1, 0)));
				int down_voxel_type = VoxelWorld::get_voxel_type(get_voxel(local_position + Vector3i(0, -1, 0)));
				int front_voxel_type = VoxelWorld::get_voxel_type(get_voxel(local_position + Vector3i(0, 0, -1)));
				int back_voxel_type = VoxelWorld::get_voxel_type(get_voxel(local_position + Vector3i(0, 0, 1)));
				int left_voxel_type = VoxelWorld::get_voxel_type(get_voxel(local_position + Vector3i(-1, 0, 0)));
				int right_voxel_type = VoxelWorld::get_voxel_type(get_voxel(local_position + Vector3i(1, 0, 0)));

				if (up_voxel_type == VoxelWorldData::EMPTY)
				{
					trigger_faces.push_back(vertexs[2]);
					trigger_faces.push_back(vertexs[1]);
					trigger_faces.push_back(vertexs[5]);
					trigger_faces.push_back(vertexs[2]);
					trigger_faces.push_back(vertexs[5]);
					trigger_faces.push_back(vertexs[6]);
				}
				if (down_voxel_type == VoxelWorldData::EMPTY)
				{
					trigger_faces.push_back(vertexs[0]);
					trigger_faces.push_back(vertexs[3]);
					trigger_faces.push_back(vertexs[7]);
					trigger_faces.push_back(vertexs[0]);
					trigger_faces.push_back(vertexs[7]);
					trigger_faces.push_back(vertexs[4]);
				}
				if (front_voxel_type == VoxelWorldData::EMPTY)
				{
					trigger_faces.push_back(vertexs[1]);
					trigger_faces.push_back(vertexs[2]);
					trigger_faces.push_back(vertexs[3]);
					trigger_faces.push_back(vertexs[1]);
					trigger_faces.push_back(vertexs[3]);
					trigger_faces.push_back(vertexs[0]);
				}
				if (back_voxel_type == VoxelWorldData::EMPTY)
				{
					trigger_faces.push_back(vertexs[6]);
					trigger_faces.push_back(vertexs[5]);
					trigger_faces.push_back(vertexs[4]);
					trigger_faces.push_back(vertexs[6]);
					trigger_faces.push_back(vertexs[4]);
					trigger_faces.push_back(vertexs[7]);
				}
				if (left_voxel_type == VoxelWorldData::EMPTY)
				{
					trigger_faces.push_back(vertexs[2]);
					trigger_faces.push_back(vertexs[6]);
					trigger_faces.push_back(vertexs[7]);
					trigger_faces.push_back(vertexs[2]);
					trigger_faces.push_back(vertexs[7]);
					trigger_faces.push_back(vertexs[3]);
				}
				if (right_voxel_type == VoxelWorldData::EMPTY)
				{
					trigger_faces.push_back(vertexs[5]);
					trigger_faces.push_back(vertexs[1]);
					trigger_faces.push_back(vertexs[0]);
					trigger_faces.push_back(vertexs[5]);
					trigger_faces.push_back(vertexs[0]);
					trigger_faces.push_back(vertexs[4]);
				}
			}
		}
	}
	Ref<ConcavePolygonShape3D> result;
	result.instantiate();
	result->reference();
	if (trigger_faces.size() > 0) {
		result->set_faces(trigger_faces);
	}
	return result;
}
/// <summary>
/// 返回区块内所有的节点实例
/// </summary>
/// <returns></returns>
void Chunk::generate_device()
{
	Ref<VoxelWorldData> voxel_world_data = voxel_world->get_voxel_world_data();
	if (voxel_world_data.is_null())
	{
		UtilityFunctions::printerr(UtilityFunctions::str("The voxel_world_data is null"));
		return;
	}
	Ref<PresetsData> presets_data = voxel_world->get_presets_data();
	Array device_presets = presets_data->get_device_presets();

	Vector3i chunk_size = voxel_world_data->get_chunk_size();
	for (int x = 0; x < chunk_size.x; x++)
	{
		for (int y = 0; y < chunk_size.y; y++)
		{
			for (int z = 0; z < chunk_size.z; z++)
			{
				Vector3i local_position = Vector3i(x, y, z);
				Voxel voxel = get_voxel(local_position);
				int type = VoxelWorld::get_voxel_type(voxel);
				int id = VoxelWorld::get_voxel_id(voxel);
				Vector3i rotation = VoxelWorld::get_voxel_rotation(voxel);

				Device* device = cast_to<Device>(devices[local_position]);

				if (type == VoxelWorldData::DEVICE)
				{
					Ref<DevicePreset> device_preset = device_presets[id];
					if (device != nullptr) {
						if (device->get_device_preset() != device_preset) {
							devices.erase(local_position);
							device->queue_free();
							device = nullptr;
						}
					}

					if (device == nullptr) {
						Node* node = device_preset->get_packed_scene()->instantiate();
						device = cast_to<Device>(node);
						if (device == nullptr)
						{
							UtilityFunctions::print("Cannot instantiate DevicePreset in Chunk" + chunk_position + "-Vectori" + local_position);
							continue;
						}
						device->set_device_preset(device_preset);
						devices[local_position] = device;

						device->set_position(local_position);
						device->set_rotation(rotation);
						add_child(device);
					}
				}
				else {
					if (device != nullptr) {
						devices.erase(local_position);
						device->queue_free();
					}
				}
			}
		}
	}
}

void Chunk::print_error(const String& value) const
{
}
