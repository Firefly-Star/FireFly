#include "ffpch.h"

#include "LayerStack.h"

namespace FireFly
{
	LayerStack::LayerStack()
	{

	}

	LayerStack::~LayerStack()
	{
		for (auto layer : m_Layers)
		{
			delete layer;
			layer = nullptr;
		}

		for (auto layer : m_OverLayers)
		{
			delete layer;
			layer = nullptr;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace_back(layer);
	}

	void LayerStack::PushOverLayer(Layer* layer)
	{
		m_OverLayers.emplace_back(layer);
	}

	bool LayerStack::EraseLayer(Layer* layer)
	{
		for (auto it = m_Layers.end(); it != m_Layers.begin();)
		{
			if (*(--it) == layer)
			{
				m_Layers.erase(it);
				return true;
			}
		}
		return false;
	}

	bool LayerStack::EraseOverLayer(Layer* layer)
	{
		for (auto it = m_OverLayers.end(); it != m_OverLayers.begin();)
		{
			if (*(--it) == layer)
			{
				delete* (it);
				m_OverLayers.erase(it);
				return true;
			}
		}
		return false;
	}

	bool LayerStack::OnEvent(Event& e)
	{
		for (auto it = m_OverLayers.end(); it != m_OverLayers.begin() && !e.IsHandled();)
		{
			(*--it)->OnEvent(e);
		}

		for (auto it = m_Layers.end(); it != m_Layers.begin() && !e.IsHandled();)
		{
			(*--it)->OnEvent(e);
		}
		return e.IsHandled();
	}

	void LayerStack::OnUpdate()
	{
		for (auto it = m_OverLayers.end(); it != m_OverLayers.begin();)
		{
			(*--it)->OnUpdate();
		}

		for (auto it = m_Layers.end(); it != m_Layers.begin();)
		{
			(*--it)->OnUpdate();
		}
	}
}