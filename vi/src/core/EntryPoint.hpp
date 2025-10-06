#pragma once

#include "Application.hpp"
#include "Log.hpp"

#include <iostream>

int main (int argc, char** argv)
{
    try {
        vi::Log::init();
        VI_CORE_INFO("Initialized Log");

        auto app = vi::createApplication();
        app->run();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    

    return 0;
}
