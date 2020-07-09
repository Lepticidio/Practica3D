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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE,	GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);



	/*glBindFramebuffer(GL_FRAMEBUFFER, m_iShadowBufferID);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_iShadowTextureID, 0);*/

	//if (State::overrideShader == nullptr)
	//{
	//	State::overrideShader = std::make_shared<Shader>("data//depthVertex.glsl", "data//depthFragment.glsl");

	//}
	//uint32_t iShaderID =  State::overrideShader->getId();

	//glUseProgram(iShaderID);
	//glClear(GL_COLOR_BUFFER_BIT);
	//glClear(GL_DEPTH_BUFFER_BIT);
	//
	//if(State::lights.size() > 0)
	//{
	//	glm::vec3 vLightPos = State::lights[0]->getPosition();
	//	glm::vec3 vLightDir = State::lights[0]->getDirection();
	//	glm::mat4 lightVmatrix = glm::lookAt(State::lights[0]->getPosition(), vLightPos + vLightDir, glm::vec3(0, 1, 0));
	//	glm::mat4 lightPmatrix = State::projectionMatrix;
	//}

	//glBindFramebuffer(GL_FRAMEBUFFER, iIDShadowBuff);
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, iIDShadowText, 0);

	glDrawBuffer(GL_NONE);
	glEnable(GL_DEPTH_TEST);

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