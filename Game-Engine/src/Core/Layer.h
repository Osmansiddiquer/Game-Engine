#pragma once
#include <Events/Event.h>
namespace Engine {
	class ENGINE_API Layer
	{
	public:
		Layer(std::string Name = "Layer");
		virtual ~Layer();
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}
		virtual std::string GetName() { return m_debugName; }
		bool enabled;
	private:
		std::string m_debugName;
	};
}