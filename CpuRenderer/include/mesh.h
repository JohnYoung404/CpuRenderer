#pragma once
#include <tiny_obj_loader.h>

namespace CPURenderer
{
	class Mesh
	{
	public:
		std::vector<tinyobj::shape_t> mesh;
		std::vector<tinyobj::material_t> mtl;

		void LoadMesh(const std::string &path);
	};
}