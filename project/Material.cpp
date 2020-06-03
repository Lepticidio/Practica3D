#include "../lib/Material.h"


Material::Material(const std::shared_ptr<Texture>& tex, const std::shared_ptr<Shader>& shader) : m_pTexture(tex), m_pShader(shader)
{

}
const glm::vec4& Material::getColor() const
{
	return m_vColor;
}
void Material::setColor(const glm::vec4& color)
{
	m_vColor = color;
}
uint8_t Material::getShininess() const
{
	return m_iShininess;
}
void Material::setShininess(uint8_t shininess)
{
	m_iShininess = shininess;
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


	glm::mat4 mv =  State::viewMatrix * State::modelMatrix;
	glm::mat4 projection = State::projectionMatrix;


	glm::mat4 normal = glm::transpose(glm::inverse(mv));

	//glm::mat4 mvp = State::projectionMatrix;
	Shader shader = * m_pShader;
	shader.setMatrix(shader.getLocation("mvMatrix"), mv);
	shader.setMatrix(shader.getLocation("projectionMatrix"), projection);
	shader.setMatrix(shader.getLocation("normalMatrix"), normal);
	shader.setVec3(shader.getLocation("globalAmbient"), State::ambient);
	shader.setVec3(shader.getLocation("material.diffuse"), m_vColor);

	int iNumberLights = State::lights.size();

	shader.setInt(shader.getLocation("inumberlights"), iNumberLights);
	for (int i = 0; i < iNumberLights; i++)
	{
		shader.setVec3(shader.getLocation("lights[i].diffuse"), State::lights[i]->getColor());
	}

}