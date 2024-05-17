#include "ffpch.h"
#include "Renderer.h"
#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace FireFly
{

	//---------BufferLayout---------
	std::pair<int, int> LayoutElementType_Size(LayoutElementType type)//  .first:size   .second:count
	{
		switch (type)
		{
		case LayoutElementType::Float:     return std::make_pair(4, 1);	         
		case LayoutElementType::Float2:    return std::make_pair(4 * 2, 2);	     
		case LayoutElementType::Float3:    return std::make_pair(4 * 3, 3);	     
		case LayoutElementType::Float4:    return std::make_pair(4 * 4, 4);	     
		case LayoutElementType::Mat3:      return std::make_pair(4 * 3 * 3, 9);	 
		case LayoutElementType::Mat4:      return std::make_pair(4 * 4 * 4, 16);
		case LayoutElementType::Int:       return std::make_pair(4, 1);	         
		case LayoutElementType::Int2:      return std::make_pair(4 * 2, 2);	     
		case LayoutElementType::Int3:      return std::make_pair(4 * 3, 3);	     
		case LayoutElementType::Int4:      return std::make_pair(4 * 4, 4);	     
		}

		FF_CORE_ASSERT(false, "Unknown Type!");
		return std::make_pair(0, 0);
	}

	BufferLayout* BufferLayout::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			FF_CORE_ERROR("API is not specified!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLBufferLayout();
		}

		FF_CORE_ERROR("Unknown API!");
		return nullptr;
	}

	void BufferLayout::Push(LayoutElement element)
	{
		m_Elements.push_back(element);
		m_Stride += LayoutElementType_Size(element.type).first;
	}

	void BufferLayout::Pop(const std::string& name)
	{
		auto it = std::find_if(m_Elements.begin(), m_Elements.end(), [name](LayoutElement element) { return element.name == name; });
		if (it == m_Elements.end())
		{
			FF_CORE_WARN("Layout element named {0} is not found!", name);
			return;
		}
		m_Elements.erase(it);
		m_Stride -= LayoutElementType_Size((*it).type).first;
	}

	//--------VertexBuffer-----------
	VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		FF_CORE_ASSERT(false, "Unknown API!");
		return nullptr;
	}

	//----------IndexBuffer----------
	IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		}

		FF_CORE_ASSERT(false, "Unknown API!");
		return nullptr;
	}
}