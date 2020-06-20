#pragma once
#include "Texture.h"

class Framebuffer
{
	std::shared_ptr <Texture> m_pColorTexture, m_pDepthTexture;
	Framebuffer(
		const std::shared_ptr<Texture>& colorTex,
		const std::shared_ptr<Texture>& depthTex);
	~Framebuffer();
	const std::shared_ptr<Texture>& getColorTexture() const;
	const std::shared_ptr<Texture>& getDepthTexture() const;
	void bind() const;
	static void bindScreen();
};

