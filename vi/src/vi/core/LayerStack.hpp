#pragma once

#include "vi/core/Layer.hpp"

#include <vector>

namespace vi
{
class LayerStack
{
public:
    LayerStack();
    ~LayerStack();

    void pushLayer(Layer* layer);
    void pushOverlay(Layer* layer);
    void popLayer(const Layer* layer);
    void popOverlay(const Layer* layer);

    std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
    std::vector<Layer*>::iterator end() { return m_layers.end(); }

private:
    std::vector<Layer*> m_layers;
    std::vector<Layer*>::iterator m_LayerInsert;
};
}
