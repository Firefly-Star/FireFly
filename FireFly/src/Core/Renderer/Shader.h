#pragma once

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

		void virtual Bind() const = 0;
		void virtual UnBind() const = 0;
	};

}