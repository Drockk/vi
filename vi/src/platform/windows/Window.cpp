#include "platform/windows/Window.hpp"
#include "vi/events/ApplicationEvent.hpp"
#include "vi/events/KeyEvent.hpp"
#include "vi/events/MouseEvent.hpp"

#include "vi/core/Log.hpp"
#include <GLFW/glfw3.h>
#include "Window.hpp"

namespace
{
    static bool s_GLFWInitialized{ false };

    static void GLFWErrorCallback(int t_error, const char* t_description)
    {
        VI_CORE_ERROR("GLFW Error ({}): {}", t_error, t_description);
    }
}

namespace windows
{
    Window::Window(const vi::WindowProps& t_props)
    {
        init(t_props);
    }

    Window::~Window()
    {
        shutdown();
    }

    void Window::init(const vi::WindowProps& t_props)
    {
        m_data.title = t_props.title;
        m_data.width = t_props.width;
        m_data.height = t_props.height;

        VI_CORE_INFO("Creating window {}, ({}, {})", t_props.title, t_props.width, t_props.height);

        if (!s_GLFWInitialized) {
            if (glfwInit() == GLFW_FALSE) {
                throw std::runtime_error("Could not initialize GLFW!");
            }

            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }

        m_window = glfwCreateWindow(
            static_cast<int>(t_props.width),
            static_cast<int>(t_props.height),
            m_data.title.c_str(),
            nullptr, nullptr
        );

        glfwMakeContextCurrent(m_window);
        glfwSetWindowUserPointer(m_window, &m_data);
        setVSync(true);

        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* t_window, int t_width, int t_height)
        {
            auto& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(t_window));
            data.width = t_width;
            data.height = t_height;

            vi::WindowResizeEvent event(t_width, t_height);
            data.eventCallback(event);
        });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* t_window)
        {
            auto& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(t_window));
            vi::WindowCloseEvent event;
            data.eventCallback(event);
        });

        glfwSetKeyCallback(m_window, [](GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods)
        {
            auto& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(t_window));

            switch (t_action)
            {
            case GLFW_PRESS:
            {
                vi::KeyPressedEvent event(t_key, 0);
                data.eventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                vi::KeyReleasedEvent event(t_key);
                data.eventCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                vi::KeyPressedEvent event(t_key, 1);
                data.eventCallback(event);
                break;
            }
            }
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* t_window, int t_button, int t_action, int t_mods)
        {
            auto& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(t_window));

            switch (t_action)
            {
            case GLFW_PRESS:
            {
                vi::MouseButtonPressedEvent event(t_button);
                data.eventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                vi::MouseButtonReleasedEvent event(t_button);
                data.eventCallback(event);
                break;
            }
            }
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow* t_window, double t_xOffset, double t_yOffset)
        {
            auto& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(t_window));

            vi::MouseScrolledEvent event(static_cast<float>(t_xOffset), static_cast<float>(t_yOffset));
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* t_window, double t_xPos, double t_yPos)
        {
            auto& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(t_window));

            vi::MouseMovedEvent event(static_cast<float>(t_xPos), static_cast<float>(t_yPos));
            data.eventCallback(event);
        });
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

    void Window::setEventCallback(const EventCallbackFn& t_callback)
    {
        m_data.eventCallback = t_callback;
    }
}
