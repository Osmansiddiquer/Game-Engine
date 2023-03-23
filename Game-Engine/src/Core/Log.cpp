#include "Engine_pch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace Engine 
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$"); //color, then timestamp, then logger name, then message
		// create color multi threaded logger
		s_CoreLogger = spdlog::stderr_color_mt("ENGINE");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}