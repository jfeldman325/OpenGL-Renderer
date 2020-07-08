#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm> 
#include "VertexArrayObject.h"
#include "Renderer.h"
#include <memory>
#include "BufferLayout.h"
#include "Shader.h"

void GLAPIENTRY MessageCallback(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar* message,const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}



static void GLClearErrors() 
{
	while (glGetError() != GL_NO_ERROR);
}

static void GLCheckError()
{
	while (GLenum error = glGetError())
	{
		std::cout<<"[Open GL ERROR] "<<error<<std::endl;
	}
}


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	
	if (glewInit() != GLEW_OK)
		std::cout << "Error! GLEW failed to initialize" << std::endl;

	// During init, enable debug output
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);


	std::cout <<glGetString(GL_VERSION)<<std::endl;
	{
		float positions[8]= {
			-0.5f, -0.5f, //0
			
			 0.5f, -0.5f, //1
			 
			 0.5f,  0.5f, //2
			
			-0.5f,  0.5f,  //3
			 
		};

		std::vector<unsigned int> indices = {
			0,1,2,
			2,3,0
		};

		float textCoord[8] = {
			 0.0f,0.0f,
			0.0f,1.0f,
			 1.0f,1.0f,
			0.0f,1.0f
		};


	

		VertexArrayObject vao;
		BufferLayout layout(Coordinate_Space::SCREEN_2D, GL_FALSE);
		layout.AddAttribute(0,Vertex_Attribute::POSITION);
		vao.AddVB(0,positions, 8 * 2 * sizeof(float),&layout);
 		vao.AddIB(0,&indices, 6);
		vao.BindIBs(0);

 		BufferLayout layout2(Coordinate_Space::SCREEN_2D,GL_FALSE);
 		layout2.AddAttribute(1,Vertex_Attribute::TEXT_CORD);
 		vao.AddVB(1,textCoord,4*2*sizeof(float),&layout2);


		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color",0.8f,0.3f,0.8f,1.0f);

		int location = shader.GetUniformLocation("u_Color");
		float r = 0.0f;
		float increment =0.05f;
			

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			if (location != -1) {
				shader.SetUniform4f("u_Color", std::min(1.0f, r), 0.3f, 0.8f, 1.0f);
				
			}

			if (r > 1.0f) {
				increment = -0.05f;
			}
			else if (r < 0) {
				increment = 0.05f;
			}

			r+=increment;

			shader.Bind();
			vao.Bind();

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		
			
		
			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
		
	}
	

	glfwTerminate();
	return 0;
}