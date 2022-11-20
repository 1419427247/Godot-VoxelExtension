# VoxelExpansion
利用GDExpansion编写的高性能体素扩展，提供了相关的节点帮助用户生成自定义的体素世界而无需重新造轮子
# 如何配置？
我们可以在godot项目文件夹下新建一个文件夹并命名为`bin`，将编译好的动态链接库(*.dll)移动到`bin`文件夹内

然后在项目目录中新建一个文件并命名为`voxel.gdextension`
```
[configuration]
entry_symbol = "voxel_library_init"

[libraries]
windows.debug.x86_64 = "res://bin/voxel_expansion.windows.template_debug.dev.x86_64.dll"
windows.release.x86_64 = "res://bin/voxel_expansion.windows.template_release.dev.x86_64.dll"
```

打开Godot，我们使用快捷键`ctrl+A`打开创建节点窗口搜索`Voxel`
![](docs/屏幕截图%202022-11-16%20183112.png)

大功告成！我们可以看到自定义节点VoxelBlock和VoxelContainer

# 开始你的第一个体素世界
我们新建一个空场景，在里面添加一个`VoxelContainer`节点，在右侧的检查器中我们新建PresetsData

![](docs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202022-11-20%20173115.png)

| 属性名        | 说明             |
| ------------- | ---------------- |
| Materials     | 材质列表         |
| BasicsPresets | 基础体素预设列表 |
| ModelPresets  | 静态网格预设列表 |
| DevicePresets | 3D结点预设列表     |

我们尝试添加2个材质预设和1个基本体素预设用于我们的演示
![](docs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202022-11-20%20185226.png)

嗯，太好了，我们现在为`VoxelContainer`设置好了`PresetsData`属性，这样`VoxelBlock`就知道如何把体素画出来了，在我们的设置中ID为0的体素描述的是一个顶部是草坪，而其他面是大理石的正方形

我们希望它可以生成网格，以便于我们观察，在编辑器内为`VoxelContainer`添加一个子节点`MeshInstance3D`用于绘制网格

---
现在到了编码阶段，我们在`VoxelContainer`节点里添加一个内置脚本

```
@tool
extends VoxelContainer

func _ready():
	var voxel_block_data : StandardVoxelBlockData = StandardVoxelBlockData.new()
	var voxel_block : VoxelBlock = VoxelBlock.new()
	
	voxel_block_data.size = voxel_block_size
	
	voxel_block.set_voxel_block_data(voxel_block_data)

	voxel_block.set_voxel(Vector3i(0,0,0),voxel_block_data.basics_voxel(0))
	voxel_block.set_voxel(Vector3i(0,1,0),voxel_block_data.basics_voxel(0))
	voxel_block.set_voxel(Vector3i(1,0,0),voxel_block_data.basics_voxel(0))
	
	set_voxel_block(Vector3i(0,0,0),voxel_block)
	$MeshInstance3D.mesh = voxel_block.generate_mesh()

```

嗯嗯嗯，现在我们按`F5`运行场景，额，怎么怎么也看不见？哦~忘记加摄像机节点了，没关系，注意到之前脚本中的`@tool`了吗，我们可以直接在编辑器中生成网格，先在选项卡里关闭当前场景的选项卡，再重新打开场景~嗯嗯嗯，还不错

![](docs/%E5%B1%8F%E5%B9%95%E6%88%AA%E5%9B%BE%202022-11-20%20190510.png)

