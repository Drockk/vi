#include <algorithm>

#include "vi/core/LayerStack.hpp"

namespace vi
{
void LayerStack::pushLayer(std::unique_ptr<Layer> layer)
{
    m_LayerInsert = m_layers.emplace(m_LayerInsert, std::move(layer));
}

void LayerStack::pushOverlay(std::unique_ptr<Layer> layer)
{
    m_layers.emplace_back(std::move(layer));
}

void LayerStack::popLayer(const std::unique_ptr<Layer>& layer)
{
    if (const auto it = std::ranges::find(m_layers, layer); it != m_layers.end()) {
        m_layers.erase(it);
        --m_LayerInsert;
    }
}

void LayerStack::popOverlay(const std::unique_ptr<Layer>& layer)
{
    if (const auto it = std::ranges::find(m_layers, layer); it != m_layers.end()) {
        m_layers.erase(it);
    }
}
}
