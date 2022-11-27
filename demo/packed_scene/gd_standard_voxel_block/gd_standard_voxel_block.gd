extends Node3D
class_name GDStandardVoxelBlock

@export
var standard_voxel_block_data : StandardVoxelBlockData

@onready
var mesh_instance_3d : MeshInstance3D = $MeshInstance3D

@onready
var collision_shap_3d : CollisionShape3D = $StaticBody3D/CollisionShape3D

@onready
var static_body_3d : StaticBody3D = $StaticBody3D

@export
var debug : bool = false

func _ready():
	pass

func _process(delta):
	pass

func refresh():
	mesh_instance_3d.mesh = standard_voxel_block_data.generate_mesh()
	collision_shap_3d.shape = standard_voxel_block_data.generate_collider()

func set_voxel(position : Vector3i,voxel : int) -> void:
	standard_voxel_block_data.set_voxel(position,voxel)

func get_voxel(position : Vector3i) -> int:
	return standard_voxel_block_data.get_voxel(position)

func fill(voxel : int) -> void:
	standard_voxel_block_data.fill(voxel)

func is_filled(voxel : int) -> bool:
	return standard_voxel_block_data.is_filled(voxel)

func get_size() -> Vector3i:
	return standard_voxel_block_data.size

func get_key() -> Vector3i:
	return standard_voxel_block_data.get_key()

func get_voxel_container() -> VoxelContainer:
	return standard_voxel_block_data.get_voxel_container()
	
func empty_voxel() -> int:
	return 0

func basics_voxel(id : int,rotation : Vector3i = Vector3i()) -> int:
	return standard_voxel_block_data.basics_voxel(id,rotation)

func model_voxel(id : int,rotation : Vector3i = Vector3i()) -> int:
	return standard_voxel_block_data.model_voxel(id,rotation)
	
func device_voxel(id : int,rotation : Vector3i = Vector3i()) -> int:
	return standard_voxel_block_data.device_voxel(id,rotation)
