#include "GL/glew.h"
#include "../lib/Framebuffer.h"


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
	GLuint iIDShadowBuff;

	glGenFramebuffers(1, &iIDShadowBuff);

	GLuint iIDShadowText;
	glGenTextures(1, &iIDShadowText);
	glBindTexture(GL_TEXTURE_2D, iIDShadowText);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, iWidth, iHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE,	GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	//glUseProgram(idProgramPass1);
	//glClear(GL_COLOR_BUFFER_BIT);
	//glClear(GL_DEPTH_BUFFER_BIT);
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
}
void Framebuffer::bindScreen()
{

}