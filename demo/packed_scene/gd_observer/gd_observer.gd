extends Node3D

class_name GDObserver

var gd_voxel_world : GDVoxelWorld

func _enter_tree():
	var node : Node = self
	while (node != null) and (node is GDVoxelWorld == false):
		node = node.get_parent()
	assert(node != null)
	gd_voxel_world = node
	gd_voxel_world.bind_gd_observers(self)
	
func _exit_tree():
	gd_voxel_world.unbind_gd_observers(self)
	gd_voxel_world = null
	
