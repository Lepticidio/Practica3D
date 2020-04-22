#include "../lib/Mesh.h"

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
void Mesh::draw()
{
	for (int i = 0; i < m_tBuffers.size(); i++)
	{
		Material material = *(m_tMaterials[i]);
		Shader shader = *(m_tMaterials[i]->getShader());
		m_tBuffers[i]->draw(shader);
	}
}