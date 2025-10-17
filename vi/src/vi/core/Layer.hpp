#pragma once
#include "vi/events/Event.hpp"

namespace vi
{
class Layer
{
public:
    Layer(std::string_view t_name = "Layer");
    virtual ~Layer() = default;

    virtual void onAttach() {}
    virtual void onDetach() {}
    virtual void onUpdate() {}
    virtual void onEvent(Event& t_event) {}

    [[nodiscard]] std::string_view getName() const { return m_debugName; }
private:
    std::string m_debugName;
};
}
