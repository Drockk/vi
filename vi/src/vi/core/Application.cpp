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
            m_window->onUpdate();
        }
    }

    void Application::onEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(
            [this](WindowCloseEvent& e) { return onWindowClose(e); }
        );

        VI_CORE_TRACE("{0}", e);
    }

    bool Application::onWindowClose(WindowCloseEvent& e)
    {
        m_running = false;
        return true;
    }
}
