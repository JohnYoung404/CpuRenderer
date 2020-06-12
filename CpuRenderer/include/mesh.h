#pragma once
#include <tiny_obj_loader.h>
#include "texture.h"

namespace CPURenderer
{
	class Mesh
	{
	public:
		std::vector<tinyobj::shape_t> mesh;
		std::vector<tinyobj::material_t> mtl;
		Texture tex;

		void loadMesh(const std::string &path);
		void loadTexture(const std::string &path);
	};
}