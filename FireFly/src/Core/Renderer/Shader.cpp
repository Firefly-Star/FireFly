#include "ffpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace FireFly
{
	Shader* Shader::Create(const std::string& vertexSRC, const std::string& fragmentSRC)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::OpenGL:
			return new OpenGLShader(vertexSRC, fragmentSRC);
		}

		FF_CORE_ASSERT(false, "Unknown API!");
		return nullptr;
	}

	void Shader::ParseFile(const std::string& filepath, ShaderType targetType, std::pair<ShaderType, std::string>& shaderSRC)
	{
		std::fstream file(filepath);
		std::stringstream ss;

		std::string line;
		ShaderType type = ShaderType::None;

		if (!file.is_open())
		{
			FF_CORE_ERROR("Failed to open the file from {}", filepath);
		}

		while (std::getline(file, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("#shader vertex") != std::string::npos)
				{
					type = ShaderType::VertexShaderSRC;
				}
				if (line.find("#shader fragment") != std::string::npos)
				{
					type = ShaderType::FragmentShaderSRC;
				}
			}
			else
			{
				ss << line << "\n";
			}
		}

		FF_CORE_ASSERT(type == targetType, "Wrong Type!")

			shaderSRC.first = type;
		shaderSRC.second = ss.str();
	}
}