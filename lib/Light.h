#pragma once
#include "Shader.h"
#include "Entity.h"
enum LightType { DIRECTIONAL, POINT };
class Light : public Entity
{
	float m_fLinearAttenuation;
	glm::vec3 m_vColor;
	LightType m_eLightType;

public:
	LightType getType() const;
	void setType(LightType type);
	const glm::vec3& getColor() const;
	void setColor(const glm::vec3& color);
	float getLinearAttenuation() const;
	void setLinearAttenuation(float att);
	void prepare(int index, std::shared_ptr<Shader>& shader) const;
};

