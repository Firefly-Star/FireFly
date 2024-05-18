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
		virtual void SetVertexBuffer(VertexBuffer* vertexbuffer);

		virtual void SetIndexBuffer(unsigned int* indices, unsigned int size);
		virtual void SetIndexBuffer(IndexBuffer* indexbuffer);

		virtual void SetShader(const std::string& vsrc, const std::string& fsrc);
		virtual void SetShader(Shader* shader);
		
		virtual void SetBufferLayout(BufferLayout& layout);

		inline Shader* GetShader() const { return m_Shader; }
		inline BufferLayout* GetBufferLayout() const { return m_BufferLayout; }

		virtual void PreForRender() const = 0;

		virtual void Render() const = 0;
	protected:
		VertexBuffer* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;
		BufferLayout* m_BufferLayout;
		Shader* m_Shader;

		unsigned int m_ID;

		static unsigned int s_Count;
		static unsigned int s_ReadyForRendering;
	};
}