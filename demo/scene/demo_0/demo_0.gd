@tool
extends Node3D

@export
var voxel_block_data : StandardVoxelBlockData

func _ready():
	for x in voxel_block_data.size.x:
		for z in voxel_block_data.size.z:
			voxel_block_data.set_voxel(Vector3i(x,0,z),StandardVoxelBlockData.basics_voxel(0))

	for x in voxel_block_data.size.x:
		for z in voxel_block_data.size.z:
			if(randi() % 6 == 0):
				for i in range(1,randi() % 8):
					voxel_block_data.set_voxel(Vector3i(x,i,z),StandardVoxelBlockData.model_voxel(0))
	$MeshInstance3D.mesh = voxel_block_data.generate_mesh()

func _process(delta):
	pass


