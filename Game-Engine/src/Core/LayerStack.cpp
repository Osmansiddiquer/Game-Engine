#include "Engine_pch.h"
#include "LayerStack.h"
#include "Log.h"
namespace Engine 
{
	LayerStack::LayerStack():m_LayerInsert(m_layerStack.begin())
	{
	
	}

	LayerStack::~LayerStack()
	{
		for (auto layer : m_layerStack)
			delete layer;
	}

	void LayerStack::PushLayer(Layer& layer)
	{
		m_LayerInsert = m_layerStack.insert(m_LayerInsert, &layer);
		layer.OnAttach();
		ENGINE_CORE_DEBUG_INFO("Layer: {0} pushed successfully", layer.GetName());
	}

	void LayerStack::PushOverlay(Layer& overlay)
	{
		m_layerStack.push_back(&overlay);
		overlay.OnAttach();
		ENGINE_CORE_DEBUG_INFO("Overlay: {0} pushed successfully", overlay.GetName());
	}

	void LayerStack::PopLayer(Layer& layer)
	{
		//ASSERT(m_layerStack.size() != 0, "Layer stack is empty!");
		std::vector<Layer*>::iterator i = std::find(m_layerStack.begin(), m_LayerInsert, &layer);
		if (i != m_LayerInsert) 
		{
			m_LayerInsert = m_layerStack.erase(i);
			layer.OnDetach();
			ENGINE_CORE_DEBUG_INFO("Layer: {0} popped successfully", layer.GetName());
		}
		else
		{
			ENGINE_CORE_DEBUG_WARN("Layer: {0} not found", layer.GetName());
		}
	}

	void LayerStack::PopOverlay(Layer& overlay)
	{
		std::vector<Layer*>::iterator i = std::find(m_LayerInsert, m_layerStack.end(), &overlay);
		if (i != m_LayerInsert)
		{
			m_LayerInsert = m_layerStack.erase(i);
			overlay.OnDetach();
			ENGINE_CORE_DEBUG_INFO("Overlay: {0} popped successfully", overlay.GetName());
		}
		else
		{
			ENGINE_CORE_DEBUG_WARN("Overlay: {0} not found", overlay.GetName());
		}
	}
}