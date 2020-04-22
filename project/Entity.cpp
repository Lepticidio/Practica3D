#include "../lib/Entity.h"
Entity::Entity()
{

}
const glm::vec3& Entity::getPosition() const
{
	return m_vPosition;
}

void Entity::setPosition(const glm::vec3& pos)
{
	m_vPosition = pos;
}
const glm::vec3& Entity::getRotation() const
{
	return m_vRotation;
}
const void Entity::setRotation(const glm::vec3& rot)
{
	m_vRotation = rot;
}
void Entity::rotate(glm::vec3 _vRotation)
{
	m_vRotation += _vRotation;
}
const glm::vec3& Entity::getScale() const
{
	return m_vScale;
}
void Entity::setScale(const glm::vec3& scale)
{
	m_vScale = scale;
}
void Entity::move(const glm::vec3& vec)
{
	m_vPosition += vec;
}