#pragma once

#include "glm/glm.hpp"

namespace FireFly
{
	enum class ShaderType
	{
		None = 0,
		VertexShaderSRC = 1, FragmentShaderSRC = 2
	};

	class Shader
	{
	public:
		virtual ~Shader() {};

		static Shader* Create(const std::string& vertexSRC, const std::string& fragmentSRC);

		static void ParseFile(const std::string& filepath, ShaderType targetType, std::pair<ShaderType, std::string>& shaderSRC);

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void UploadUniform(const glm::mat4& mat, const std::string& name) = 0;
	};

}