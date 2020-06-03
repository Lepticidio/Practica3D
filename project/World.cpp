#include "../lib/World.h"
#include "../lib/State.h"
void World::addEntity(const std::shared_ptr<Entity>& entity)
{
	m_tEntities.push_back(entity);
	std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera, Entity>(entity);
	if (camera)
	{
		m_tCameras.push_back(camera);
	}
	std::shared_ptr<Light> light = std::dynamic_pointer_cast<Light, Entity>(entity);
	if (light)
	{
		m_tLights.push_back(light);
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
	std::shared_ptr<Light> light = std::dynamic_pointer_cast<Light, Entity>(entity);
	if (light)
	{
		for (int i = 0; i < m_tLights.size(); i++)
		{
			if (m_tLights[i] == light)
			{
				m_tLights.erase(m_tLights.begin() + i);
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
const glm::vec3& World::getAmbient() const
{
	return m_vAmbientLight;
}
void World::setAmbient(const glm::vec3& ambient)
{
	m_vAmbientLight = ambient;
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
	/*
	State::ambient = m_vAmbientLight;
	State::lights.clear();
	for (int i = 0; i < m_tLights.size(); i++)
	{
		State::lights.push_back(m_tLights[i]);
	}
	
	
	*/
	for (int i = 0; i < m_tCameras.size(); i++)
	{
		m_tCameras[i]->prepare();
		for (int j = 0; j < m_tEntities.size(); j++)
		{
			m_tEntities[j]->draw();
		}
	}
}