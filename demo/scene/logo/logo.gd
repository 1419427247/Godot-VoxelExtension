@tool
extends Node3D

@export
var voxel_block_data : StandardVoxelBlockData

func _ready():
	voxel_block_data.set_voxel(Vector3i(0,1,0),StandardVoxelBlockData.basics_voxel(0))
	voxel_block_data.set_voxel(Vector3i(1,0,0),StandardVoxelBlockData.basics_voxel(0))
	voxel_block_data.set_voxel(Vector3i(0,0,1),StandardVoxelBlockData.basics_voxel(0))
	
	voxel_block_data.set_voxel(Vector3i(0,2,0),StandardVoxelBlockData.model_voxel(2,Vector3i(0,45,0)))
	
	$MeshInstance3D.mesh = voxel_block_data.generate_mesh()

func _process(delta):
	pass
