#include "chunk.h"
#include "voxel_world.h"
#include "basics_perset.h"
#include "material_perset.h"

Chunk::Chunk() {

	this->state = State::NONE;
	this->voxel_world = nullptr;
	this->chunk_position = Vector3i(0, 0, 0);
}

Chunk::~Chunk() {

}

void Chunk::set_chunk_position(const Vector3i& value) {
	chunk_position = value;
}

Vector3i Chunk::get_chunk_position() const {
	return chunk_position;
}

void Chunk::set_voxel(const int& type, const int& id, const Vector3i& relative_position, const Vector3i& rotation) {
	voxel_world->set_voxel(type, id, relative_position + chunk_position * voxel_world->chunk_size, rotation);
}

int Chunk::get_voxel_type(const Vector3i& relative_position) const {
	return voxel_world->get_voxel_type(relative_position + chunk_position * voxel_world->chunk_size);
}

int Chunk::get_voxel_id(const Vector3i& relative_position) const {
	return voxel_world->get_voxel_id(relative_position + chunk_position * voxel_world->chunk_size);
}

Vector3i Chunk::get_voxel_rotation(const Vector3i& relative_position) const {
	return voxel_world->get_voxel_rotation(relative_position + chunk_position * voxel_world->chunk_size);
}

Vector3i Chunk::get_voxel_position(const Vector3& position, const Vector3& normal) const
{
	Vector3 voxel_position = position - get_position() + chunk_position * voxel_world->chunk_size;
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

void Chunk::generate_mesh() {
	mesh_arrays.clear();
	mesh_arrays.resize(voxel_world->material_persets.size());

	for (size_t x = 0; x < voxel_world->chunk_size; x++)
	{
		for (size_t y = 0; y < voxel_world->chunk_size; y++)
		{
			for (size_t z = 0; z < voxel_world->chunk_size; z++)
			{
				Vector3i relative_position = Vector3i(x, y, z);
				int type = get_voxel_type(relative_position);
				if (type == VoxelWorld::EMPTY)
				{
					continue;
				}
				int id = get_voxel_id(relative_position);
				Vector3i rotation = get_voxel_rotation(relative_position);
				switch (type)
				{
				case VoxelWorld::BASICS:
				{
					Ref<BasicsPerset> basics_perset = voxel_world->basics_persets[id];
					draw_mesh(basics_perset, relative_position, rotation);
					break;
				}
				case VoxelWorld::MESH:
				{
					break;
				}
				case VoxelWorld::DEVICE:
				{
					break;
				}
				}
			}
		}
	}

	Ref<ArrayMesh> mesh;
	mesh.instantiate();
	for (size_t i = 0; i < mesh_arrays.size(); i++)
	{
		if (mesh_arrays[i].get_type() != Variant::NIL) {
			Array arrays = mesh_arrays[i];
			arrays[ArrayMesh::ARRAY_VERTEX] = PackedVector3Array((Array)arrays[ArrayMesh::ARRAY_VERTEX]);
			arrays[ArrayMesh::ARRAY_NORMAL] = PackedVector3Array((Array)arrays[ArrayMesh::ARRAY_NORMAL]);
			arrays[ArrayMesh::ARRAY_TEX_UV] = PackedVector2Array((Array)arrays[ArrayMesh::ARRAY_TEX_UV]);
			Ref<ShaderMaterial> material = cast_to<MaterialPerset>(voxel_world->material_persets[i])->instance;
			mesh->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, arrays);
			mesh->surface_set_material(mesh->get_surface_count() - 1, material);
		}
	}
	mesh_instance->set_mesh(mesh);
}

void Chunk::generate_collider() {
	Ref<ArrayMesh> mesh = mesh_instance->get_mesh();
	if (mesh->get_surface_count() != 0) {
		Ref<ConcavePolygonShape3D> concave_polygon_shape;
		concave_polygon_shape.instantiate();
		concave_polygon_shape->set_faces(mesh->get_faces());
		collision_shap->set_shape(concave_polygon_shape);
	}
}

void Chunk::generate_trigger() {
	PackedVector3Array trigger_faces;
	for (size_t x = 0; x < voxel_world->chunk_size; x++)
	{
		for (size_t y = 0; y < voxel_world->chunk_size; y++)
		{
			for (size_t z = 0; z < voxel_world->chunk_size; z++)
			{
				Vector3i relative_position = Vector3i(x, y, z);
				int type = get_voxel_type(relative_position);
				if (type == VoxelWorld::EMPTY || VoxelWorld::BASICS) {
					continue;
				}
				Vector3 vertexs[] = {
					Vector3(0.5, -0.5, -0.5) + Vector3(relative_position),
					Vector3(0.5, 0.5, -0.5) + Vector3(relative_position),
					Vector3(-0.5, 0.5, -0.5) + Vector3(relative_position),
					Vector3(-0.5, -0.5, -0.5) + Vector3(relative_position),
					Vector3(0.5, -0.5, 0.5) + Vector3(relative_position),
					Vector3(0.5, 0.5, 0.5) + Vector3(relative_position),
					Vector3(-0.5, 0.5, 0.5) + Vector3(relative_position),
					Vector3(-0.5, -0.5, 0.5) + Vector3(relative_position),
				};
				int up_voxel_type = get_voxel_type(relative_position + Vector3i(0, 1, 0));
				int down_voxel_type = get_voxel_type(relative_position + Vector3i(0, -1, 0));
				int front_voxel_type = get_voxel_type(relative_position + Vector3i(0, 0, -1));
				int back_voxel_type = get_voxel_type(relative_position + Vector3i(0, 0, 1));
				int left_voxel_type = get_voxel_type(relative_position + Vector3i(-1, 0, 0));
				int right_voxel_type = get_voxel_type(relative_position + Vector3i(1, 0, 0));

				if (up_voxel_type == VoxelWorld::EMPTY)
				{
					trigger_faces.push_back(vertexs[2]);
					trigger_faces.push_back(vertexs[1]);
					trigger_faces.push_back(vertexs[5]);
					trigger_faces.push_back(vertexs[2]);
					trigger_faces.push_back(vertexs[5]);
					trigger_faces.push_back(vertexs[6]);
				}
				if (down_voxel_type == VoxelWorld::EMPTY)
				{
					trigger_faces.push_back(vertexs[0]);
					trigger_faces.push_back(vertexs[3]);
					trigger_faces.push_back(vertexs[7]);
					trigger_faces.push_back(vertexs[0]);
					trigger_faces.push_back(vertexs[7]);
					trigger_faces.push_back(vertexs[4]);
				}
				if (front_voxel_type == VoxelWorld::EMPTY)
				{
					trigger_faces.push_back(vertexs[1]);
					trigger_faces.push_back(vertexs[2]);
					trigger_faces.push_back(vertexs[3]);
					trigger_faces.push_back(vertexs[1]);
					trigger_faces.push_back(vertexs[3]);
					trigger_faces.push_back(vertexs[0]);
				}
				if (back_voxel_type == VoxelWorld::EMPTY)
				{
					trigger_faces.push_back(vertexs[6]);
					trigger_faces.push_back(vertexs[5]);
					trigger_faces.push_back(vertexs[4]);
					trigger_faces.push_back(vertexs[6]);
					trigger_faces.push_back(vertexs[4]);
					trigger_faces.push_back(vertexs[7]);
				}
				if (left_voxel_type == VoxelWorld::EMPTY)
				{
					trigger_faces.push_back(vertexs[2]);
					trigger_faces.push_back(vertexs[6]);
					trigger_faces.push_back(vertexs[7]);
					trigger_faces.push_back(vertexs[2]);
					trigger_faces.push_back(vertexs[7]);
					trigger_faces.push_back(vertexs[3]);
				}
				if (right_voxel_type == VoxelWorld::EMPTY)
				{
					trigger_faces.push_back(vertexs[5]);
					trigger_faces.push_back(vertexs[1]);
					trigger_faces.push_back(vertexs[0]);
					trigger_faces.push_back(vertexs[5]);
					trigger_faces.push_back(vertexs[0]);
					trigger_faces.push_back(vertexs[4]);
				}
				if (trigger_faces.size() > 0) {
					Ref<ConcavePolygonShape3D> concave_polygon_shape;
					concave_polygon_shape.instantiate();
					concave_polygon_shape->set_faces(trigger_faces);
					trigger_shap->set_shape(concave_polygon_shape);
				}
			}
		}
	}
}

Array Chunk::get_mesh_array(const int& index) {
	Array result;
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

void Chunk::draw_mesh(const Ref<BasicsPerset>& basics_perset, const Vector3i& relative_position, const Vector3i& rotation) {
	Vector3i basics_position = relative_position + chunk_position * voxel_world->chunk_size;

	Vector3i up_position = voxel_world->get_voxel_relative_position(basics_position, Vector3(0, 1, 0), rotation);
	int up_voxel_type = voxel_world->get_voxel_type(up_position);
	if (up_voxel_type != VoxelWorld::BASICS) {
		int up_material_id = basics_perset->get_material_id(BasicsPerset::UP);
		Array arrays = get_mesh_array(up_material_id);
		BasicsPerset::draw_mesh(BasicsPerset::UP, arrays, relative_position, rotation);
	}

	Vector3i down_position = voxel_world->get_voxel_relative_position(basics_position, Vector3(0, -1, 0), rotation);
	int down_voxel_type = voxel_world->get_voxel_type(down_position);
	if (down_voxel_type != VoxelWorld::BASICS) {
		int down_material_id = basics_perset->get_material_id(BasicsPerset::DOWN);
		Array arrays = get_mesh_array(down_material_id);
		BasicsPerset::draw_mesh(BasicsPerset::DOWN, arrays, relative_position, rotation);
	}

	Vector3i front_position = voxel_world->get_voxel_relative_position(basics_position, Vector3(0, 0, -1), rotation);
	int front_voxel_type = voxel_world->get_voxel_type(front_position);
	if (front_voxel_type != VoxelWorld::BASICS) {
		int front_material_id = basics_perset->get_material_id(BasicsPerset::FRONT);
		Array arrays = get_mesh_array(front_material_id);
		BasicsPerset::draw_mesh(BasicsPerset::FRONT, arrays, relative_position, rotation);
	}


	Vector3i back_position = voxel_world->get_voxel_relative_position(basics_position, Vector3(0, 0, 1), rotation);
	int back_voxel_type = voxel_world->get_voxel_type(back_position);
	if (back_voxel_type != VoxelWorld::BASICS) {
		int back_material_id = basics_perset->get_material_id(BasicsPerset::BACK);
		Array arrays = get_mesh_array(back_material_id);
		BasicsPerset::draw_mesh(BasicsPerset::BACK, arrays, relative_position, rotation);
	}

	Vector3i left_position = voxel_world->get_voxel_relative_position(basics_position, Vector3(-1, 0, 0), rotation);
	int left_voxel_type = voxel_world->get_voxel_type(left_position);
	if (left_voxel_type != VoxelWorld::BASICS) {
		int left_material_id = basics_perset->get_material_id(BasicsPerset::LEFT);
		Array arrays = get_mesh_array(left_material_id);
		BasicsPerset::draw_mesh(BasicsPerset::LEFT, arrays, relative_position, rotation);
	}

	Vector3i right_position = voxel_world->get_voxel_relative_position(basics_position, Vector3(1, 0, 0), rotation);
	int right_voxel_type = voxel_world->get_voxel_type(right_position);
	if (right_voxel_type != VoxelWorld::BASICS) {
		int right_material_id = basics_perset->get_material_id(BasicsPerset::RIGHT);
		Array arrays = get_mesh_array(right_material_id);
		BasicsPerset::draw_mesh(BasicsPerset::RIGHT, arrays, relative_position, rotation);
	}
}


void Chunk::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_chunk_position", "value"), &Chunk::set_chunk_position);

	ClassDB::bind_method(D_METHOD("get_chunk_position"), &Chunk::get_chunk_position);

	ClassDB::bind_method(D_METHOD("generate_mesh"), &Chunk::generate_mesh);
	ClassDB::bind_method(D_METHOD("generate_collider"), &Chunk::generate_collider);
	ClassDB::bind_method(D_METHOD("generate_trigger"), &Chunk::generate_trigger);

	ClassDB::add_property("Chunk", PropertyInfo(Variant::VECTOR3I, "chunk_position"), "set_chunk_position", "get_chunk_position");
}

void Chunk::_notification(int p_what) {
	if (p_what == NOTIFICATION_ENTER_TREE)
	{
		voxel_world = static_cast<VoxelWorld*>(get_parent());
		this->mesh_instance = memnew(MeshInstance3D());

		this->collision = memnew(StaticBody3D());
		this->collision_shap = memnew(CollisionShape3D());

		this->trigger = memnew(Area3D());
		this->trigger_shap = memnew(CollisionShape3D());

		this->collision->add_child(this->collision_shap);
		this->trigger->add_child(this->trigger_shap);

		add_child(this->trigger);
		add_child(this->collision);
		add_child(this->mesh_instance);
	}
}