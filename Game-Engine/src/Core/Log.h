#pragma once
#include "Core.h"
#include <spdlog/spdlog.h>

namespace Engine {
	class ENGINE_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger; //ptr to the Core Logger
		static std::shared_ptr<spdlog::logger> s_ClientLogger; //ptr to the Client Logger
	public:
		static void Init();
		//reference getter functions for the loggers
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};
}
// Core Log macro functions
#define ENGINE_CORE_INFO(...)  ::Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_CORE_TRACE(...) ::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ENGINE_CORE_WARN(...)  ::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_CORE_ERROR(...) ::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#ifdef ENGINE_DEBUG
#define ENGINE_CORE_DEBUG_INFO(...) ::Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_CORE_DEBUG_TRACE(...) ::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ENGINE_CORE_DEBUG_WARN(...) ::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_CORE_DEBUG_ERROR(...) ::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#else
#define ENGINE_CORE_DEBUG_INFO(...) 
#define ENGINE_CORE_DEBUG_TRACE(...)
#define ENGINE_CORE_DEBUG_WARN(...) 
#define ENGINE_CORE_DEBUG_ERROR(...)
#endif
// Client Log macro functions
#define ENGINE_INFO(...)      ::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define ENGINE_TRACE(...)     ::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ENGINE_WARN(...)      ::Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ENGINE_ERROR(...)     ::Engine::Log::GetClientLogger()->error(__VA_ARGS__)