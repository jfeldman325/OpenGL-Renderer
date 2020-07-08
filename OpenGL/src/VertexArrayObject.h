#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <vector>
#include <memory>
#include "BufferLayout.h"

class BufferLayout;

struct ObjectBuffer {
	std::shared_ptr<VertexBuffer> vertex_buffer;
	std::vector<std::vector<unsigned int>*> index_buffer_data;
	std::shared_ptr<IndexBuffer> index_buffer;
	BufferLayout* layout;
	int buffer_id;
	
};

class VertexArrayObject
{
private:
	unsigned int m_RendererID;
	std::vector<ObjectBuffer> buffers;
public:
	VertexArrayObject();
	~VertexArrayObject();

	void Bind() const;
	void Unbind() const;
	void AddVB(int object_index,const void* data, unsigned int size,BufferLayout* layout);
	void AddIB(int object_index, std::vector<unsigned int>* data, unsigned int count);
	void BindIBs(int object_index);
};
