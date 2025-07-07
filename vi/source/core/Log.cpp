#include "Log.hpp"

#include <memory>
#include <vector>

#include <spdlog/async.h>
#include "spdlog/cfg/env.h" 
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace vi::core {
	Log::~Log() {
		spdlog::shutdown();
	}

	void Log::init() {
		spdlog::cfg::load_env_levels();

		spdlog::init_thread_pool(8192, 1);

		auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		stdout_sink->set_pattern("%^[%T] [%n]: %v%$");

		auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("vi.log", true);
		file_sink->set_pattern("[%T] [%l] [%n]: %v");

		std::vector<spdlog::sink_ptr> sinks {stdout_sink, file_sink};

		auto core_logger = std::make_shared<spdlog::async_logger>("CORE", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
		core_logger->set_level(spdlog::level::trace);
		core_logger->flush_on(spdlog::level::trace);
		spdlog::register_logger(core_logger);

		auto app_logger = std::make_shared<spdlog::async_logger>("APP", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
		app_logger->set_level(spdlog::level::trace);
		app_logger->flush_on(spdlog::level::trace);
		spdlog::register_logger(app_logger);
	}
}