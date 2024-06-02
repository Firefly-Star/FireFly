#include "ffpch.h"

#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace FireFly
{
	OpenGLVertxArray::OpenGLVertxArray()
		:VertexArray(), m_RendererID(0)
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	OpenGLVertxArray::~OpenGLVertxArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertxArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertxArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertxArray::PreForRender() const
	{
		if (s_ReadyForRendering != m_ID)
		{
			glBindVertexArray(m_RendererID);
		
			if (m_Shader)
			{
				m_Shader->Bind();
			}
			m_VertexBuffer->Bind();
			m_IndexBuffer->Bind();

			m_BufferLayout->UploadLayout();

			s_ReadyForRendering = m_ID;
		}
	}

	void OpenGLVertxArray::Render() const
	{
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}