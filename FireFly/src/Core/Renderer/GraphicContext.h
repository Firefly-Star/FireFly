#pragma once

namespace FireFly
{
	class GraphicContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;
	};
}