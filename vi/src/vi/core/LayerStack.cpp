#include <algorithm>

#include "vi/core/LayerStack.hpp"

namespace vi
{
LayerStack::LayerStack()
{
    m_LayerInsert = m_layers.begin();
}

LayerStack::~LayerStack()
{
    for (const auto* layer : m_layers) {
        delete layer;
    }
}

void LayerStack::pushLayer(Layer* layer)
{
    m_LayerInsert = m_layers.emplace(m_LayerInsert, layer);
}

void LayerStack::pushOverlay(Layer* layer)
{
    m_layers.emplace_back(layer);
}

void LayerStack::popLayer(const Layer* layer)
{
    if (const auto it = std::ranges::find(m_layers, layer); it != m_layers.end()) {
        m_layers.erase(it);
        --m_LayerInsert;
    }
}

void LayerStack::popOverlay(const Layer* layer)
{
    if (const auto it = std::ranges::find(m_layers, layer); it != m_layers.end()) {
        m_layers.erase(it);
    }
}
}
