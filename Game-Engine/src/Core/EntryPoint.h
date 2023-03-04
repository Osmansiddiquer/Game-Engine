#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	std::cout << "Gogog" << std::endl;
	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}
#else
#error Engine only supports windows at the moment
#endif