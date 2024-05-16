#include "ffpch.h"
#include "Renderer.h"
#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace FireFly
{
	VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			FF_CORE_ERROR("API is not specified!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		FF_CORE_ERROR("Unknown API!");
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			FF_CORE_ERROR("API is not specified!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		}

		FF_CORE_ERROR("Unknown API!");
		return nullptr;
	}
}