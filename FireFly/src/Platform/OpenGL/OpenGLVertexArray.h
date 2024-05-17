#pragma once

#include "Core/Renderer/VertexArray.h"

namespace FireFly
{
	class OpenGLVertxArray : public VertexArray
	{
	public:
		OpenGLVertxArray();
		virtual ~OpenGLVertxArray();

		virtual void Bind() const;
		virtual void UnBind() const;

		virtual void PreForRender() const override;

		virtual void Render() const override;
	private:
		unsigned int m_RendererID;
	};
}