#pragma once
#include "Core.h"
#include "LayerStack.h"
#include "Window.h"
namespace Engine 
{
	class ENGINE_API Application
	{
		std::unique_ptr<Window> m_window;
		bool m_running = true;
		LayerStack m_layerStack;
		static Application* s_Instance;
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		inline Window &GetWindow() { return *m_window; }
		void PushLayer(Layer& layer);
		void PopLayer(Layer& layer);
		void PushOverlay(Layer& layer);
		void PopOverlay(Layer& layer);
		static Application* GetInstance();
	};
	//To be defined in CLIENT
	Application* CreateApplication();
}

