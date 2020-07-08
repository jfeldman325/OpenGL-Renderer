#pragma once
#include "VertexArrayObject.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>



VertexArrayObject::VertexArrayObject()
{
	
	glGenVertexArrays(1, &m_RendererID);
	glBindVertexArray(m_RendererID);

}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1,&m_RendererID);
}

void VertexArrayObject::Bind() const
{	

	glBindVertexArray(m_RendererID);
}

void VertexArrayObject::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArrayObject::AddVB(int object_index,const void* data,unsigned int size,BufferLayout* layout)
{
	std::shared_ptr<VertexBuffer> vb_ret(new VertexBuffer(data,size));
	

	ObjectBuffer object;

	object.vertex_buffer=vb_ret;
	object.buffer_id=object_index;
	object.layout=layout;
	layout->BindLayout();
	buffers.push_back(object);
	
	
}

//	TO DO FIX DATA POINTER FROM GOING OUT OF SCOPE

void VertexArrayObject::AddIB(int object_index,std::vector<unsigned int>* data, unsigned int count)
{

	for (ObjectBuffer bf : buffers) {
		if (bf.buffer_id == object_index) {
			std::move(bf.index_buffer_data.begin(),bf.index_buffer_data.end(),std::back_inserter(data)); //the issue is here, i am pushing back the data and then it is going out of scope after this call.   
			//bf.index_buffer_data.push_back(data);
			std::cout<<bf.index_buffer_data.size();
	
		}
	};
	
}

void VertexArrayObject::BindIBs(int object_index) {

	std::vector<unsigned int> accum_data={};

	std::shared_ptr<IndexBuffer> ib_ret(new IndexBuffer(0));

	for (ObjectBuffer bf : buffers) {
		if (bf.buffer_id == object_index) {
		
			

			for (auto ib : bf.index_buffer_data) {
				accum_data.reserve(accum_data.size() + ib->size());
				std::move(ib->begin(), ib->end(), std::back_inserter(accum_data));
			}

			bf.index_buffer=ib_ret;
		}
	}

	ib_ret->GenBufferData(&accum_data,accum_data.size());

}


