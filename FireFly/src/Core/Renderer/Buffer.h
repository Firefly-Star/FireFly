#pragma once

namespace FireFly
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer(){}

		static VertexBuffer* Create(float* vertices, unsigned int size);

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer(){}

		static IndexBuffer* Create(unsigned int* indices, unsigned int size);

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
 	};
}