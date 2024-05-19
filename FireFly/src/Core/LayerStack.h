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
		void OnUpdate();
		void OnImGuiRender();

		inline const std::vector<Ref<Layer>>& GetLayers() { return m_Layers; }
		inline const std::vector<Ref<Layer>>& GetOverLayers() { return m_OverLayers; }
	private:
		std::vector<Ref<Layer>> m_Layers;
		std::vector<Ref<Layer>> m_OverLayers;
	};
}