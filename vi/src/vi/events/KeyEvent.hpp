#pragma once

#include "Event.hpp"

#include <format>

namespace vi
{
class KeyEvent : public Event
{
public:
    inline int32_t getKeyCode() const { return m_keyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

protected:
    KeyEvent(int32_t keycode)
        : m_keyCode(keycode) {}
    int32_t m_keyCode;
};

class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent(int32_t keycode, int32_t repeatCount)
        : KeyEvent(keycode), m_repeatCount(repeatCount) {}

    inline int32_t getRepeatCount() const { return m_repeatCount; }

    std::string toString() const override
    {
        return std::format("KeyPressedEvent: {}, {} repeats", m_keyCode, m_repeatCount);
    }
    EVENT_CLASS_TYPE(KeyPressed)
private:
    int32_t m_repeatCount;
};

class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent(int keycode)
        : KeyEvent(keycode) {}

    std::string toString() const override
    {
        return std::format("KeyReleasedEvent: {}", m_keyCode);
    }

    EVENT_CLASS_TYPE(KeyReleased)
};

}