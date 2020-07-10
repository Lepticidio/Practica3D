
#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "GL/glew.h"
#include "../lib/Texture.h"

Texture::Texture(int _iId, int _iWidth, int _iHeight) : m_iId(_iId), m_iWidth(_iWidth), m_iHeight(_iHeight)
{



}

Texture::Texture(int _iWidth, int _iHeight, bool _bIsDepth) :  m_iWidth(_iWidth), m_iHeight(_iHeight), m_bIsDepth(_bIsDepth)
{
	GLuint texId;
	glGenTextures(1, &texId);
	glActiveTexture(GL_TEXTURE1);

	glBindTexture(GL_TEXTURE_2D, texId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _iWidth, _iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
}
std::shared_ptr<Texture> Texture::load(const char* filename)
{
	int iWidth = 0;
	int iHeight = 0;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* sRunBytes = stbi_load(filename, &iWidth, &iHeight, nullptr, 4);
	GLuint texId;
	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &texId);
	
	(GL_TEXTURE_2D, texId);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, sRunBytes);


	stbi_image_free(sRunBytes);
	std::shared_ptr<Texture> pResult = std::make_shared<Texture>(texId, iWidth, iHeight);
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
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_iId);
}