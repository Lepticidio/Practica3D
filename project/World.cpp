#include "../lib/World.h"
void World::addEntity(const std::shared_ptr<Entity>& entity)
{
	m_tEntities.push_back(entity);
	std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera, Entity>(entity);
	if (camera)
	{
		m_tCameras.push_back(camera);
	}
}
void World::removeEntity(const std::shared_ptr<Entity>& entity)
{
	std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera, Entity>(entity);
	if (camera)
	{
		for (int i = 0; i < m_tCameras.size(); i++)
		{
			if (m_tCameras[i] == camera)
			{
				m_tCameras.erase(m_tCameras.begin() + i);
				break;
			}
		}

	}
	for (int i = 0; i < m_tEntities.size(); i++)
	{
		if (m_tEntities[i] == entity)
		{
			m_tEntities.erase(m_tEntities.begin() + i);
			break;
		}
	}	
}
size_t World::getNumEntities() const
{
	return m_tEntities.size();
}
const std::shared_ptr<Entity>& World::getEntity(size_t index) const
{
	return m_tEntities[index];
}
std::shared_ptr<Entity>& World::getEntity(size_t index)
{
	return m_tEntities[index];
}
void World::update(float deltaTime)
{
	for (int i = 0; i < m_tEntities.size(); i++)
	{
		m_tEntities[i]->update(deltaTime);
	}
}
void World::draw()
{
	for (int i = 0; i < m_tCameras.size(); i++)
	{
		m_tCameras[i]->prepare();
		for (int j = 0; j < m_tEntities.size(); j++)
		{
			m_tEntities[j]->draw();
		}
	}
}