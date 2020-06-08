#include "mesh.h"

void CPURenderer::Mesh::LoadMesh(const std::string &path)
{
	std::vector<tinyobj::shape_t> mesh;
	std::vector<tinyobj::material_t> mtl;
	tinyobj::LoadObj(mesh, mtl, path.c_str());
}
