#include "vi/core/Application.hpp"
#include "vi/events/ApplicationEvent.hpp"
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
    }

    void Application::run()
    {
        while (m_running) {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_window->onUpdate();
        }
    }
}
