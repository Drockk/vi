#include "Application.hpp"
#include "Log.hpp"

namespace vi::core {
	void Application::init() {
		Log::init();
		VI_CORE_INFO("Application initialized");
	}

	void Application::run() {
		VI_CORE_INFO("Application running");
	}

	void Application::shutdown() {
		VI_CORE_INFO("Application shutting down");
	}
}