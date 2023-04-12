#pragma once
#include "Engine_pch.h"
#include "Core/Core.h"
#include "Events/Event.h"

namespace Engine {
	using EventCallBackFn = std::function<void(Event&)>;

	class WindowProperties
	{
	public:
		bool VSync;
		std::string title;
		unsigned int width, height;

		WindowProperties(unsigned width = 1280, unsigned height = 720, const std::string& title = "Game Engine")
			:width(width), height(height), title(title), VSync(true){}
	};
	class ENGINE_API Window 
	{
	protected:
		WindowProperties m_WindowProperties;
		EventCallBackFn m_EventCallBackFunction;
	public:
		virtual ~Window() {};

		virtual void OnUpdate() = 0;
		virtual	Vec2 GetWindowPos() = 0;
		unsigned int GetWidth() const { return this->m_WindowProperties.width; }
		unsigned int GetHeight() const { return this->m_WindowProperties.height; }
		virtual bool isVsync() const = 0;

		virtual void SetEventCallBack(const EventCallBackFn& callback) = 0;
		virtual void SetVSync(bool enbabled) = 0;

		static Window* Create(const WindowProperties& wp = WindowProperties());
	};
}