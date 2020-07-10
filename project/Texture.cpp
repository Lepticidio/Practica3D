
#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "GL/glew.h"
#include "../lib/Texture.h"

Texture::Texture(int _iId, int _iWidth, int _iHeight) : m_iId(_iId), m_iWidth(_iWidth), m_iHeight(_iHeight)
{



}

Texture::Texture(int _iWidth, int _iHeight, bool _bIsDepth) :  m_iWidth(_iWidth), m_iHeight(_iHeight), m_bIsDepth(_bIsDepth)
{
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_iId);
	glBindTexture(GL_TEXTURE_2D, m_iId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _iWidth, _iHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
std::shared_ptr<Texture> Texture::load(const char* filename)
{
	glActiveTexture(GL_TEXTURE1);
	int iWidth = 0;
	int iHeight = 0;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* sRunBytes = stbi_load(filename, &iWidth, &iHeight, nullptr, 4);
	GLuint m_iId;
	glGenTextures(1, &m_iId);
	glBindTexture(GL_TEXTURE_2D, m_iId);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, sRunBytes);


	stbi_image_free(sRunBytes);
	std::shared_ptr<Texture> pResult = std::make_shared<Texture>(m_iId, iWidth, iHeight);
	return pResult;
}
uint32_t Texture::getId() const
{
	return m_iId;
}
const glm::ivec2& Texture::getSize() const
{
	return glm::ivec2(m_iWidth, m_iHeight);
}
void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_iId);
}