#define TINYOBJLOADER_IMPLEMENTATION

#include "../lib/Mesh.h"
#include "../../lib/tinyobjloader-master/tiny_obj_loader.h"

void Mesh::addBuffer(const std::shared_ptr<Buffer>& buffer, const std::shared_ptr<Material>& material)
{
	m_tBuffers.push_back(buffer);
	m_tMaterials.push_back(material);
}
size_t Mesh::getNumBuffers() const
{
	return m_tBuffers.size();
}
const std::shared_ptr<Buffer>& Mesh::getBuffer(size_t index) const
{
	return m_tBuffers[index];
}
std::shared_ptr<Buffer>& Mesh::getBuffer(size_t index)
{
	return m_tBuffers[index];
}
const std::shared_ptr<Material>& Mesh::getMaterial(size_t index) const
{
	return m_tMaterials[index];
}
std::shared_ptr<Material>& Mesh::getMaterial(size_t index)
{
	return m_tMaterials[index];
}
void Mesh::setMaterial(std::shared_ptr<Material>& _pMaterial, size_t index)
{
	if (index < m_tMaterials.size())
	{
		m_tMaterials[index] = _pMaterial;
	}
}
std::shared_ptr<Mesh> Mesh::load(const char* filename, const std::shared_ptr<Shader>& shader)
{
	std::shared_ptr<Mesh> pResult = std::make_shared<Mesh>();
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::vector<Vertex> tVertex;
	std::vector<uint16_t> tIndex;
	std::string warn, err;
	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename)) 
	{
		throw std::runtime_error(warn + err);
	}
	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			Vertex* vertexAux = new Vertex();
			vertexAux->m_vPosition.x = attrib.vertices[3 * index.vertex_index + 0];
			vertexAux->m_vPosition.y = attrib.vertices[3 * index.vertex_index + 1];
			vertexAux->m_vPosition.z = attrib.vertices[3 * index.vertex_index + 2];
			vertexAux->m_vNormal.x = attrib.normals[3 * index.normal_index + 0];
			vertexAux->m_vNormal.y = attrib.normals[3 * index.normal_index + 1];
			vertexAux->m_vNormal.z = attrib.normals[3 * index.normal_index + 2];
			vertexAux->m_vColor.r = 1;
			vertexAux->m_vColor.g = 1;
			vertexAux->m_vColor.b = 1;
			vertexAux->m_vTextureCoord.x = attrib.texcoords[2 *
				index.texcoord_index + 0];
			vertexAux->m_vTextureCoord.y = attrib.texcoords[2 *
				index.texcoord_index + 1];
			tVertex.push_back(*vertexAux);
			tIndex.push_back(tIndex.size());
		}
	}
	std::shared_ptr<Material> pMaterial = std::make_shared<Material>(nullptr, shader);
	pResult->addBuffer(std::make_shared<Buffer>(tVertex, tIndex), pMaterial);
	return pResult;
}
void Mesh::draw()
{
	for (int i = 0; i < m_tBuffers.size(); i++)
	{
		Material material = *(m_tMaterials[i]);
		Shader shader = *(m_tMaterials[i]->getShader());
		material.prepare();
		m_tBuffers[i]->draw(shader);
	}
}