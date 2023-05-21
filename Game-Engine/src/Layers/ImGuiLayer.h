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
		void OnKeyPressedEvent(Event& e);
		void OnMouseMovedEvent(Event& e);
		void OnKeyReleasedEvent(Event& e);
		void OnMousePressedEvent(Event& e);
		void OnMouseReleasedEvent(Event& e);
		void OnMouseScrolledEvent(Event& e);
		void OnWindowResizeEvent(Event& e);
	};
}

