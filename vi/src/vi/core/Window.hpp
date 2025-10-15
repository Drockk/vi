#pragma once

#include "vi/events/Event.hpp"

#include <functional>
#include <memory>
#include <string>

namespace vi
{
struct WindowProps
{
    std::string title = "vi";
    uint32_t width = 1280;
    uint32_t height = 720;
    WindowProps(std::string_view t_title = "vi", uint32_t t_width = 1280, uint32_t t_height = 720)
        : title(t_title), width(t_width), height(t_height)
    {
    }
};

class Window
{
public:
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~Window() = default;

    virtual void onUpdate() = 0;
    virtual uint32_t getWidth() const = 0;
    virtual uint32_t getHeight() const = 0;

    virtual void setEventCallback(const EventCallbackFn& callback) = 0;
    virtual void setVSync(bool enabled) = 0;
    virtual bool isVSync() const = 0;

    static std::unique_ptr<Window> create(const WindowProps& props = WindowProps());
};
}