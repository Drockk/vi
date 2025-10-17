#include "vi/core/Window.hpp"
#include "platform/windows/Window.hpp"

namespace vi
{
std::unique_ptr<Window> Window::create(const WindowProps &props)
{
    return std::make_unique<windows::Window>(props);
}
}
