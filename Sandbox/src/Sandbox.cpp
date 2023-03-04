#include <Engine.h>
using namespace Engine;
class Sandbox : public Application
{
public:
	Sandbox() 
	{
		ENGINE_INFO("SandBox Started!");
	}
	~Sandbox()
	{

	}
};

Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}