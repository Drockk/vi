#pragma once

#include "vi/core/Layer.hpp"

#include <vector>

namespace vi
{
class LayerStack
{
public:
    void pushLayer(std::unique_ptr<Layer> layer);
    void pushOverlay(std::unique_ptr<Layer> layer);
    void popLayer(const std::unique_ptr<Layer>& layer);
    void popOverlay(const std::unique_ptr<Layer>& layer);

    auto begin() { return m_layers.begin(); }
    auto end() { return m_layers.end(); }

private:
    std::vector<std::unique_ptr<Layer>> m_layers;
    std::vector<std::unique_ptr<Layer>>::iterator m_LayerInsert = m_layers.begin();
};
}
