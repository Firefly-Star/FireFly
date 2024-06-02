#pragma once
#include "Utils/TypeStruct.h"

#if 1
namespace FireFly
{
	class RendererCommandQueue
	{
	public:
		// 10MB Buffer
#define FF_COMMAND_BUFFER_SIZE 10 * 1024 * 1024  
		typedef void(*CommandFunc)(byte*);
	public:
		RendererCommandQueue();
		~RendererCommandQueue();
		
		void Submit(CommandFunc fnptr, const byte* params, unsigned int size, unsigned int alignemnt);
		void Execute();
	private:
		byte* m_OriginCommandBuffer;
		byte* m_CommandBuffer;
		byte* m_CommandBufferWorkPtr;
		unsigned int m_CommandCount;
	};
}
#endif