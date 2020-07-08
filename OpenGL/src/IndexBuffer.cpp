#include "IndexBuffer.h"
#include "Renderer.h"
#include <vector>

IndexBuffer::IndexBuffer( unsigned int count) :m_count(count)
{

	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	


}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1,&m_RendererID);
}

void IndexBuffer::GenBufferData(std::vector<unsigned int>* data, unsigned int count) {

	if (count != m_count) {
		m_count=count;
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
