#include "Engine_pch.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "Application.h"
namespace Engine {
	Application* Application::s_Instance = nullptr;
	Application::Application() 
	{
		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetEventCallBack(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		s_Instance = this;
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e) 
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) { //takes a function as an argument
			m_running = false;
			return true;
		});
		for (Layer* layer : m_layerStack| std::views::reverse) //tranversing the layer stack in reverse
		{
			layer->OnEvent(e);
			if (e.isHandled())
				break;
		}
		if(!e.isHandled())
			ENGINE_CORE_DEBUG_TRACE("Event Not Handled: {0}", e.ToString());
	}
	
	void Application::Run() 
	{	
		float f[4];
		bool my_tool_show;
		while (m_running) {
			for (Layer* layer : m_layerStack)
			{
				layer->OnUpdate();
			}
			m_window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer& layer)
	{
		m_layerStack.PushLayer(layer);

	}

	void Application::PopLayer(Layer& layer)
	{
		m_layerStack.PopLayer(layer);
	}

	void Application::PushOverlay(Layer& layer)
	{
		m_layerStack.PushOverlay(layer);

	}

	void Application::PopOverlay(Layer& layer)
	{
		m_layerStack.PopOverlay(layer);
	}

	Application* Application::GetInstance()
	{
		return s_Instance;
	}
}
