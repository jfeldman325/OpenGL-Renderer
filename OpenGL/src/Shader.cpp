#include "Shader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "VertexArrayObject.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "BufferLayout.h"


Shader::Shader(const std::string& filepath):m_FilePath(filepath),m_RendererId(0)
{
	ShaderProgramSource source = ParseShader();

	m_RendererId = CreateShader(source.VertexSource, source.FragmentSource);

}

Shader::~Shader()
{
	glDeleteShader(m_RendererId);
}



ShaderProgramSource Shader::ParseShader()
{
	std::ifstream stream(m_FilePath);

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};


	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			if (type != ShaderType::NONE)
			{
				ss[(int)type] << line << '\n';
			}

		}
	}

	return { ss[0].str(),ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	int params;
	glGetProgramiv(program, GL_VALIDATE_STATUS, &params);
	if (params == GL_FALSE) {
		std::cout << "WARNING Shader not effective." << std::endl;
	}

	return program;
}


void Shader::Bind() const
{
	glUseProgram(m_RendererId);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
	
	glUniform4f(GetUniformLocation(name),f0,f1,f2,f3);
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.count(name)) {
		return m_UniformLocationCache[name];
	}
	else {
		int location = glGetUniformLocation(m_RendererId, name.c_str());

		m_UniformLocationCache[name]=location;

		if (location == -1)
			std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
	
		return location;

	}

	
}