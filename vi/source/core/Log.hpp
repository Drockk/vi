#pragma once
#include <spdlog/spdlog.h>

namespace vi::core {
	class Log {
	public:
		~Log();

		static void init();
	};
}

#define VI_CORE_TRACE(...)    ::spdlog::get("CORE")->trace(__VA_ARGS__)
#define VI_CORE_INFO(...)     ::spdlog::get("CORE")->info(__VA_ARGS__)
#define VI_CORE_WARN(...)     ::spdlog::get("CORE")->warn(__VA_ARGS__)
#define VI_CORE_ERROR(...)    ::spdlog::get("CORE")->error(__VA_ARGS__)
#define VI_CORE_CRITICAL(...) ::spdlog::get("CORE")->critical(__VA_ARGS__)

#define VI_APP_TRACE(...)    ::spdlog::get("APP")->trace(__VA_ARGS__)
#define VI_APP_INFO(...)     ::spdlog::get("APP")->info(__VA_ARGS__)
#define VI_APP_WARN(...)     ::spdlog::get("APP")->warn(__VA_ARGS__)
#define VI_APP_ERROR(...)    ::spdlog::get("APP")->error(__VA_ARGS__)
#define VI_APP_CRITICAL(...) ::spdlog::get("APP")->critical(__VA_ARGS__)