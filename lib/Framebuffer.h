#pragma once
#include "Texture.h"

class Framebuffer
{
	std::shared_ptr <Texture> m_pColorTexture, m_pDepthTexture;
	GLuint m_iShadowBufferID, m_iShadowTextureID;
public:
	Framebuffer(
		const std::shared_ptr<Texture>& colorTex,
		const std::shared_ptr<Texture>& depthTex);
	~Framebuffer();
	const std::shared_ptr<Texture>& getColorTexture() const;
	const std::shared_ptr<Texture>& getDepthTexture() const;
	GLuint getShadowBufferID() { return m_iShadowBufferID; }
	GLuint getShadowTextureID() { return m_iShadowTextureID; }
	void bind() const;
	static void bindScreen();
};

