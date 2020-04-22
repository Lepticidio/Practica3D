#pragma once
#include "Entity.h"
class Camera : public Entity
{
	glm::vec3 m_vColor;
	glm::mat4 m_projection;
	glm::ivec4 m_vViewport;
public:
	Camera();
	const glm::mat4& getProjection() const;
	void setProjection(const glm::mat4& proj);
	const glm::ivec4& getViewport() const;
	void setViewport(const glm::ivec4& vp);
	const glm::vec3& getClearColor() const;
	void setClearColor(const glm::vec3& color);
	void prepare();
};

