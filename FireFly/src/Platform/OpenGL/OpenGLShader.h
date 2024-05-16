#pragma once
#include "Core/Renderer/Shader.h"

namespace FireFly
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSRC, const std::string& fragmentSRC);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		
	private:
		unsigned int m_RendererID;
	};
}