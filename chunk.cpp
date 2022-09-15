#include "chunk.h"
#include "voxel_world.h"
#include "basics_perset.h"
#include "material_perset.h"

void Chunk::instantiate_mesh_array(int index) {
	if (mesh_arrays[index].get_type() == Variant::NIL) {
		Array value = Array();
		value.resize(Mesh::ARRAY_MAX);
		value[Mesh::ARRAY_VERTEX] = PackedVector3Array();
		value[Mesh::ARRAY_TEX_UV] = PackedVector2Array();
		value[Mesh::ARRAY_NORMAL] = PackedVector3Array();
		mesh_arrays[index] = value;
	}
}

void Chunk::generate_brick_mesh(Ref<BasicsPerset> basics_perset, const Vector3i& relative_position, const Vector3i& rotation) {
	bool generate_flag;
	Vector3i basics_position = relative_position + chunk_position * woxel_world->chunk_size;

	generate_flag = true;
	Vector3i up_position = woxel_world->get_voxel_relative_position(basics_position, Vector3(0, 1, 0), rotation);
	int up_voxel_type = woxel_world->get_voxel_type(up_position);
	if (up_voxel_type != VoxelWorld::EMPTY) {
		int up_voxel_id = woxel_world->get_voxel_id(up_position);
		BasicsPerset* up_perset = cast_to<BasicsPerset>(woxel_world->basics_persets[up_voxel_id]);
		if (up_perset->mesh_type != BasicsPerset::MeshType::BRICK) {
			generate_flag = false;
		}
	}
	if (generate_flag == true) {
		int up_material_id = basics_perset->get_material_id("up");
		instantiate_mesh_array(up_material_id);
		BasicsPerset::draw_brick_up_mesh(mesh_arrays, up_material_id, relative_position, rotation);
	}

	Vector3i down_position = woxel_world->get_voxel_relative_position(basics_position, Vector3(0, -1, 0), rotation);
	int down_voxel_type = woxel_world->get_voxel_type(down_position);
	generate_flag = true;
	if (down_voxel_type != VoxelWorld::EMPTY) {
		int down_voxel_id = woxel_world->get_voxel_id(down_position);
		BasicsPerset* down_perset = cast_to<BasicsPerset>(woxel_world->basics_persets[down_voxel_id]);
		if (down_perset->mesh_type != BasicsPerset::MeshType::BRICK) {
			generate_flag = false;
		}
	}
	if (generate_flag == true) {
		int down_material_id = basics_perset->get_material_id("down");
		instantiate_mesh_array(down_material_id);
		BasicsPerset::draw_brick_down_mesh(mesh_arrays, down_material_id,relative_position, rotation);
	}

	Vector3i front_position = woxel_world->get_voxel_relative_position(basics_position, Vector3(0, 0, -1), rotation);
	int front_voxel_type = woxel_world->get_voxel_type(front_position);
	if (front_voxel_type != VoxelWorld::EMPTY) {
		int front_voxel_id = woxel_world->get_voxel_id(front_position);
		BasicsPerset* front_perset = cast_to<BasicsPerset>(woxel_world->basics_persets[front_voxel_id]);
		if (front_perset->mesh_type != BasicsPerset::MeshType::BRICK) {
			generate_flag = false;
		}
	}
	if (generate_flag == true) {
		int front_material_id = basics_perset->get_material_id("front");
		instantiate_mesh_array(front_material_id);
		BasicsPerset::draw_brick_front_mesh(mesh_arrays, front_material_id, relative_position, rotation);
	}


	Vector3i back_position = woxel_world->get_voxel_relative_position(basics_position, Vector3(0, 0, 1), rotation);
	int back_voxel_type = woxel_world->get_voxel_type(back_position);
	if (back_voxel_type != VoxelWorld::EMPTY) {
		int back_voxel_id = woxel_world->get_voxel_id(back_position);
		BasicsPerset* back_perset = cast_to<BasicsPerset>(woxel_world->basics_persets[back_voxel_id]);
		if (back_perset->mesh_type != BasicsPerset::MeshType::BRICK) {
			generate_flag = false;
		}
	}
	if (generate_flag == true) {
		int back_material_id = basics_perset->get_material_id("back");
		instantiate_mesh_array(back_material_id);
		BasicsPerset::draw_brick_back_mesh(mesh_arrays, back_material_id, relative_position, rotation);
	}

	Vector3i left_position = woxel_world->get_voxel_relative_position(basics_position, Vector3(-1, 0, 0), rotation);
	int left_voxel_type = woxel_world->get_voxel_type(left_position);
	if (left_voxel_type != VoxelWorld::EMPTY) {
		int left_voxel_id = woxel_world->get_voxel_id(left_position);
		BasicsPerset* left_perset = cast_to<BasicsPerset>(woxel_world->basics_persets[left_voxel_id]);
		if (left_perset->mesh_type != BasicsPerset::MeshType::BRICK) {
			generate_flag = false;
		}
	}
	if (generate_flag == true) {
		int left_material_id = basics_perset->get_material_id("left");
		instantiate_mesh_array(left_material_id);
		BasicsPerset::draw_brick_left_mesh(mesh_arrays, left_material_id, relative_position, rotation);
	}

	Vector3i right_position = woxel_world->get_voxel_relative_position(basics_position, Vector3(-1, 0, 0), rotation);
	int right_voxel_type = woxel_world->get_voxel_type(right_position);
	if (right_voxel_type != VoxelWorld::EMPTY) {
		int right_voxel_id = woxel_world->get_voxel_id(right_position);
		BasicsPerset* right_perset = cast_to<BasicsPerset>(woxel_world->basics_persets[right_voxel_id]);
		if (right_perset->mesh_type != BasicsPerset::MeshType::BRICK) {
			generate_flag = false;
		}
	}
	if (generate_flag == true) {
		int right_material_id = basics_perset->get_material_id("right");
		instantiate_mesh_array(right_material_id);
		BasicsPerset::draw_brick_right_mesh(mesh_arrays, right_material_id, relative_position, rotation);
	}

}

Chunk::Chunk() {

	this->state = State::NONE;
	this->woxel_world = nullptr;
	this->chunk_position = Vector3i(0, 0, 0);

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

Chunk::~Chunk() {

}

void Chunk::set_chunk_position(Vector3i value) {
	chunk_position = value;
}

Vector3i Chunk::get_chunk_position() {
	return chunk_position;
}

void Chunk::set_voxel(const int type, const int id, const Vector3i& relative_position, const Vector3i& rotation) {
	woxel_world->set_voxel(type, id, relative_position + chunk_position * woxel_world->chunk_size, rotation);
}

int Chunk::get_voxel_type(const Vector3i& relative_position) const {
	return woxel_world->get_voxel_type(relative_position + chunk_position * woxel_world->chunk_size);
}

int Chunk::get_voxel_id(const Vector3i& relative_position) const {
	return woxel_world->get_voxel_id(relative_position + chunk_position * woxel_world->chunk_size);
}

Vector3i Chunk::get_voxel_rotation(const Vector3i& relative_position) const {
	return woxel_world->get_voxel_rotation(relative_position + chunk_position * woxel_world->chunk_size);
}

void Chunk::generate_mesh() {
	mesh_arrays.clear();
	mesh_arrays.resize(woxel_world->material_persets.size());

	for (size_t x = 0; x < woxel_world->world_size.x; x++)
	{
		for (size_t y = 0; y < woxel_world->world_size.y; y++)
		{
			for (size_t z = 0; z < woxel_world->world_size.z; z++)
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
					Ref<BasicsPerset> basics_perset = woxel_world->basics_persets[id];
					generate_brick_mesh(basics_perset, relative_position, rotation);
					UtilityFunctions::print(mesh_arrays);
				}
				break;
				case VoxelWorld::EMPTY:

					break;
				}
			}
		}
	}


	Ref<ArrayMesh> mesh;
	mesh.instantiate();
	for (size_t i = 0; i < mesh_arrays.size(); i++)
	{
		if (mesh_arrays[i].get_type() != Variant::NIL) {
			Ref<ShaderMaterial> material = cast_to<MaterialPerset>(woxel_world->material_persets[i])->instance;
			mesh->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, mesh_arrays[i]);
			mesh->surface_set_material(mesh->get_surface_count() - 1, material);
		}
	}
	mesh_instance->set_mesh(mesh);
}
void Chunk::generate_collider() {

}
void Chunk::generate_trigger() {

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
		woxel_world = static_cast<VoxelWorld*>(get_parent());
	}
}