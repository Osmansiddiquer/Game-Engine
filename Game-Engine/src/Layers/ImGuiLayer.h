#pragma once
#include "Core/Layer.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace Engine 
{
	class ENGINE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);
	private:
		void OnKeyPressedEvent(KeyPressedEvent& e);
		void OnMouseMovedEvent(MouseMovedEvent& e);
		void OnKeyReleasedEvent(KeyReleasedEvent& e);
		void OnMousePressedEvent(MouseButtonPressedEvent& e);
		void OnMouseReleasedEvent(MouseButtonReleasedEvent& e);
		void OnMouseScrolledEvent(MouseScrolledEvent& e);
		void OnWindowResizeEvent(WindowResizeEvent& e);
	};
}

