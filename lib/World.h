#pragma once
#include "Camera.h"
#include <vector>
#include <memory>
class World
{
	std::vector<std::shared_ptr<Entity>> m_tEntities;
	std::vector<std::shared_ptr<Camera>> m_tCameras;
public:
	void addEntity(const std::shared_ptr<Entity>& entity);
	void removeEntity(const std::shared_ptr<Entity>& entity);
	size_t getNumEntities() const;
	const std::shared_ptr<Entity>& getEntity(size_t index) const;
	std::shared_ptr<Entity>& getEntity(size_t index);
	void update(float deltaTime);
	void draw();
};

