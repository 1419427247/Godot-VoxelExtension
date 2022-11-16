# VoxelExpansion
利用GDExpansion编写的高性能体素扩展，提供了相关的节点帮助用户生成自定义的体素世界而无需重新造轮子
# 快速上手
在godot项目文件夹下新建一个文件夹并命名为`bin`，将编译好的二进制文件移动到`bin`文件夹内

然后在项目目录中新建一个文件并命名为`voxel.gdextension`
```
[configuration]
entry_symbol = "voxel_library_init"

[libraries]
windows.debug.x86_64 = "res://bin/voxel_expansion.windows.template_debug.dev.x86_64.dll"
windows.release.x86_64 = "res://bin/voxel_expansion.windows.template_release.x86_64.dll"
```

打开Godot，我们使用快捷键`ctrl+A`打开创建节点窗口搜索`Voxel`
![图片](docs/屏幕截图%202022-11-16%20183112.png)

可以看到，大功告成！
