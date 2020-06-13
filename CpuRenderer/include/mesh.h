#pragma once
#include <tiny_obj_loader.h>
#include "texture.h"

namespace CPURenderer
{
	class Mesh
	{
	public:
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> mtl;
		tinyobj::attrib_t attrib;
		Texture tex;

		void loadMesh(const std::string &path);
		void loadTexture(const std::string &path);
	};
}