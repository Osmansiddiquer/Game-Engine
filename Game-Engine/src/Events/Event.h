#ifndef EVENT_H
#define EVENT_H

#include "Core/Core.h"

#include <functional>
#include <string>

#define BIT(x) 1<<x
namespace Engine {

enum class EventType
{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory
{
	None = 0,
	EventCategoryApplication    = BIT(0),
	EventCategoryInput          = BIT(1),
	EventCategoryKeyboard       = BIT(2),
	EventCategoryMouse          = BIT(3),
	EventCategoryMouseButton    = BIT(4)
};
#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

class ENGINE_API Event
{
	friend class EventDispatcher;
public:
	virtual ~Event() = default;

	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual int GetCategoryFlags() const = 0;
	virtual std::string ToString() const { return GetName(); }

	bool IsInCategory(EventCategory category)
	{
		return GetCategoryFlags() & category;
	}

	bool isHandled() { return m_handled; }
protected:
	bool m_handled = false;
};

class EventDispatcher
{
public:
	EventDispatcher(Event& event)
		: m_Event(event)
	{
	}
	
	template<class T>
	bool Dispatch(std::function<bool(T&)> func)
	{
		if (m_Event.GetEventType() == T::GetStaticType()) //checks if functionn is 
		{
			m_Event.m_handled |= func(static_cast<T&>(m_Event)); //runs the function
			return true;
		}
		return false;
	}
private:
	Event& m_Event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
	return os << e.ToString();
}
}

#endif 