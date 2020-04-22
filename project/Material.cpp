#include "../lib/Material.h"


Material::Material(const std::shared_ptr<Texture>& tex, const std::shared_ptr<Shader>& shader) : m_pTexture(tex), m_pShader(shader)
{

}
std::shared_ptr<Shader> Material::getShader()
{
	if (m_pShader)
	{
		return m_pShader;
	}
	else
	{
		return State::defaultShader;
	}
}
std::shared_ptr<Texture> Material::getTexture()
{
	return m_pTexture;
}
void Material::setShader(const std::shared_ptr<Shader>& shader)
{
	m_pShader = shader;
}
void Material::setTexture(const std::shared_ptr<Texture>& tex)
{
	m_pTexture = tex;
}
void Material::prepare(glm::vec3 _vPos, float _fScreenWidth, float _fScreenHeight, float _fAngle)
{
	(*m_pShader).use();
	m_pTexture->bind();
	m_pShader->setInt(m_pShader->getLocation("texSampler"), 0);


	glm::mat4 viewMatrix = glm::lookAt
	(
		glm::vec3(0, 1, 3), // the position of your camera

		glm::vec3(0, 0, 0),   // where you want to look at
		glm::vec3(0, 1, 0)       // up vector
	);


	glm::mat4 projectionMatrix = glm::perspective
	(
		glm::radians(45.0f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
		_fScreenWidth / _fScreenHeight,       // Aspect Ratio. Depends on the size of your window. 
		0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		1000.0f             // Far clipping plane. Keep as little as possible.
	);

	glm::mat4 modelMatrix = glm::translate(glm::mat4(), _vPos);
	modelMatrix = glm::rotate(modelMatrix, glm::radians(_fAngle), glm::vec3(0, 1, 0));
	glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
	Shader shader = * m_pShader;
	shader.setMatrix(shader.getLocation("mvp"), mvp);
}