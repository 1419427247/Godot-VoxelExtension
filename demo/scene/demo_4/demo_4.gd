extends Node3D

@export
var noise : Noise

func _ready():
	pass
#	var standard_voxel_block_data = StandardVoxelBlockData.new()
#	standard_voxel_block_data.size = Vector3i(32,32,32)
#
#	standard_voxel_block_data.fill(standard_voxel_block_data.basics_voxel(0))
	

func _on_gd_voxel_world_on_load_voxel_block(gd_standard_voxel_block : GDStandardVoxelBlock):
	var key : Vector3i = gd_standard_voxel_block.get_key()
	if key.y == 0:
		for x in range(gd_standard_voxel_block.get_size().x):
			for z in range(gd_standard_voxel_block.get_size().z):
				var height = (noise.get_noise_2dv(Vector2(key.x,key.z) * Vector2(gd_standard_voxel_block.get_size().x,gd_standard_voxel_block.get_size().z) + Vector2(x,z)) + 0.5) * 16
				for y in range(height):
					var voxel_position = Vector3i(x,y,z)
					var voxel_global_position = key * gd_standard_voxel_block.get_size() + voxel_position
					gd_standard_voxel_block.set_voxel(Vector3i(x,y,z),gd_standard_voxel_block.basics_voxel(2,Vector3i(0,randi() % 4 * 90,0)))
	elif key.y < 0:
		gd_standard_voxel_block.fill(gd_standard_voxel_block.basics_voxel(0))
	elif key.y > 0:
		gd_standard_voxel_block.set_voxel(Vector3i(randi() % 16,randi() % 32,randi() % 16),gd_standard_voxel_block.basics_voxel(2,Vector3i(0,randi() % 4 * 90,0)))
