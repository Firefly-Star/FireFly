#include "ffpch.h"
#include "OpenGLShader.h"
#include "OpenGLError.h"

namespace FireFly
{
	OpenGLShader::OpenGLShader(const std::string& vertexSRC, const std::string& fragmentSRC)
		:m_RendererID(0)
	{
		//Create Shaders
		unsigned int vs, fs;
		GLCALL(vs = glCreateShader(GL_VERTEX_SHADER));
		GLCALL(fs = glCreateShader(GL_FRAGMENT_SHADER));

		const char* vSource = (const char*)vertexSRC.c_str();
		const char* fSource = (const char*)fragmentSRC.c_str();

		GLCALL(glShaderSource(vs, 1, &vSource, nullptr));
		GLCALL(glShaderSource(fs, 1, &fSource, nullptr));
		
		int status = 0;

		//Compile the vs
		GLCALL(glCompileShader(vs));
		GLCALL(glGetShaderiv(vs, GL_COMPILE_STATUS, &status));
		if (status != GL_TRUE)
		{
			int length;
			GLCALL(glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length));
			char* log = new char[length];
			GLCALL(glGetShaderInfoLog(vs, length, &length, log));
			FF_CORE_ERROR("Failed to Compile the shader: {}", log);

			glDeleteShader(vs);
			delete []log;
			return;
		}

		//Compile the fs
		GLCALL(glCompileShader(fs));
		GLCALL(glGetShaderiv(fs, GL_COMPILE_STATUS, &status));
		if (status != GL_TRUE)
		{
			int length;
			GLCALL(glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &length));
			char* log = new char[length];
			GLCALL(glGetShaderInfoLog(fs, length, &length, log));
			FF_CORE_ERROR("Failed to Compile the shader: {}", log);

			glDeleteShader(fs);
			delete []log;
			return;
		}

		//Attach shaders
		GLCALL(m_RendererID = glCreateProgram());
		GLCALL(glAttachShader(m_RendererID, vs));
		GLCALL(glAttachShader(m_RendererID, fs));

		GLCALL(glLinkProgram(m_RendererID));

		GLCALL(glGetProgramiv(m_RendererID, GL_LINK_STATUS, &status));
		if (status != GL_TRUE)
		{
			int length;
			GLCALL(glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &length));
			char* log = new char[length];
			GLCALL(glGetProgramInfoLog(m_RendererID, length, &length, log));
			FF_CORE_ERROR("Failed to Link the Program: {}", log);

			glDeleteProgram(m_RendererID);

			glDeleteShader(vs);
			glDeleteShader(fs);
			delete []log;
			return;
		}

		GLCALL(glDeleteShader(vs));
		GLCALL(glDeleteShader(fs));
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

}