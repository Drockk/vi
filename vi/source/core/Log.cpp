#include "Log.hpp"

#include <memory>
#include <vector>

#include <spdlog/async.h>
#include "spdlog/cfg/env.h" 
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace {
	void create_logger(const std::string& name, const std::vector<spdlog::sink_ptr>& sinks) {
		auto logger = std::make_shared<spdlog::async_logger>(name, sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
		logger->set_level(spdlog::level::trace);
		logger->flush_on(spdlog::level::trace);
		spdlog::register_logger(logger);
	}
}

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

		create_logger("CORE", sinks);
		create_logger("APP", sinks);
	}
}