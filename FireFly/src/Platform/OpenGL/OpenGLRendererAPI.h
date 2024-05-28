#pragma once

#include "Core/Renderer/Renderer.h"

namespace FireFly
{
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void SetClearColor(float* color) override;
		virtual void Clear() override;
		virtual void Init() override;
		virtual void SetViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;

		virtual void PreForRender(Ref<VertexArray> vertexarray) override;

		virtual void UploadUniform(Ref<VertexArray> vertexarray, const glm::mat4& mat, const std::string name) override;

		virtual void DrawIndexed(Ref<VertexArray> vertexarray) override;
	};

}