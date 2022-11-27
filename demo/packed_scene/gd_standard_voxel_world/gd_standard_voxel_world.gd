extends VoxelContainer

class_name GDVoxelWorld

const GDStandardVoxelBlockScene = preload("res://packed_scene/gd_standard_voxel_block/gd_standard_voxel_block.tscn")

signal on_load_voxel_block(gd_standard_voxel_block : GDStandardVoxelBlock)
signal on_unload_voxel_block(gd_standard_voxel_block : GDStandardVoxelBlock)

@export
var sight_distance : Vector3i = Vector3i(8,2,8)

var gd_voxel_blocks : Dictionary = {}

var gd_observers : Array[Node3D] = []

var threads : Array[Thread] = [
	Thread.new(),
	Thread.new(),
	Thread.new(),
]
var refresh_queue : Array[GDStandardVoxelBlock] = []
var refresh_queue_mutex : Mutex = Mutex.new()
func _ready():
	for thread in threads:
		thread.start(_refresh_update)

func _refresh_update():
	while true:
		refresh_queue_mutex.lock()
		var gd_standard_voxel_block : GDStandardVoxelBlock
		if refresh_queue.size() > 0:
			gd_standard_voxel_block = refresh_queue.pop_front()
		else:
			refresh_queue_mutex.unlock()
			continue
		refresh_queue_mutex.unlock()

		on_load_voxel_block.emit(gd_standard_voxel_block)
		if(gd_standard_voxel_block.is_filled(0)):
			continue
		gd_standard_voxel_block.refresh()

func _process(delta):
	if(refresh_queue.size() > 15):
		return
	for gd_observer in gd_observers:
		var key = get_voxel_block_key(Vector3i(gd_observer.global_position))
		
		var keys : Array[Vector3i] = []
		for x in range(-sight_distance.x,sight_distance.x + 1):
			for y in range(-sight_distance.y,sight_distance.y + 1):
				for z in range(-sight_distance.z,sight_distance.z + 1):
					keys.push_back(Vector3i(x,y,z))
		keys.sort_custom(func(left : Vector3i,right : Vector3i):
				return left.length_squared() < right.length_squared()
		)
		for i in keys.size():
			if(gd_voxel_blocks.has(keys[i] + key) == false):
				_load_voxel_block(keys[i] + key)
				break

func _load_voxel_block(key : Vector3i,standard_voxel_block_data : StandardVoxelBlockData = null):
	var gd_standard_voxel_block : GDStandardVoxelBlock = GDStandardVoxelBlockScene.instantiate()
	if standard_voxel_block_data == null:
		standard_voxel_block_data = StandardVoxelBlockData.new()
	gd_standard_voxel_block.standard_voxel_block_data = standard_voxel_block_data
	gd_standard_voxel_block.standard_voxel_block_data.size = voxel_block_size
	
	set_voxel_block_data(key,gd_standard_voxel_block.standard_voxel_block_data);
	gd_standard_voxel_block.position = key * voxel_block_size
	
	add_child(gd_standard_voxel_block)
	
	refresh_queue_mutex.lock()
	gd_voxel_blocks[key] = gd_standard_voxel_block
	refresh_queue.push_back(gd_standard_voxel_block)
	refresh_queue_mutex.unlock()

func bind_gd_observers(gd_observer):
	gd_observers.push_back(gd_observer)

func unbind_gd_observers(gd_observer):
	gd_observers.erase(gd_observer)
