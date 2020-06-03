#pragma once
#include "Camera.h"
#include <vector>
#include <memory>
#include "Light.h"
class World
{
	glm::vec3 m_vAmbientLight;

	std::vector<std::shared_ptr<Entity>> m_tEntities;
	std::vector<std::shared_ptr<Camera>> m_tCameras;
	std::vector<std::shared_ptr<Light>> m_tLights;
public:
	const glm::vec3& getAmbient() const;
	void setAmbient(const glm::vec3& ambient);

	void addEntity(const std::shared_ptr<Entity>& entity);
	void removeEntity(const std::shared_ptr<Entity>& entity);
	size_t getNumEntities() const;
	const std::shared_ptr<Entity>& getEntity(size_t index) const;
	std::shared_ptr<Entity>& getEntity(size_t index);
	void update(float deltaTime);
	void draw();
};

