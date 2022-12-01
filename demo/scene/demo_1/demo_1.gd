extends Node3D

@export
var voxel_block_data : StandardVoxelBlockData

@export
var noise : Noise

func _ready():
	
	voxel_block_data.set_voxel(Vector3i(),StandardVoxelBlockData.basics_voxel(0))
	var mesh : ArrayMesh = voxel_block_data.generate_mesh()
	print(mesh.surface_get_arrays(1))
	
	for x in voxel_block_data.size.x:
		for z in voxel_block_data.size.z:
			var height = (noise.get_noise_2d(x,z) + 0.5) * 8
			for y in range(height):
				voxel_block_data.set_voxel(Vector3i(x,y,z),StandardVoxelBlockData.basics_voxel(0))

			if(randi() % 64 == 0):
				_build_tree(voxel_block_data,Vector3i(x,height,z))
	
	$MeshInstance3D.mesh = mesh
#	$StaticBody3D/CollisionShape3D.shape = voxel_block_data.generate_collider()
	
#[[
#	(0.5, -0.5, -0.5), (-0.5, -0.5, -0.5), (-0.5, -0.5, 0.5),
#	 (0.5, -0.5, -0.5), (-0.5, -0.5, 0.5), (0.5, -0.5, 0.5),
#
#	 (0.5, 0.5, -0.5), (-0.5, 0.5, -0.5), (-0.5, -0.5, -0.5),
#	 (0.5, 0.5, -0.5), (-0.5, -0.5, -0.5), (0.5, -0.5, -0.5),
#
#	 (-0.5, 0.5, 0.5), (0.5, 0.5, 0.5), (0.5, -0.5, 0.5),
#	 (-0.5, 0.5, 0.5), (0.5, -0.5, 0.5), (-0.5, -0.5, 0.5),
#
#	 (-0.5, 0.5, -0.5), (-0.5, 0.5, 0.5), (-0.5, -0.5, 0.5),
#	 (-0.5, 0.5, -0.5), (-0.5, -0.5, 0.5), (-0.5, -0.5, -0.5),
#
#	 (0.5, 0.5, 0.5), (0.5, 0.5, -0.5), (0.5, -0.5, -0.5), 
#	(0.5, 0.5, 0.5), (0.5, -0.5, -0.5), (0.5, -0.5, 0.5)
#], [
#	(0, -1, -0.000015), (0, -1, -0.000015), (0, -1, -0.000015),
#	 (0, -1, -0.000015), (0, -1, -0.000015), (0, -1, -0.000015),
#
#	 (0, 0, -1), (0, 0, -1), (0, 0, -1), 
#	(0, 0, -1), (0, 0, -1), (0, 0, -1), 
#
#	(-0.000015, -0.000015, 1), (-0.000015, -0.000015, 1),(-0.000015, -0.000015, 1), 
#	(-0.000015, -0.000015, 1), (-0.000015, -0.000015, 1),(-0.000015, -0.000015, 1), 
#
#	(-1, 0, -0.000015),(-1, 0, -0.000015), (-1, 0, -0.000015), 
#	(-1, 0, -0.000015), (-1, 0, -0.000015), (-1, 0, -0.000015), 
#
#	(1, 0, -0.000015), (1, 0, -0.000015), (1, 0, -0.000015), 
#	(1, 0, -0.000015), (1, 0, -0.000015), (1, 0, -0.000015)
#
#], <null>, <null>, [
#(0, 0), (1, 0), (1, 1), 
#(0, 0), (1, 1), (0, 1),
#
# (0, 0), (1, 0), (1, 1),
# (0, 0), (1, 1), (0, 1), 
#
#(0, 0), (1, 0), (1, 1), 
#(0, 0), (1, 1), (0, 1), 
#
#(0, 0), (1, 0), (1, 1), 
#(0, 0), (1, 1), (0, 1), 
#
#(0, 0), (1, 0), (1, 1), 
#(0, 0), (1, 1), (0, 1)
#], <null>, <null>, <null>, <null>, <null>, <null>, <null>, <null>]

func _build_tree(voxel_block_data : StandardVoxelBlockData,bottom : Vector3i):
	var top = bottom.y + randi() % 2 + 4
	for y in range(bottom.y,top):
		voxel_block_data.set_voxel(Vector3i(bottom.x,y,bottom.z),StandardVoxelBlockData.model_voxel(1))
	for y in range(bottom.y + 4,bottom.y + randi() % 4 + 6):
		var width = randi() % 1 + 1
		for x in range(-1 * width,2 * width):
			for z in range(-1 * width,2 * width):
				voxel_block_data.set_voxel(Vector3i(bottom.x + x,y,bottom.z + z),StandardVoxelBlockData.basics_voxel(1))
				
