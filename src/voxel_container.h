#ifndef VOXEL_CONTAINER_H
#define VOXEL_CONTAINER_H

#include "presets_data.h"
#include "device.h"

class VoxelBlockData;
class VoxelContainer : public Node3D
{
	GDCLASS(VoxelContainer, Node3D);
private:
	Ref<PresetsData> presets_data;
	Vector3i voxel_block_size;
	bool isolated;

	Dictionary voxel_block_datas;
protected:
	static void _bind_methods();
public:
	VoxelContainer();
	~VoxelContainer();

	void set_presets_data(const Ref<PresetsData>& value);
	Ref<PresetsData> get_presets_data() const;

	void set_voxel_block_size(const Vector3i& value);
	Vector3i get_voxel_block_size() const;

	void set_isolated(const bool& value);
	bool is_isolated() const;

	void set_voxel_block_data(const Vector3i& key, const Ref<VoxelBlockData>& value);
	Ref<VoxelBlockData> get_voxel_block_data(const Vector3i& key) const;

	void set_voxel(const Vector3i& position, const Voxel& value);
	Voxel get_voxel(const Vector3i& position) const;

	Vector3i get_voxel_block_key(const Vector3i& position) const;

	VoxelBlockData* copy(const Vector3i& from, const Vector3i& to);
	void paste(const Ref<VoxelBlockData>& voxel_block_data, const Vector3i& position, const Vector3i& direction);
	void fill(const Voxel& voxel, const Vector3i& from, const Vector3i& to);
};

#endif // !VOXEL_CONTAINER_H