#include "ffpch.h"
#include "OpenGLShader.h"
#include "OpenGLError.h"

namespace FireFly
{
	OpenGLShader::OpenGLShader(const std::string& vertexSRC, const std::string& fragmentSRC)
		:m_RendererID(0)
	{
		GLCALL(m_RendererID = glCreateProgram());
		std::unordered_map<FireFly::Shader::ShaderType, std::string> shaderSources = 
		{ {FireFly::Shader::ShaderType::VertexShaderSRC, vertexSRC},{FireFly::Shader::ShaderType::FragmentShaderSRC, fragmentSRC} };
		auto shaderIDs = Compile(shaderSources);
		Attach(shaderIDs);
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
		:m_RendererID(0)
	{
		GLCALL(m_RendererID = glCreateProgram());
		auto shaderSources = ParseFile(filepath);
		auto shaderIDs = Compile(shaderSources);
		Attach(shaderIDs);
	}

	
	OpenGLShader::~OpenGLShader()
	{
		GLCALL(glDeleteProgram(m_RendererID));
	}
	
	void OpenGLShader::Bind() const
	{
		GLCALL(glUseProgram(m_RendererID));
	}
	
	void OpenGLShader::UnBind() const
	{
		GLCALL(glUseProgram(0));
	}

	void OpenGLShader::UploadUniform(const glm::mat4& mat, const std::string& name)
	{
		int location;
		auto it = m_UniformLocationMap.find(name);

		if (it != m_UniformLocationMap.end())
		{
			location = it->second;
		}
		else
		{
			GLCALL(location = glGetUniformLocation(m_RendererID, name.c_str()));
			if (location == -1)
			{
				FF_CORE_WARN("Failed to locate the Uniform \"{0}\"!", name);
				return;
			}
			m_UniformLocationMap[name] = location;
		}

		GLCALL(glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]));
	}

	void OpenGLShader::UploadUniform(int i, const std::string& name)
	{
		int location;
		auto it = m_UniformLocationMap.find(name);

		if (it != m_UniformLocationMap.end())
		{
			location = it->second;
		}
		else
		{
			GLCALL(location = glGetUniformLocation(m_RendererID, name.c_str()));
			if (location == -1)
			{
				FF_CORE_WARN("Failed to locate the Uniform \"{0}\"!", name);
				return;
			}
			m_UniformLocationMap[name] = location;
		}

		GLCALL(glUniform1i(location, i));
	}


	//--------HelperFunc---------


	GLenum OpenGLShader::ShaderTypeToOpenGLenum(ShaderType type)
	{
		switch (type)
		{
		case ShaderType::VertexShaderSRC:		return GL_VERTEX_SHADER;
		case ShaderType::FragmentShaderSRC:		return GL_FRAGMENT_SHADER;
		}
		FF_CORE_ASSERT("false", "Unknown Shader type!");
		return 0;
	}

	std::unordered_map<Shader::ShaderType, unsigned int> OpenGLShader::Compile(std::unordered_map<ShaderType, std::string>& sourceFile)
	{
		std::unordered_map<ShaderType, unsigned int> shaderIDs;
		//Create Shaders
		for (const auto pair : sourceFile)
		{
			unsigned int shader;
			GLenum type = ShaderTypeToOpenGLenum(pair.first);
			GLCALL(shader = glCreateShader(type));
			shaderIDs[pair.first] = shader;
			const char* src = (const char*)pair.second.c_str();

			GLCALL(glShaderSource(shader, 1, &src, nullptr));

			int status = 0;

			//Compile the shader
			GLCALL(glCompileShader(shader));
			GLCALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &status));
			if (status != GL_TRUE)
			{
				int length;
				GLCALL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
				char* log = new char[length];
				GLCALL(glGetShaderInfoLog(shader, length, &length, log));
			
				FF_CORE_ERROR("Failed to Compile the shader: {}", log);
				FF_CORE_ASSERT(false, "");
				glDeleteShader(shader);
				delete[]log;
				return shaderIDs;
			}
		}
		return shaderIDs;
	}

	void OpenGLShader::Attach(std::unordered_map<ShaderType, unsigned int>& shaderIDs)
	{
		for (auto pair : shaderIDs)
		{
			GLCALL(glAttachShader(m_RendererID, pair.second));
		}
		GLCALL(glLinkProgram(m_RendererID));
		int status = 0;
		GLCALL(glGetProgramiv(m_RendererID, GL_LINK_STATUS, &status));
		if (status != GL_TRUE)
		{
			int length;
			GLCALL(glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &length));
			char* log = new char[length];
			GLCALL(glGetProgramInfoLog(m_RendererID, length, &length, log));
			FF_CORE_ERROR("Failed to Link the Program: {}", log);

			glDeleteProgram(m_RendererID);
			delete[]log;
		}
		for (auto pair : shaderIDs)
		{
			GLCALL(glDeleteShader(pair.second));
		}
		return;
	}
}