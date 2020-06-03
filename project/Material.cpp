#include "../lib/Material.h"
#include <string>

Material::Material(const std::shared_ptr<Texture>& tex, const std::shared_ptr<Shader>& shader) : m_pTexture(tex), m_pShader(shader), m_vColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
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
	shader.setVec4(shader.getLocation("material.diffuse"), m_vColor);

	int iNumberLights = State::lights.size();
	
	
	shader.setInt(shader.getLocation("inumberlights"), iNumberLights);
	for (int i = 0; i < iNumberLights; i++)
	{
		std::string sPosDiffuse = "lights[" + std::to_string(i) + "].diffuse";
		std::string sPosPosition = "lights[" + std::to_string(i) + "].position";
		const char* cPosDiffuse = sPosDiffuse.c_str();
		const char* cPosPosition = sPosPosition.c_str();
		glm::vec3 vLightDiffuse = State::lights[i]->getColor();
		glm::vec3 vLightPosition = State::lights[i]->getPosition();
		float fLightAttenuation = State::lights[i]->getLinearAttenuation();
		shader.setVec3(shader.getLocation(cPosDiffuse), vLightDiffuse);
		shader.setVec3(shader.getLocation(cPosPosition), vLightPosition);
	}

}