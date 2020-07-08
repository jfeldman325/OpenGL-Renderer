#pragma once 
#include <string>
#include <unordered_map>
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{
	private:
		std::string m_FilePath;
		unsigned int m_RendererId;
		std::unordered_map<std::string,unsigned int> m_UniformLocationCache;
		
		
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		ShaderProgramSource ParseShader();
	public:
		Shader(const std::string& filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		//set uniforms 
		void SetUniform4f(const std::string& name,float f0,float f1, float f2, float f3);
		int GetUniformLocation(const std::string& name);

};