#include "mesh.h"

void CPURenderer::Mesh::loadMesh(const std::string &path)
{
	tinyobj::LoadObj(mesh, mtl, path.c_str());
}

void CPURenderer::Mesh::loadTexture(const std::string & path)
{
	tex.load(path);
}
