#include "BufferLayout.h"
#include "Renderer.h"
#include <iostream>
#include <map>


BufferLayout::BufferLayout(Coordinate_Space cord_space, bool normalized): cord_space(cord_space),normalized(normalized),curr_offset(0)
{

}

BufferLayout::~BufferLayout()
{
	
}

//type_override overrides the data type for the attribute, layout_index overrides the assumed sequence of buffer data E.G. 
//method assumes user specifies attributes in the order they appear in the data, if user wants to specify attributes independent 
//of order in data or override an existing attribute layout, the layout index must be specified.
void BufferLayout::AddAttribute(int attrib_index, Vertex_Attribute attrib,int type_override,int layout_index)
{

	
	int cord_count = 0;
	cord_count=GetAttributeCount(attrib);

	if (type_override != -1) {
		ModifyMapping(attrib,type_override);
	}

	unsigned int  type = GetAttributeVarType(attrib);

	curr_offset += sizeof(type) * cord_count;
	Attribute at;
	at.attrib = attrib;
	at.attrib_count = cord_count;
	at.attrib_index = attrib_index;
	at.attrib_type=type;

	if (layout_index == -1) {
		layout.push_back(at);
	}
	else {
		//override existing attribute layout
		if (layout_index < layout.size()) {
			layout[layout_index]=at;
		}
		else {
			layout.resize(layout_index+1);
			layout[layout_index]=at;
		}
	}

}

void BufferLayout::BindLayout() const{
	unsigned int tot_size=0;
	const void* ts=&tot_size;
	for (int i = 0; i < layout.size(); i++) {
		
			Attribute a=layout[i];
			

			std::cout<<"attrib_index:"<<a.attrib_index<<" attrib_count:"<<a.attrib_count<<" a.attrib_type:"<<a.attrib_type<<" normalized:"<<normalized<<" curr_offset:"<<curr_offset<<" ts:"<<ts;
			glEnableVertexAttribArray(a.attrib_index);
			glVertexAttribPointer(a.attrib_index, a.attrib_count, a.attrib_type, normalized, curr_offset,(const void*)tot_size);
			tot_size += sizeof(a.attrib_type) * a.attrib_count;
		
	}


}

void BufferLayout::RemoveAttribute(int attrib_index, Vertex_Attribute attrib)
{
	std::cout<<"NOT IMPLEMENTED";
}



unsigned int BufferLayout::GetAttributeCount(Vertex_Attribute attrib)
{
	switch (attrib)
	{
	case Vertex_Attribute::POSITION:
	{
		return cord_space;
		break;
	}
	case Vertex_Attribute::NORMAL:
	{
		return cord_space;
		break;
	}
	case Vertex_Attribute::TEXT_CORD:
	{
		return 2;
		break;
	}
	case Vertex_Attribute::WORLD_OFFSET:
	{
		return cord_space;
		break;
	}
	case Vertex_Attribute::COLOR:
	{
		return 4;
		break;
	}
	default:
	{
		return cord_space;
		break;
	}
	}
}

unsigned int BufferLayout::GetAttributeVarType(Vertex_Attribute attrib)
{
	switch(attrib)
	{
		case Vertex_Attribute::POSITION: 
		{
			return GL_FLOAT;
			break;
		}
		case Vertex_Attribute::NORMAL: 
		{
			return GL_FLOAT;
			break;
		}
		case Vertex_Attribute::TEXT_CORD :
		{
			return GL_FLOAT;
			break;
		}
		case Vertex_Attribute::WORLD_OFFSET:
		{
			return GL_FLOAT;
			break;
		}
		case Vertex_Attribute::COLOR:
		{
			return GL_FLOAT;
			break;
		}
		default:
		{
			return GL_FLOAT;
			break;
		}
	}

}

void BufferLayout::ModifyMapping(Vertex_Attribute attrib, int type)
{
	mapping[attrib]=type;
}


