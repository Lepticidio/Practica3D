#pragma once
#include "State.h"
#include "../glm/gtc/matrix_transform.hpp"
class Material
{
	std::shared_ptr<Shader> m_pShader;
	std::shared_ptr<Texture> m_pTexture;
public:


	Material(const std::shared_ptr<Texture>& tex = nullptr,
		const std::shared_ptr<Shader>& shader = nullptr);
	void prepare();
	std::shared_ptr<Shader> getShader();
	std::shared_ptr<Texture> getTexture();
	void setShader(const std::shared_ptr<Shader>& shader);
	void setTexture(const std::shared_ptr<Texture>& tex);
};

