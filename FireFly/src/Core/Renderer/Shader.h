#pragma once

#include "glm/glm.hpp"

namespace FireFly
{
	class Shader
	{
	public:
		enum class ShaderType
		{
			None = 0,
			VertexShaderSRC = 1, FragmentShaderSRC = 2
		};
		
		virtual ~Shader() {};

		static Shader* Create(const std::string& vertexSRC, const std::string& fragmentSRC);
		static Shader* Create(const std::string& filepath);

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void UploadUniform(const glm::mat4& mat, const std::string& name) = 0;
		virtual void UploadUniform(int i, const std::string& name) = 0;
	protected:
		std::unordered_map<ShaderType, std::string> ParseFile(const std::string& filepath);
	};

}