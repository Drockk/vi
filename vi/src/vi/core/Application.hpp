#pragma once

#include <memory>
#include "vi/core/Window.hpp"

namespace vi
{
class Application
{
public:
    Application();
    virtual ~Application() = default;

    void run();

private:
    std::unique_ptr<Window> m_window;
    bool m_running{true};
};

// To be defined in CLIENT
std::unique_ptr<Application> createApplication();
}
