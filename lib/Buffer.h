#pragma once
#include "Material.h"
#include <vector>
class Buffer
{
private:
	unsigned int m_tIds[2];
	std::vector<Vertex> m_tVertex;
	std::vector<uint16_t> m_tIndexes;
public:
	Buffer(std::vector<Vertex> _tVertex, std::vector<uint16_t> _tIndexes);
	void draw(const Shader& shader) const;
};

