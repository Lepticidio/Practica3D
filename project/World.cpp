#include "../lib/World.h"
#include "../lib/State.h"
#include "../lib/Camera.h"
#include "../lib/Framebuffer.h"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/quaternion.hpp"
#include "../glm/gtx/quaternion.hpp"


World::World()
{
	std::shared_ptr<Framebuffer> frameBuffer = std::make_shared<Framebuffer>(nullptr, std::make_shared<Texture>(1024, 1024, true));
	m_pDepthCamera = new Camera();
	m_pDepthCamera->setFramebuffer(frameBuffer);
	m_pDepthCamera->setViewport(glm::ivec4(0, 0, 1024, 1024));
	m_pDepthShader = std::make_shared<Shader>("data//depthVertex.glsl", "data//depthFragment.glsl");
}
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
	//PASS 1

	State::overrideShader = m_pDepthShader;
	glActiveTexture(GL_TEXTURE0);
	m_pDepthShader->use();



	std::shared_ptr<Light> pShadowLight;
	for (int i = 0; i < m_tLights.size(); i++)
	{
		std::shared_ptr<Light> pLight = m_tLights[i];
		if (pLight->getType() == LightType::DIRECTIONAL)
		{
			pShadowLight = pLight;
		}
	}


	m_pDepthCamera->setPosition(pShadowLight->getDirection()*8.f);
	glm::mat4 lookAt = glm::lookAt(m_pDepthCamera->getPosition(), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::quat quaterRot = glm::toQuat(lookAt);
	glm::vec3 vEuler = glm::eulerAngles(quaterRot);
	m_pDepthCamera->setRotation(vEuler);
	m_pDepthCamera->prepare();

	m_pDepthCamera->getFramebuffer()->bind();
	for (int j = 0; j < m_tEntities.size(); j++)
	{
		m_tEntities[j]->draw();
	}

	//PASS 2

	State::overrideShader = nullptr;

	glm::mat4 bias
	(
		0.5f, 0.0f, 0.0f, 0.0f, 
		0.0f, 0.5f, 0.0f, 0.0f, 
		0.0f, 0.0f, 0.5f, 0.0f, 
		0.5f, 0.5f, 0.5f, 1.0f
	);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	State::depthBiasMatrix = bias * State::projectionMatrix * State::viewMatrix;
	State::ambient = m_vAmbientLight;
	State::lights.clear();

	
	for (int i = 0; i < m_tLights.size(); i++)
	{
		State::lights.push_back(m_tLights[i]);
	}
	
	for (int i = 0; i < m_tCameras.size(); i++)
	{
		m_tCameras[i]->prepare();
		std::shared_ptr<Framebuffer> pFramebuffer = m_pDepthCamera->getFramebuffer();
		GLuint iShadowTextureID = pFramebuffer->getShadowTextureID();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, iShadowTextureID);
		glActiveTexture(GL_TEXTURE1);
		for (int j = 0; j < m_tEntities.size(); j++)
		{
			m_tEntities[j]->draw();
		}
	}

}
void World::setShadows(bool enable)
{
	m_bShadows = enable;
}
void World::setDepthOrtho(float left, float right, float bottom, float top, float near, float far)
{
	m_pDepthCamera->setProjection(glm::ortho(left, right, bottom, top, near, far));
}