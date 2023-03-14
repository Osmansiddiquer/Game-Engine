#pragma once

#include "Game-Engine/Events/Event.h"

namespace Game-Engine {

	class ApplicationEvent : public Event {
	public:
		virtual ~ApplicationEvent() = default;

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class WindowResizeEvent : public ApplicationEvent {
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)

	private:
		unsigned int m_Width, m_Height;
	};

	class WindowCloseEvent : public ApplicationEvent {
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
	};

	class AppTickEvent : public ApplicationEvent {
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
	};

	class AppUpdateEvent : public ApplicationEvent {
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
	};

	class AppRenderEvent : public ApplicationEvent {
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
	};
}
