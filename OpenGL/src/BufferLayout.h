#pragma once 

#include <vector>
#include "Renderer.h"
#include <map>

//integer value of -1 means this value cannot be determined independent of coordinate_space specification any other value is the number of items (most likely floats) required

enum Vertex_Attribute {
	POSITION,
	NORMAL,
	COLOR,
	TEXT_CORD,
	WORLD_OFFSET,
};

//to fully implement a new vertex attribute, return values for getattributecount and getattributevartype must also be added

enum Coordinate_Space {
	SCREEN_2D=2,
	WORLD_3D=3,
	WORLD_2D=2
};

struct Attribute {
	Vertex_Attribute attrib;
	int attrib_count;
	int attrib_index;
	int attrib_type;
};

class BufferLayout {

	private:
		Coordinate_Space cord_space;
		std::vector<Attribute> layout;
		std::map<Vertex_Attribute,int> mapping;
		int curr_offset;
		bool normalized;
		
		unsigned int GetAttributeCount(Vertex_Attribute attrib);
		unsigned int GetAttributeVarType(Vertex_Attribute attrib);
	public:
		BufferLayout(Coordinate_Space cord_space,bool normalized);
		~BufferLayout();

		void AddAttribute(int attrib_index, Vertex_Attribute attrib, int type_override = -1, int layout_index = -1);
		void RemoveAttribute(int attrib_index,Vertex_Attribute attrib);
		
		void BindLayout() const;
		void ModifyMapping(Vertex_Attribute attrib,int type);
};