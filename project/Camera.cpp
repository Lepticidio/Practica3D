#include "../lib/Camera.h"
#include "../lib/State.h"
#include "../glm/gtc/matrix_transform.hpp"
#include "../lib/Framebuffer.h"

Camera::Camera()
{

}
const glm::mat4& Camera::getProjection() const
{
	return m_projection;
}
void Camera::setProjection(const glm::mat4& proj)
{
	m_projection = proj;
}
const glm::ivec4& Camera::getViewport() const
{
	return m_vViewport;
}
void Camera::setViewport(const glm::ivec4& vp)
{
	m_vViewport = vp;
}
const glm::vec3& Camera::getClearColor() const
{
	return m_vColor;
}
void Camera::setClearColor(const glm::vec3& color)
{
	m_vColor = color;
}
void Camera::prepare()
{
	State::projectionMatrix = m_projection;
	glm::mat4 viewMatrix = glm::translate(glm::mat4(), -m_vPosition);

	viewMatrix = glm::rotate(viewMatrix, -m_vRotation.x, glm::vec3(1, 0, 0));
	viewMatrix = glm::rotate(viewMatrix, -m_vRotation.y, glm::vec3(0, 1, 0));
	viewMatrix = glm::rotate(viewMatrix, -m_vRotation.z, glm::vec3(0, 0, 1));
	viewMatrix = glm::scale(viewMatrix, m_vScale);
	State::viewMatrix = viewMatrix;

	glViewport(m_vViewport.x, m_vViewport.y, m_vViewport.z, m_vViewport.w);
	//glScissor(m_vViewport.x, m_vViewport.y, m_vViewport.z, m_vViewport.w);

	//clear buffers
	glClearColor(m_vColor.r, m_vColor.g, m_vColor.b, 1.0f);
}
void Camera::setFramebuffer(std::shared_ptr<Framebuffer>& framebuffer)
{
	m_pFramebuffer = framebuffer;
}
const std::shared_ptr<Framebuffer> Camera::getFramebuffer() const
{
	return m_pFramebuffer;
}
