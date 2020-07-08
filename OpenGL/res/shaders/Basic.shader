
#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 text_cord;

out vec4 colorV;

void main()
{
	colorV=text_cord;
	gl_Position= position; 
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec4 colorV;

uniform  vec4 u_Color;

void main()
{
	
	color=colorV*u_Color;
};