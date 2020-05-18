#pragma once
#include "GL/glew.h"
#include "Vertex.h"
#include "Texture.h"
class Vertex
{
public:
	glm::vec3 m_vPosition;
	glm::vec3 m_vColor;
	glm::vec2 m_vTextureCoord;
	glm::vec2 m_vNormal;
};

