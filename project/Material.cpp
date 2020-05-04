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
void Material::prepare()
{
	if (!m_pShader)
	{
		m_pShader = State::defaultShader;
	}

	(*m_pShader).use();
	if (m_pTexture)
	{
		m_pTexture->bind();

	}
	m_pShader->setInt(m_pShader->getLocation("texSampler"), 0);


	glm::mat4 mvp = State::projectionMatrix * State::viewMatrix * State::modelMatrix;
	Shader shader = * m_pShader;
	shader.setMatrix(shader.getLocation("mvp"), mvp);
}