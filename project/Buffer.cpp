#include "../lib/Buffer.h"

Buffer::Buffer(std::vector<Vertex> _tVertex, std::vector<uint16_t> _tIndexes) : m_tVertex(_tVertex), m_tIndexes(_tIndexes)
{
	glGenBuffers(2, m_tIds);
	glBindBuffer(GL_ARRAY_BUFFER, m_tIds[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_tIds[1]);


	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) *	m_tVertex.size(), &m_tVertex[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * m_tIndexes.size(), &m_tIndexes[0],	GL_STATIC_DRAW);
}
void Buffer::draw(const Shader& shader) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_tIds[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_tIds[1]);
	shader.setupAttribs();
	glDrawElements(GL_TRIANGLES, m_tIndexes.size(), GL_UNSIGNED_SHORT, nullptr);

}