@tool
extends Node3D

@export
var voxel_block_data : StandardVoxelBlockData

@export
var noise_0 : Noise

@export
var noise_1 : Noise

@onready
var gd_controller : GDController = $GDController

func _ready():
	for x in voxel_block_data.size.x:
		for z in voxel_block_data.size.z:
			var height = (noise_0.get_noise_2d(x,z) + 0.5) * 3 + (noise_1.get_noise_2d(x,z) + 0.5) * 4
			for y in range(height):
				voxel_block_data.set_voxel(Vector3i(x,y,z),StandardVoxelBlockData.basics_voxel(0))
			if(randi() % 6 == 0):
				for i in range(1,randi() % 8):
					voxel_block_data.set_voxel(Vector3i(x,i,z),StandardVoxelBlockData.model_voxel(0))
	
	_refresh()
	
var preview : CSGBox3D = CSGBox3D.new()

func _physics_process(delta):
	if(Engine.is_editor_hint()):
		return
	preview.size = Vector3(1.01,1.01,1.01)
	preview.transparency = 0.9
	
	var point = gd_controller.ray_cast.get_collision_point()
	var normal = gd_controller.ray_cast.get_collision_normal()
	var collider = gd_controller.ray_cast.get_collider()
	
	if preview.get_parent() != null:
		preview.get_parent().remove_child(preview)
	if(gd_controller.ray_cast.is_colliding() == false):
		return
	preview.position = VoxelBlockData.get_voxel_local_position(collider.global_transform,point,normal) + Vector3i(VoxelBlockData.normal_converted_to_voxel_block(collider.global_transform,normal))

	collider.add_child(preview)

	if Input.is_action_just_pressed("cursor_a"):
		voxel_block_data.set_voxel(Vector3i(preview.position),voxel_block_data.basics_voxel(1))
		_refresh()
		
	if Input.is_action_just_pressed("cursor_b"):
		print(VoxelBlockData.point_converted_to_voxel_block(collider.global_transform,point))
		voxel_block_data.set_voxel(VoxelBlockData.get_voxel_local_position(collider.global_transform,point,normal),voxel_block_data.empty_voxel())
	_refresh()

func _refresh():
	$VoxelBlock_0.mesh = voxel_block_data.generate_mesh()
	$VoxelBlock_0/StaticBody3D/CollisionShape3D.shape = voxel_block_data.generate_collider()

	$VoxelBlock_1.mesh = $VoxelBlock_0.mesh
	$VoxelBlock_1/StaticBody3D/CollisionShape3D.shape = $VoxelBlock_0/StaticBody3D/CollisionShape3D.shape
		
	$VoxelBlock_2.mesh = $VoxelBlock_0.mesh
	$VoxelBlock_2/StaticBody3D/CollisionShape3D.shape = $VoxelBlock_0/StaticBody3D/CollisionShape3D.shape

