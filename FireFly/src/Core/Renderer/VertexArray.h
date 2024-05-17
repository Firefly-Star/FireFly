#pragma once

#include "Buffer.h"
#include "Shader.h"

namespace FireFly
{
	class VertexArray
	{
	public:
		VertexArray();
		virtual ~VertexArray();

		static VertexArray* Create();

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetVertexBuffer(float* vertices, unsigned int size);
		virtual void SetVertexBuffer(const VertexBuffer& vertexbuffer);

		virtual void SetIndexBuffer(unsigned int* indices, unsigned int size);
		virtual void SetIndexBuffer(const IndexBuffer& indexbuffer);

		virtual void SetShader(const std::string& vsrc, const std::string& fsrc);
		virtual void SetShader(const Shader& shader);
		
		virtual void SetBufferLayout(BufferLayout& layout);

		inline BufferLayout* GetBufferLayout() const { return m_BufferLayout; }

		virtual void PreForRender() const = 0;

		virtual void Render() const = 0;
	protected:
		const VertexBuffer* m_VertexBuffer;
		const IndexBuffer* m_IndexBuffer;
		BufferLayout* m_BufferLayout;
		const Shader* m_Shader;

		unsigned int m_ID;

		static unsigned int s_Count;
		static unsigned int s_ReadyForRendering;
	};
}