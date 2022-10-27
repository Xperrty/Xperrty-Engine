#pragma once
#include "../Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace Xperrty {

	class Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return clientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};
}

#define XP_TRACE(...)	::Xperrty::Log::getCoreLogger()->trace(__VA_ARGS__)
#define XP_INFO(...)	::Xperrty::Log::getCoreLogger()->info(__VA_ARGS__)
#define XP_WARN(...)	::Xperrty::Log::getCoreLogger()->warn(__VA_ARGS__)
#define XP_ERROR(...)	::Xperrty::Log::getCoreLogger()->error(__VA_ARGS__)
#define XP_FATAL(...)	::Xperrty::Log::getCoreLogger()->fatal(__VA_ARGS__)

#define APP_TRACE(...)	::Xperrty::Log::getClientLogger()->trace(__VA_ARGS__)
#define APP_INFO(...)	::Xperrty::Log::getClientLogger()->info(__VA_ARGS__)
#define APP_WARN(...)	::Xperrty::Log::getClientLogger()->warn(__VA_ARGS__)
#define APP_ERROR(...)	::Xperrty::Log::getClientLogger()->error(__VA_ARGS__)
#define APP_FATAL(...)	::Xperrty::Log::getClientLogger()->fatal(__VA_ARGS__)