#include "ffpch.h"

#include "LayerStack.h"

namespace FireFly
{
	LayerStack::LayerStack()
	{

	}

	LayerStack::~LayerStack()
	{

	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace_back(std::shared_ptr<Layer>(layer));
	}

	void LayerStack::PushOverLayer(Layer* layer)
	{
		m_OverLayers.emplace_back(std::shared_ptr<Layer>(layer));
	}

	bool LayerStack::EraseLayer(Layer* layer)
	{
		auto it = std::find_if(m_Layers.begin(), m_Layers.end(), [layer](std::shared_ptr<Layer> l)
			{
				return l.get() == layer;
			});
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			return true;
		}
		return false;
	}

	bool LayerStack::EraseOverLayer(Layer* layer)
	{
		auto it = std::find_if(m_OverLayers.begin(), m_OverLayers.end(), [layer](std::shared_ptr<Layer> l)
			{
				return l.get() == layer;
			});
		if (it != m_OverLayers.end())
		{
			m_OverLayers.erase(it);
			return true;
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

	void LayerStack::OnUpdate(Ref<TimeStep> ts, Ref<Input> input)
	{
		for (auto it = m_OverLayers.end(); it != m_OverLayers.begin();)
		{
			(*--it)->OnUpdate(ts, input);
		}

		for (auto it = m_Layers.end(); it != m_Layers.begin();)
		{
			(*--it)->OnUpdate(ts, input);
		}
	}

	void LayerStack::OnImGuiRender()
	{
		for (auto it = m_OverLayers.end(); it != m_OverLayers.begin();)
		{
			(*--it)->OnImGuiRender();
		}

		for (auto it = m_Layers.end(); it != m_Layers.begin();)
		{
			(*--it)->OnImGuiRender();
		}
	}
}