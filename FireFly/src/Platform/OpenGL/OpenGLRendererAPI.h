#pragma once

#include "Core/Renderer/Renderer.h"

namespace FireFly
{
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void SetClearColor(glm::vec4 color) override;
		virtual void ClearColor() override;
		virtual void Init() override;

		virtual void PreForRender(const VertexArray* vertexarray) override;

		virtual void UploadUniform(const VertexArray* vertexarray, const glm::mat4& mat, const std::string name) override;

		virtual void DrawIndexed(const VertexArray* vertexarray) override;
	};

}