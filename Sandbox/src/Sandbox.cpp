#include <Engine.h>
using namespace Engine;

class ExampleLayer : public Layer
{
public:
	ExampleLayer() :Layer("gog9") {}
	void OnUpdate()
	{}
	void OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>([this](MouseButtonPressedEvent& e) {
				ENGINE_INFO("{0}: Event recieved --- {1}", GetName(), e.ToString());
				return true;
			});
	}
};
class Sandbox : public Application
{
public:
	Sandbox() 
	{
		ENGINE_INFO("SandBox Started!"); 
		PushLayer(*new ExampleLayer());
		PushOverlay(*new ImGuiLayer());
	}
	~Sandbox()
	{

	}
};

Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}