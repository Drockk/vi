#pragma once

#include <string>
#include <functional>
#include <ostream>
#include <spdlog/fmt/fmt.h>

#define BIT(x) (1 << x)

namespace vi
{
enum class EventType
{
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyReleased,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};


enum EventCategory
{
    None = 0,
    EventCategoryApplication    = BIT(0),
    EventCategoryInput          = BIT(1),
    EventCategoryKeyboard       = BIT(2),
    EventCategoryMouse          = BIT(3),
    EventCategoryMouseButton    = BIT(4)
};

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::##type; }       \
                                EventType getEventType() const override { return getStaticType(); } \
                                const char* getName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) int getCategoryFlags() const override { return category; }

class Event
{
friend class EventDispatcher;

public:
    bool handled{ false };

    virtual EventType getEventType() const = 0;
    virtual const char* getName() const = 0;
    virtual int getCategoryFlags() const = 0;
    virtual std::string toString() const { return getName(); }

    bool isInCategory(const EventCategory category) const
    {
        return getCategoryFlags() & category;
    }
};

class EventDispatcher
{
    template<typename T>
    using EventFn = std::function<bool(T&)>;

public:
    EventDispatcher(Event& event)
    : m_event(event)
    {
    }

    template<typename T>
    bool dispatch(EventFn<T> func)
    {
        if (m_event.getEventType() == T::getStaticType()) {
            m_event.handled = func(*static_cast<T*>(&m_event));
            return true;
        }

        return false;
    }

private:
    Event& m_event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
    return os << e.toString();
}
}

// Formatter for fmt/spdlog
template <>
struct fmt::formatter<vi::Event> : fmt::formatter<std::string>
{
    auto format(const vi::Event& e, format_context& ctx) const
    {
        return fmt::formatter<std::string>::format(e.toString(), ctx);
    }
};
