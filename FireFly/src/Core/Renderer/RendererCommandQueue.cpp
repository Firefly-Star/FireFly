#include "ffpch.h"
#include "RendererCommandQueue.h"

#if 01
namespace FireFly
{
	RendererCommandQueue::RendererCommandQueue()
		:m_CommandCount(0)
	{
		m_OriginCommandBuffer = new byte[FF_COMMAND_BUFFER_SIZE];
		auto padding = (size_t)m_OriginCommandBuffer % 8;

		m_CommandBuffer = m_OriginCommandBuffer;
		if (padding != 0) // alignment of 8
		{
			m_CommandBuffer = m_OriginCommandBuffer + 8 - padding;
		}
		m_CommandBufferWorkPtr = m_CommandBuffer;
		memset(m_CommandBuffer, 0, FF_COMMAND_BUFFER_SIZE);
	}

	RendererCommandQueue::~RendererCommandQueue()
	{
		delete[] m_OriginCommandBuffer;
		m_OriginCommandBuffer = nullptr;
		m_CommandBuffer = nullptr;
		m_CommandBufferWorkPtr = nullptr;
	}

	void RendererCommandQueue::Submit(CommandFunc fnptr, const byte* params, unsigned int size, unsigned int alignment)
	{
		// The memory layout should be fn / size / alignment / params

		//function
		*(CommandFunc*)m_CommandBufferWorkPtr = fnptr;
		m_CommandBufferWorkPtr += sizeof(CommandFunc); 
		// size
		*(unsigned int*)m_CommandBufferWorkPtr = size;
		m_CommandBufferWorkPtr += sizeof(unsigned int);
		// alignment
		*(unsigned int*)m_CommandBufferWorkPtr = alignment;
		m_CommandBufferWorkPtr += sizeof(unsigned int);

		// alignment when memcpy
		{
			auto padding = (size_t)m_CommandBufferWorkPtr % alignment;
			if (padding != 0)
			{
				m_CommandBufferWorkPtr += alignment - padding;
			}
		}
		// params
		if (size != 0)
		{
			memcpy(m_CommandBufferWorkPtr, params, size);
			m_CommandBufferWorkPtr += size;
		}

		// alignment for the next command
		{
			auto padding = (size_t)m_CommandBufferWorkPtr % 8;
			if (padding != 0)
			{
				m_CommandBufferWorkPtr += 8 - padding;
			}
		}

		m_CommandCount++;

		FF_CORE_ASSERT((m_CommandBufferWorkPtr - m_CommandBuffer) <= FF_COMMAND_BUFFER_SIZE, "Command queue overflow!");
	}

	void RendererCommandQueue::Execute()
	{
		//FF_CORE_TRACE("Renderer Command Queue: {0}commands, {1}bytes", m_CommandCount, m_CommandBufferWorkPtr - m_CommandBuffer);
		byte* workPtr = m_CommandBuffer;

		for (unsigned int i = 1; i <= m_CommandCount; i++)
		{
			// function
			CommandFunc func = *(CommandFunc*)workPtr;
			workPtr += sizeof(CommandFunc);
			// size
			unsigned int size = *(unsigned int*)workPtr;
			workPtr += sizeof(unsigned int);
			FF_CORE_TRACE("Executing the command at index {}, size:{}, sizePtr:{}", i, *(unsigned int*)workPtr, (size_t)workPtr);
			//alignment
			unsigned int alignment = *(unsigned int*)workPtr;
			workPtr += sizeof(unsigned int);

			// alignment when memcpy
			{
				auto padding = (size_t)workPtr % alignment;
				if (padding != 0)
				{
					workPtr += alignment - padding;
				}
			}
			// params
			func(workPtr);
			workPtr += size;

			// alignment for the next command
			{
				auto padding = (size_t)workPtr % 8;
				if (padding != 0)
				{
					workPtr += 8 - padding;
				}
			}
		}

		m_CommandBufferWorkPtr = m_CommandBuffer;
		m_CommandCount = 0;
	}

}
#endif