#include "../lib/Material.h"


Material::Material(const std::shared_ptr<Texture>& tex, const std::shared_ptr<Shader>& shader) : m_pTexture(tex), m_pShader(shader)
{

}
std::shared_ptr<Shader> Material::getShader()
{
	return m_pShader;
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
	(*m_pShader).use();
	m_pTexture->bind();
	m_pShader->setInt(m_pShader->getLocation("texSampler"), 0);
}