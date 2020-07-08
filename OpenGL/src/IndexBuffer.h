#pragma once
#include <vector>

class IndexBuffer
{
	private:
		unsigned int m_RendererID;
		unsigned int m_count;
	public:
		IndexBuffer( unsigned int count);
		~IndexBuffer();

		void GenBufferData(std::vector<unsigned int>* data, unsigned int count);
		void Bind() const;
		void Unbind() const;

		inline unsigned int GetCount() const {return m_count;}
};
