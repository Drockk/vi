#include <source/core/Application.hpp>

#include <iostream>

int main() {
	try {
		auto app = vi::core::Application();
		app.init();
		app.run();
		app.shutdown();
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
