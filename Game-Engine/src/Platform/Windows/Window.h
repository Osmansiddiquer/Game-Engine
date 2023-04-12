#pragma once
#include "Engine_pch.h"
#include "imgui.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"
#include "Platform/GLFW/imgui_impl_glfw.h"
#include "Events/Event.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Core/Window.h"
namespace Engine {
	class ENGINE_API WindowsWindow: public Engine::Window
	{
		using EventCallBackFn = std::function<void(Engine::Event&)>;
	public:
		WindowsWindow(const WindowProperties& windowproperties);
		virtual Vec2 GetWindowPos();
		virtual ~WindowsWindow();

		void OnUpdate() override;

		bool isVsync() const override;

		void SetEventCallBack(const EventCallBackFn& callback) override;
		void SetVSync(bool enbabled) override;
	private:
		virtual void Init(const WindowProperties&);
		virtual void Shutdown();
		struct Pointers {
			WindowProperties *properties;
			EventCallBackFn *eventfn;
		};
		Pointers m_pointers;
		GLFWwindow* m_window;
	};
}

