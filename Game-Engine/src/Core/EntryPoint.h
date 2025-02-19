#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();
	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}
#else
#error Engine only supports windows at the moment
#endif