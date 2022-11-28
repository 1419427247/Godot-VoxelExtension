extends Node3D

@export
var voxel_block_data : StandardVoxelBlockData

@export
var noise : Noise

@onready
var gd_controller : GDController = $GDController

func _ready():
	for x in voxel_block_data.size.x:
		for z in voxel_block_data.size.z:
			var height = (noise.get_noise_2d(x,z) + 0.5) * 3
			for y in range(height):
				voxel_block_data.set_voxel(Vector3i(x,y,z),StandardVoxelBlockData.basics_voxel(3))
			if(randi() % 6 == 0):
				for i in range(1,randi() % 8):
					voxel_block_data.set_voxel(Vector3i(x,i,z),StandardVoxelBlockData.basics_voxel(3))
	
	$VoxelBlock_0.mesh = voxel_block_data.generate_mesh()
	$VoxelBlock_0/StaticBody3D/CollisionShape3D.shape = voxel_block_data.generate_collider()
