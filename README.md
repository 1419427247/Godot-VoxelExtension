# Godot-VoxelExtension

<p align="center">
	<img src="docs/logo.png">
</p

[English](. /README.md)
[Chinese](. /README_CN.md)

I came up with a cool game a couple of months ago, but unfortunately the project fell through halfway. This extension was made when designing the map generation, which was initially written using GDScript, but for performance reasons I decided to rewrite it in C++ using Godot 4.0 GDExtension. Registered some relevant nodes for generating custom voxel meshes, hope it can help o(\*￣▽￣\*)o

***
Support the author: if you like it, point a star ⭐ it (＾∀＾＾)ノシ

QQ group：773700466
***

<figure class="half">
    <img src="docs/preview_2.png">
</figure>

# How to configure?
Create a new folder under godot project folder and name it `bin`, move the compiled dynamic link library (*.dll) to the `bin` folder, then create a new file in the project directory and name it `voxel.gdextension`
```
[configuration]
entry_symbol = "voxel_library_init"

[libraries]
windows.debug.x86_64 = "res://bin/voxel_expansion.windows.template_debug.x86_64.dll"
windows.release.x86_64 = "res://bin/voxel_expansion.windows.template_release.x86_64.dll"
```
Open the editor, if no error message is output then you're done!

# Start your first voxel block

Let's create a new empty scene, add a Node3D node to it, attach a script to the node and write at the beginning

`
@export
var voxel_block_data : StandardVoxelBlockData
`

Now we can edit the voxel preset directly in the inspector

! [](docs/1.png)

| Attribute Name | Description |
| ------------- | ---------------- |
| Materials | Material array |
| BasicsPresets | Array of Basics Presets |
| ModelPresets | Static mesh presets |
| DevicePresets | 3D Node Presets |

Now I want a grass cube, we can add two materials to the `materials` property and one preset to the `basics_presets` property

<img src="docs/2.png">

Well, great, we set the `PresetsData` property so that `VoxelBlockData` knows what we need the generated voxel mesh to look like (^v^)/

Now add a child node `MeshInstance3D` to the scene in the editor to display the mesh

The full code is as follows
```godot
@export
var voxel_block_data : StandardVoxelBlockData

func _ready():
	voxel_block_data.set_voxel(Vector3i(0,0,0),voxel_block_data.basics_voxel(0))
	$MeshInstance3D.mesh = voxel_block_data.generate_mesh()
```
Hmmmmmmmm, now we press `F6` to run the current scene being edited, uh, how come we can't see it? Uh-oh! I forgot to add the camera node, then add the environment! Well, well, well! Looks pretty good o(*￣▽￣*)ブ
<img src="docs/3.png">
ps:This grass mapping is a bit hard to see o(TヘTo)

Ok, now there is only one lone voxel in this block, not even enough for a standing position I'm afraid
```godot
for x in voxel_block_data.size.x:
	for z in voxel_block_data.size.z:
		voxel_block_data.set_voxel(Vector3i(x,0,z),voxel_block_data.basics_voxel(0))
$MeshInstance3D.mesh = voxel_block_data.generate_mesh()
````
<img src="docs/4.png">

That's nice o(^▽^)o

Now I suddenly want to add a cylinder, er, no reason suddenly want how to do it!!!

In the `model_presets` attribute of `voxel_block_data` add
<img src="docs/5.png">

Before generating the grid add
```godot
	for x in voxel_block_data.size.x:
		for z in voxel_block_data.size.z:
			if(randy() % 6 == 0):
				voxel_block_data.set_voxel(Vector3i(x,0,z),StandardVoxelBlockData.model_voxel(0))
```
So hard to see(ðŸ™')

<img src="docs/6.png">

tip:I secretly made `voxel_block_data` `size` a little bigger, one more thing, this model has too many vertices, it will slow down block loading qwq

# Start your first voxel world

start swinging

Translated with www.DeepL.com/Translator (free version)