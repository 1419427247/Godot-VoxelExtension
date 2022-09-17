#include"register_types.h"

#include "chunk.h"
#include "voxel_world.h"
#include "material_perset.h"
#include "basics_perset.h"
#include "mesh_perset.h"

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
	ClassDB::register_class<Chunk>();

	ClassDB::register_class<MaterialPerset>();
	ClassDB::register_class<BasicsPerset>();
	ClassDB::register_class<MeshPerset>();
}

void uninitialize_voxel_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

}
