#include "ffpch.h"
#include "OpenGLBuffer.h"
#include "OpenGLError.h"

#include <glad/glad.h>

namespace FireFly
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned int size)
		:m_RendererID(0)
	{
		GLCALL(glGenBuffers(1, &m_RendererID));
		GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));

		GLCALL(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		GLCALL(glDeleteBuffers(1, &m_RendererID));
	}

	void OpenGLVertexBuffer::Bind() const
	{
		GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* indices, unsigned int size)
		:m_RendererID(0)
	{
		GLCALL(glGenBuffers(1, &m_RendererID));
		GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));

		GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW));
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		GLCALL(glDeleteBuffers(1, &m_RendererID));
	}

	void OpenGLIndexBuffer::Bind() const
	{
		GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}
