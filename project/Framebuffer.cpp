#include "GL/glew.h"
#include "../lib/Framebuffer.h"
#include "../lib/State.h"
#include "../lib/Light.h"
#include "../glm/gtc/matrix_transform.hpp"
#include <vector>


Framebuffer::Framebuffer(
	const std::shared_ptr<Texture>& colorTex,
	const std::shared_ptr<Texture>& depthTex
)
{
	m_pColorTexture = colorTex;
	m_pDepthTexture = depthTex;
	GLFWwindow* pWindow = glfwGetCurrentContext();
	int iWidth, iHeight;
	glfwGetFramebufferSize(pWindow, &iWidth, &iHeight);

	glGenFramebuffers(1, &m_iShadowBufferID);

	glGenTextures(1, &m_iShadowTextureID);
	glBindTexture(GL_TEXTURE_2D, m_iShadowTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, iWidth, iHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
}
Framebuffer::~Framebuffer()
{

}
const std::shared_ptr<Texture>& Framebuffer::getColorTexture() const
{
	return m_pColorTexture;
}
const std::shared_ptr<Texture>& Framebuffer::getDepthTexture() const
{
	return m_pDepthTexture;
}
void Framebuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_iShadowBufferID);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_iShadowTextureID, 0);
}
void Framebuffer::bindScreen()
{

}