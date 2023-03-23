#pragma once
#include <sstream>
#include "Event.h"

namespace Engine {

	class ENGINE_API ApplicationEvent : public Event {
	public:
		virtual ~ApplicationEvent() = default;

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ENGINE_API WindowResizeEvent : public ApplicationEvent {
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

	class ENGINE_API WindowCloseEvent : public ApplicationEvent {
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
	};

	class ENGINE_API AppTickEvent : public ApplicationEvent {
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
	};

	class ENGINE_API AppUpdateEvent : public ApplicationEvent {
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
	};

	class ENGINE_API AppRenderEvent : public ApplicationEvent {
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
	};
}
