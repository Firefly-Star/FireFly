#pragma once

#include "Core/Renderer/Renderer.h"

namespace FireFly
{
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void SetClearColor(glm::vec4 color);
		virtual void ClearColor();

		virtual void DrawIndexed(const VertexArray* vertexarray) override;
	};

}