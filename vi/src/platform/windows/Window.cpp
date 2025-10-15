#include "platform/windows/Window.hpp"

#include "vi/core/Log.hpp"
#include <GLFW/glfw3.h>
#include "Window.hpp"

namespace
{
    static bool s_GLFWInitialized{ false };
}

namespace windows
{
    Window::Window(const vi::WindowProps& props)
    {
        init(props);
    }

    Window::~Window()
    {
        shutdown();
    }

    void Window::init(const vi::WindowProps& props)
    {
        m_data.title = props.title;
        m_data.width = props.width;
        m_data.height = props.height;

        VI_CORE_INFO("Creating window {}, ({}, {})", props.title, props.width, props.height);

        if (!s_GLFWInitialized) {
            if (glfwInit() == GLFW_FALSE) {
                throw std::runtime_error("Could not initialize GLFW!");
            }

            s_GLFWInitialized = true;
        }

        m_window = glfwCreateWindow(
            static_cast<int>(props.width),
            static_cast<int>(props.height),
            m_data.title.c_str(),
            nullptr, nullptr
        );

        glfwMakeContextCurrent(m_window);
        glfwSetWindowUserPointer(m_window, &m_data);
        setVSync(true);
    }

    void Window::shutdown()
    {
        if (m_window) {
            glfwDestroyWindow(m_window);
        }

        if (s_GLFWInitialized) {
            glfwTerminate();
            s_GLFWInitialized = false;
        }
    }

    void Window::onUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    uint32_t Window::getWidth() const
    {
        return m_data.width;
    }

    uint32_t Window::getHeight() const
    {
        return m_data.height;
    }

    void Window::setVSync(bool enabled)
    {
        if (enabled) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }
        m_data.vSync = enabled;
    }

    bool Window::isVSync() const
    {
        return m_data.vSync;
    }

    void Window::setEventCallback(const EventCallbackFn& callback)
    {
        m_data.eventCallback = callback;
    }
}
