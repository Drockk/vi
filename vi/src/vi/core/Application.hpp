#pragma once

#include "vi/core/Window.hpp"
#include "vi/events/ApplicationEvent.hpp"

#include <memory>

namespace vi
{
class Application
{
public:
    Application();
    virtual ~Application() = default;

    void run();

    void onEvent(Event& e);

private:
    bool onWindowClose(WindowCloseEvent& e);

    std::unique_ptr<Window> m_window;
    bool m_running{true};
};

// To be defined in CLIENT
std::unique_ptr<Application> createApplication();
}
