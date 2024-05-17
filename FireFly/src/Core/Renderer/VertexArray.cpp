#include "ffpch.h"

#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace FireFly
{
	unsigned int VertexArray::s_Count = 0;
	unsigned int VertexArray::s_ReadyForRendering = 0;

	VertexArray::VertexArray()
		:m_VertexBuffer(nullptr), m_IndexBuffer(nullptr), m_Shader(nullptr), m_BufferLayout(nullptr), m_ID(++ s_Count)
	{
		m_BufferLayout = BufferLayout::Create();
	}

	VertexArray::~VertexArray()
	{
		delete m_BufferLayout;
		delete m_IndexBuffer;
		delete m_Shader;
		delete m_VertexBuffer;
	}

	VertexArray* VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::OpenGL: return new OpenGLVertxArray();
		}

		FF_CORE_ASSERT(false, "Unknown API!");

		return nullptr;
	}

	void VertexArray::SetVertexBuffer(float* vertices, unsigned int size)
	{
		m_VertexBuffer = VertexBuffer::Create(vertices, size);
	}

	void VertexArray::SetVertexBuffer(const VertexBuffer& vertexbuffer)
	{
		m_VertexBuffer = &vertexbuffer;
	}
	
	void VertexArray::SetIndexBuffer(unsigned int* indices, unsigned int size)
	{
		m_IndexBuffer = IndexBuffer::Create(indices, size);
	}

	void VertexArray::SetIndexBuffer(const IndexBuffer& indexbuffer)
	{
		m_IndexBuffer = &indexbuffer;
	}
	
	void VertexArray::SetShader(const std::string& vsrc, const std::string& fsrc)
	{
		m_Shader = Shader::Create(vsrc, fsrc);
	}

	void VertexArray::SetShader(const Shader& shader)
	{
		m_Shader = &shader;
	}
	
	void VertexArray::SetBufferLayout(BufferLayout& layout)
	{
		m_BufferLayout = &layout;
	}
}