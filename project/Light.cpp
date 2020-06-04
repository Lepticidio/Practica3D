#include "../lib/Light.h"


LightType Light::getType() const
{
	return m_eLightType;
}
void Light::setType(LightType type)
{
	m_eLightType = type;
}
const glm::vec3& Light::getColor() const
{
	return m_vColor;
}
void Light::setColor(const glm::vec3& color)
{
	m_vColor = color;
}
const glm::vec3& Light::getDirection() const
{
	return m_vDirection;
}
void Light::setDirection(const glm::vec3& direction)
{
	m_vDirection = direction;
}
float Light::getLinearAttenuation() const
{
	return m_fLinearAttenuation;
}
void Light::setLinearAttenuation(float att)
{
	m_fLinearAttenuation = att;
}
void Light::prepare(int index, std::shared_ptr<Shader>& shader) const
{

}