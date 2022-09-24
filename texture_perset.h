#ifndef TEXTURE_PERSET_H
#define TEXTURE_PERSET_H

#include "perset.h"

class TexturePerset : public Perset
{
	GDCLASS(TexturePerset, Perset);
	enum TextureType {
		ALBEDO = 0,
		METALLIC = 1,
		ROUGHNESS = 2,
		EMISSION = 3,
		NORMAL = 4,
		RIM = 5,
		CLEARCOAT = 6,
		ANISOTROPY = 7,
		AMBIENT_OCCLUSION = 8,
		HEIGHT = 9,
		SUBSURF_SCATTERING = 10,
		REFRACTION = 11,
		DETAIL_ALBEDO = 12,
		DETAIL_NORMAL = 13,
	};
private:
	Array textures;
public:
	void set_texture(TextureType type, Ref<Texture> texture);
	void get_texture(TextureType type,Ref<Texture> texture);

protected:
	static void _bind_methods();
};

VARIANT_ENUM_CAST(TexturePerset,TextureType);

#endif // !TEXTURE_PERSET_H




