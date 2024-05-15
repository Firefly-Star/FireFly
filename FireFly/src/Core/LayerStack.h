#pragma once

#include "Core.h"

#include "Events/Event.h"
#include "Layer.h"

namespace FireFly
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* layer);

		bool EraseLayer(Layer* layer);
		bool EraseOverLayer(Layer* layer);

		bool OnEvent(Event& e);

		inline const std::vector<Layer*>& GetLayers() { return m_Layers; }
		inline const std::vector<Layer*>& GetOverLayers() { return m_OverLayers; }
	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*> m_OverLayers;
	};
}