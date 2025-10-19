#include "platform/windows/Window.hpp"
#include "vi/events/ApplicationEvent.hpp"
#include "vi/events/KeyEvent.hpp"
#include "vi/events/MouseEvent.hpp"

#include "vi/core/Log.hpp"
#include <GLFW/glfw3.h>

namespace
{
    bool s_glfw_initialized{ false };

    void glfw_error_callback(int t_error, const char* t_description)
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

        if (!s_glfw_initialized) {
            if (glfwInit() == GLFW_FALSE) {
                throw std::runtime_error("Could not initialize GLFW!");
            }

            glfwSetErrorCallback(glfw_error_callback);
            s_glfw_initialized = true;
        }

        m_window.reset(glfwCreateWindow(
            static_cast<int>(t_props.width),
            static_cast<int>(t_props.height),
            m_data.title.c_str(),
            nullptr, nullptr
        ));

        glfwMakeContextCurrent(m_window.get());
        glfwSetWindowUserPointer(m_window.get(), &m_data);
        setVSync(true);

        glfwSetWindowSizeCallback(m_window.get(), [](GLFWwindow* t_window, const int t_width, const int t_height) {
            auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(t_window));
            data.width = t_width;
            data.height = t_height;

            vi::WindowResizeEvent event(t_width, t_height);
            data.eventCallback(event);
        });

        glfwSetWindowCloseCallback(m_window.get(), [](GLFWwindow* t_window) {
            const auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(t_window));
            vi::WindowCloseEvent event;
            data.eventCallback(event);
        });

        glfwSetKeyCallback(m_window.get(), [](GLFWwindow* t_window, const int t_key, int t_scancode, int t_action, int t_mods) {
            const auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(t_window));

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
            default:
                VI_CORE_ERROR("Unknown GLFW action {}", t_action);
                break;
            }
        });

        glfwSetMouseButtonCallback(m_window.get(), [](GLFWwindow* t_window, const int t_button, int t_action, int t_mods) {
            const auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(t_window));

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
            default:
                VI_CORE_ERROR("Unknown GLFW action {}", t_action);
                break;
            }
        });

        glfwSetScrollCallback(m_window.get(), [](GLFWwindow* t_window, const double t_x_offset, const double t_y_offset) {
            const auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(t_window));

            vi::MouseScrolledEvent event(static_cast<float>(t_x_offset), static_cast<float>(t_y_offset));
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(m_window.get(), [](GLFWwindow* t_window, const double t_x_pos, const double t_y_pos) {
            const auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(t_window));

            vi::MouseMovedEvent event(static_cast<float>(t_x_pos), static_cast<float>(t_y_pos));
            data.eventCallback(event);
        });
    }

    void Window::shutdown()
    {
        m_window.reset();

        if (s_glfw_initialized) {
            glfwTerminate();
            s_glfw_initialized = false;
        }
    }

    void Window::onUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_window.get());
    }

    uint32_t Window::getWidth() const
    {
        return m_data.width;
    }

    uint32_t Window::getHeight() const
    {
        return m_data.height;
    }

    void Window::setVSync(const bool t_enabled)
    {
        if (t_enabled) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }
        m_data.vSync = t_enabled;
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
