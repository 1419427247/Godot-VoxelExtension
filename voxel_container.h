#ifndef VOXEL_CONTAINER_H
#define VOXEL_CONTAINER_H

#include "voxel_container_data.h"
#include "presets_data.h"

class VoxelContainer : public Node3D
{
	GDCLASS(VoxelContainer, Node3D)
private:

protected:
	Ref<PresetsData> presets_data;
	Vector3i chunk_size;
	bool isolated;

	static void _bind_methods();
public:
	VoxelContainer();
	~VoxelContainer();

	void set_presets_data(const Ref<PresetsData>& value);
	Ref<PresetsData> get_presets_data() const;

	void set_chunk_size(const Vector3i& value);
	Vector3i get_chunk_size() const;


	void set_isolated(const bool& value);
	bool is_isolated() const;

	virtual void set_voxel(const Vector3i& position, const Voxel& value);
	virtual Voxel get_voxel(const Vector3i& position) const;
	
	VoxelContainerData* copy(const Vector3i& from, const Vector3i& to);
	void paste(const Ref<VoxelContainerData>& voxel_container_data, const Vector3i& position, const Vector3i& direction);

	static Vector3i get_voxel_direction(const Vector3i& direction, const Vector3i& rotation);

	static int get_voxel_type(const Voxel& value);
	static int get_voxel_id(const Voxel& value);
	static Vector3i get_voxel_rotation(const Voxel& value);
	static int get_voxel_flag(const Voxel& value);

	static Voxel empty_voxel();
	static Voxel basics_voxel(const int& id, const Vector3i& rotation = Vector3i(), const int& flag = 0);
	static Voxel mesh_voxel(const int& id, const Vector3i& rotation = Vector3i(), const int& flag = 0);
	static Voxel device_voxel(const int& id, const Vector3i& rotation = Vector3i(), const int& flag = 0);
};

#endif // !VOXEL_CONTAINER_H