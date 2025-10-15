#pragma once

#include "vi/core/Window.hpp"

struct GLFWwindow;

namespace windows
{
class Window final : public vi::Window
{
public:
    Window(const vi::WindowProps& props);
    ~Window() override;

    void onUpdate() override;
    uint32_t getWidth() const override;
    uint32_t getHeight() const override;

    void setEventCallback(const EventCallbackFn& callback) override;
    void setVSync(bool enabled) override;
    bool isVSync() const override;

private:
    void init(const vi::WindowProps& props);
    void shutdown();

    GLFWwindow* m_window{nullptr};

    struct WindowData
    {
        std::string title;
        uint32_t width;
        uint32_t height;
        bool vSync;

        EventCallbackFn eventCallback;
    };

    WindowData m_data;
};
}