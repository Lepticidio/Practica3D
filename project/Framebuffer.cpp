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
	glActiveTexture(GL_TEXTURE0);
	m_pColorTexture = colorTex;
	m_pDepthTexture = depthTex;

	m_iShadowTextureID = m_pDepthTexture->getId();

	glGenFramebuffers(1, &m_iShadowBufferID);

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
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_iShadowTextureID, 0);

	glDrawBuffer(GL_NONE);
	//glReadBuffer(GL_NONE);
	glEnable(GL_DEPTH_TEST);


	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void Framebuffer::bindScreen()
{

}