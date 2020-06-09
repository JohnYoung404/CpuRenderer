#include "mesh.h"

void CPURenderer::Mesh::LoadMesh(const std::string &path)
{
	tinyobj::LoadObj(mesh, mtl, path.c_str());
}