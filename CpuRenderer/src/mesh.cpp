#include "mesh.h"
#include <iostream>

void CPURenderer::Mesh::loadMesh(const std::string &path)
{
	std::string warn, err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &mtl, &warn, &err, path.c_str());
	if (!warn.empty()) std::cout << warn << std::endl;
	if (!err.empty()) std::cout << err << std::endl;
	if (!ret) exit(1);
}

void CPURenderer::Mesh::loadTexture(const std::string & path)
{
	tex.load(path);
}
