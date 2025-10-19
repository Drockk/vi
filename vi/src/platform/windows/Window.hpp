#pragma once

#include "vi/core/Window.hpp"
#include <memory>
#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace windows
{
class Window final : public vi::Window
{
public:
    Window(const vi::WindowProps& t_props);
    ~Window() override;

    void onUpdate() override;
    uint32_t getWidth() const override;
    uint32_t getHeight() const override;

    void setEventCallback(const EventCallbackFn& t_callback) override;
    void setVSync(bool t_enabled) override;
    bool isVSync() const override;

private:
    void init(const vi::WindowProps& t_props);
    void shutdown();

    struct GLFWwindowDeleter
    {
        void operator()(GLFWwindow* window) const
        {
            if (window) {
                glfwDestroyWindow(window);
            }
        }
    };

    std::unique_ptr<GLFWwindow, GLFWwindowDeleter> m_window{nullptr};

    struct WindowData
    {
        std::string title{};
        uint32_t width{};
        uint32_t height{};
        bool vSync{};

        EventCallbackFn eventCallback;
    };

    WindowData m_data;
};
}