#pragma once
#include "Layer.h"
namespace Engine 
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		void PushLayer(Layer& layer); //adds a layer at the end of the layers
		void PushOverlay(Layer& overlay); //adds an overlay at the end of the overlays
		
		void PopLayer(Layer& layer); // dettaches a layer
		void PopOverlay(Layer& overlay); // dettaches an overlay

		std::vector<Layer*>::iterator begin() { return m_layerStack.begin(); } // returns an iterators to the start
		std::vector<Layer*>::iterator end() { return m_layerStack.end(); } // returns an iterator to the end
	private:
		std::vector<Layer*> m_layerStack;
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}


