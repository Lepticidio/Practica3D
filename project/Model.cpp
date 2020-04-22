#include "../lib/Model.h"
Model::Model(const std::shared_ptr<Mesh>& mesh) : m_pMesh(mesh)
{

}
void Model::draw()
{

	glm::mat4 modelMatrix = glm::translate(glm::mat4(), m_vPosition);

	modelMatrix = glm::rotate(modelMatrix, m_vRotation.x, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, m_vRotation.y, glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, m_vRotation.z, glm::vec3(0, 0, 1));
	modelMatrix = glm::scale(modelMatrix, m_vScale);
	State::modelMatrix = modelMatrix;
	m_pMesh->draw();
}