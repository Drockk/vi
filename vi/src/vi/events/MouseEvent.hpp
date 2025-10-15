#include "Event.hpp"

#include <format>

namespace vi
{
class MouseMovedEvent : public Event
{
public:
    MouseMovedEvent(float x, float y)
        : m_mouseX(x), m_mouseY(y) {}

    inline float getX() const { return m_mouseX; }
    inline float getY() const { return m_mouseY; }

    std::string toString() const override
    {
        return std::format("MouseMovedEvent: {}, {}", m_mouseX, m_mouseY);
    }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
    float m_mouseX, m_mouseY;
};

class MouseScrolledEvent : public Event
{
public:
    MouseScrolledEvent(float xOffset, float yOffset)
        : m_xOffset(xOffset), m_yOffset(yOffset) {}

    inline float getXOffset() const { return m_xOffset; }
    inline float getYOffset() const { return m_yOffset; }

    std::string toString() const override
    {
        return std::format("MouseScrolledEvent: {}, {}", getXOffset(), getYOffset());
    }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
    float m_xOffset, m_yOffset;
};

class MouseButtonEvent : public Event
{
public:
    inline int32_t getMouseButton() const { return m_button; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
protected:
    MouseButtonEvent(int button)
        : m_button(button) {}

    int32_t m_button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
    MouseButtonPressedEvent(int32_t button)
        : MouseButtonEvent(button) {}

    std::string toString() const override
    {
        return std::format("MouseButtonPressedEvent: {}", m_button);
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
    MouseButtonReleasedEvent(int32_t button)
        : MouseButtonEvent(button) {}

    std::string toString() const override
    {
        return std::format("MouseButtonReleasedEvent: {}", m_button);
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
};
}
