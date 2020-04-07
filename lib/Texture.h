#pragma once
#include <memory>
#include "stb_image.h".
#include "glm/glm.hpp"
#include "../lib/glfw/glfw3.h"
class Texture
{
	uint32_t m_iId, m_iWidth, m_iHeight;
public:
	Texture(int _iId, int _iWidth, int _iHeight);
	static std::shared_ptr<Texture> load(const char* filename);
	uint32_t getId() const;
	const glm::ivec2& getSize() const;
	void bind() const;
};