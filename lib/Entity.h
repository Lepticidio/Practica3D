#pragma once
#include "glm/glm.hpp"
class Entity
{
protected:
	glm::vec3 m_vPosition;
	glm::vec3 m_vRotation;
	glm::vec3 m_vScale = glm::vec3(1,1,1);
public:
	Entity();
	virtual ~Entity() {}
	const glm::vec3& getPosition() const;
	void setPosition(const glm::vec3& pos);
	const glm::vec3& getRotation() const; // puede ser quat
	const void setRotation(const glm::vec3& rot); // puede ser quat
	void rotate(glm::vec3 _vRotation);
	const glm::vec3& getScale() const;
	void setScale(const glm::vec3& scale);
	void move(const glm::vec3& vec); // ver en las diapositivas
	virtual void update(float deltaTime) {}
	virtual void draw() {}
};

