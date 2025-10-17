#pragma once

#include "vi/core/LayerStack.hpp"
#include "vi/core/Window.hpp"
#include "vi/events/Event.hpp"
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

    void onEvent(Event& t_event);

    void pushLayer(Layer* t_layer);
    void pushOverlay(Layer* t_layer);

private:
    bool onWindowClose(WindowCloseEvent& t_event);

    std::unique_ptr<Window> m_window;
    bool m_running{true};
	LayerStack m_layerStack;
};

// To be defined in CLIENT
std::unique_ptr<Application> createApplication();
} 
