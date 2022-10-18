#include"register_types.h"


extern "C" {
	GDNativeBool GDN_EXPORT voxel_library_init(const GDNativeInterface* p_interface, const GDNativeExtensionClassLibraryPtr p_library, GDNativeInitialization* r_initialization) {
		godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

		init_obj.register_initializer(initialize_voxel_module);
		init_obj.register_terminator(uninitialize_voxel_module);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}

void initialize_voxel_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	ClassDB::register_class<VoxelWorld>();
	ClassDB::register_class<VoxelWorldData>();
	ClassDB::register_class<Chunk>();

	ClassDB::register_class<Preset>();
	ClassDB::register_class<MaterialPreset>();
	ClassDB::register_class<BasicsPreset>();
	ClassDB::register_class<MeshPreset>();
	ClassDB::register_class<DevicePreset>();
}

void uninitialize_voxel_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

}
