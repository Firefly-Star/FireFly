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

		static Ref<VertexArray> Create();

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetVertexBuffer(float* vertices, unsigned int size);

		virtual void SetIndexBuffer(unsigned int* indices, unsigned int size);

		virtual void SetShader(const std::string& vsrc, const std::string& fsrc);
		virtual void SetShader(const std::string& filepath);
		virtual void SetShader(Ref<Shader> shader);
		
		virtual void SetBufferLayout(BufferLayout* layout);

		inline Shader* GetShader() const { return m_Shader.get(); }
		inline BufferLayout* GetBufferLayout() const { return m_BufferLayout.get(); }
		inline unsigned int GetCount() const { return m_IndexBuffer->GetCount(); }

		virtual void PreForRender() const = 0;

		virtual void Render() const = 0;
	protected:
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
		Ref<BufferLayout> m_BufferLayout;
		Ref<Shader> m_Shader;

		unsigned int m_ID;

		static unsigned int s_Count;
		static unsigned int s_ReadyForRendering;
	};
}