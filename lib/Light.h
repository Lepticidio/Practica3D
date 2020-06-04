#pragma once
#include "Shader.h"
#include "Entity.h"
enum LightType { DIRECTIONAL, POINT };
class Light : public Entity
{
	float m_fLinearAttenuation;
	glm::vec3 m_vColor;
	glm::vec3 m_vDirection;
	LightType m_eLightType;

public:
	LightType getType() const;
	void setType(LightType type);
	const glm::vec3& getColor() const;
	const glm::vec3& getDirection() const;
	void setColor(const glm::vec3& color);
	void setDirection(const glm::vec3& direction);
	float getLinearAttenuation() const;
	void setLinearAttenuation(float att);
	void prepare(int index, std::shared_ptr<Shader>& shader) const;
};

