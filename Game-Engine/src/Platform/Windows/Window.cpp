#include "Engine_pch.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Core/Log.h"
#include "Window.h" 
namespace Engine {
	static bool GLFWInitialized = false;
	static bool gladInitialized = false;
	WindowsWindow::WindowsWindow(const Engine::WindowProperties& windowproperties) {
		Init(windowproperties);
	}
	void WindowsWindow::SetEventCallBack(const EventCallBackFn& callback)
	{
		m_EventCallBackFunction = callback;
	}
	Window* Window::Create(const WindowProperties& wp)
	{
		return new WindowsWindow(wp);
	}
	void WindowsWindow::Init(const WindowProperties& properties)
	{
		m_WindowProperties = *new Engine::WindowProperties(properties);
		m_pointers = { &m_WindowProperties, &m_EventCallBackFunction };

		ENGINE_CORE_INFO("Window created: {0} ----- {1} x {2} ----- VSync: {3}", m_WindowProperties.title, m_WindowProperties.height, m_WindowProperties.width, (m_WindowProperties.VSync) ? "True" : "False");
		if (!GLFWInitialized) {
			bool success = glfwInit();
			if (!success) { ENGINE_CORE_ERROR("GLFW initialization failed"); __debugbreak(); }
			else GLFWInitialized = true;
			glfwSetErrorCallback([](int errorcode, const char *description) {
				ENGINE_CORE_ERROR("GLFW: {0} -- {1}", errorcode, description);
			});
		}
		m_window = glfwCreateWindow(m_WindowProperties.width,
			m_WindowProperties.height,
			m_WindowProperties.title.c_str(), nullptr, nullptr);
		if (m_window == nullptr)
		{
			ENGINE_CORE_ERROR("GLFW window creation failed"); __debugbreak();
		}

		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_pointers);
		SetVSync(m_WindowProperties.VSync);

		if (!gladInitialized)
		{
			gladInitialized = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			if (!gladInitialized) { ENGINE_CORE_ERROR("Glad initialization failed!"); __debugbreak(); }
			else ENGINE_CORE_DEBUG_INFO("Glad succesfully initialized");
			//ASSERT(gladInitialized, "Falied to initialize Glad!");
		}

		//Setting callbacks
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window ,int width, int height) {
			Pointers pointer = *(Pointers*)glfwGetWindowUserPointer(window);
			(*pointer.properties).height = height;
			(*pointer.properties).width = width;
			(*pointer.eventfn)(*new WindowResizeEvent(width, height));
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			Pointers pointer = *(Pointers*)glfwGetWindowUserPointer(window);
			(*pointer.eventfn)(*new WindowCloseEvent());
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			Pointers pointer = *(Pointers*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS:
					(*pointer.eventfn)(*new KeyPressedEvent(key));
					break;
				case GLFW_REPEAT:
					(*pointer.eventfn)(*new KeyPressedEvent(key, true));
					break;
				case GLFW_RELEASE:
					(*pointer.eventfn)(*new KeyReleasedEvent(key));
					break;
			}
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
			Pointers pointer = *(Pointers*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS:
					(*pointer.eventfn)(*new MouseButtonPressedEvent(button));
					break;
				case GLFW_RELEASE:
					(*pointer.eventfn)(*new MouseButtonReleasedEvent(button));
					break;
			}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double x_offset, double y_offset) {
			Pointers pointer = *(Pointers*)glfwGetWindowUserPointer(window);
			(*pointer.eventfn)(*new MouseScrolledEvent(x_offset, y_offset));
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x_pos, double y_pos) {
			Pointers pointer = *(Pointers*)glfwGetWindowUserPointer(window);
			(*pointer.eventfn)(*new MouseMovedEvent(x_pos, y_pos));
		});
	}
	void WindowsWindow::Shutdown() {
		
		glfwDestroyWindow(m_window);
	}
	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}
	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(m_window);
	}
	bool WindowsWindow::isVsync() const
	{
		return m_WindowProperties.VSync;
	}
	void WindowsWindow::SetVSync(bool enabled) {
		glfwSwapInterval(enabled);
		m_WindowProperties.VSync = enabled;
	}

	Vec2 WindowsWindow::GetWindowPos()
	{
		int x, y;
		glfwGetWindowPos(m_window, &x, &y);
		return Vec2(x, y);
	}
}