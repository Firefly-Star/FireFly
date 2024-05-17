#include "ffpch.h"

#include "OpenGLVertexArray.h"
#include "OpenGLError.h"

#include <glad/glad.h>

namespace FireFly
{
	OpenGLVertxArray::OpenGLVertxArray()
		:VertexArray(), m_RendererID(0)
	{
		GLCALL(glGenVertexArrays(1, &m_RendererID));
	}

	OpenGLVertxArray::~OpenGLVertxArray()
	{
		GLCALL(glDeleteVertexArrays(1, &m_RendererID));
	}

	void OpenGLVertxArray::Bind() const
	{
		GLCALL(glBindVertexArray(m_RendererID));
	}

	void OpenGLVertxArray::UnBind() const
	{
		GLCALL(glBindVertexArray(0));
	}

	void OpenGLVertxArray::PreForRender() const
	{
		GLCALL(glBindVertexArray(m_RendererID));
		
		m_Shader->Bind();
		m_VertexBuffer->Bind();
		m_IndexBuffer->Bind();

		m_BufferLayout->UploadLayout();
	}

	void OpenGLVertxArray::Render() const
	{
		GLCALL(glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
	}
}