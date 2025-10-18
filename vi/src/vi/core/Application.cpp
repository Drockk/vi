#include "vi/core/Application.hpp"
#include "vi/core/Log.hpp"

//TODO: temporary //////////////////////////////
#include <Windows.h>
#include <gl/GL.h>
#include <GLFW/glfw3.h>
///////////////////////////////////////////////

namespace vi
{
    Application::Application()
    {
        m_window = Window::create();
        m_window->setEventCallback([this](Event& e) { onEvent(e); });
    }

    void Application::run()
    {
        while (m_running) {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (auto& layer : m_layerStack) {
                layer->onUpdate();
            }

            m_window->onUpdate();
        }
    }

    void Application::onEvent(Event& t_event)
    {
        EventDispatcher dispatcher(t_event);
        dispatcher.dispatch<WindowCloseEvent>(
            [this](WindowCloseEvent& e) { return onWindowClose(e); }
        );

        for (auto it = m_layerStack.end(); it != m_layerStack.begin();) {
            (*--it)->onEvent(t_event);
            if (t_event.handled) {
                break;
            }
        }
    }

    void Application::pushLayer(std::unique_ptr<Layer> t_layer)
    {
        m_layerStack.pushLayer(std::move(t_layer));
    }

    void Application::pushOverlay(std::unique_ptr<Layer> t_layer)
    {
        m_layerStack.pushOverlay(std::move(t_layer));
    }

    bool Application::onWindowClose(WindowCloseEvent&)
    {
        m_running = false;
        return true;
    }
}
