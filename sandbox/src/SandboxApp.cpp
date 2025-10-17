#include <vi.hpp>

#include <memory>
#include <string>
using namespace std::literals;

class ExampleLayer : public vi::Layer
{
public:
    ExampleLayer() : Layer("Example"sv) {}

    void onUpdate() override
    {
        VI_INFO("ExampleLayer::onUpdate");
    }
    void onEvent(vi::Event& event) override
    {
        VI_TRACE("{}", event);
    }
};

namespace sandbox
{
class SandboxApp: public vi::Application
{
public:
    SandboxApp()
    {
        pushLayer(new ExampleLayer);
    }

    ~SandboxApp() override = default;
};
}

std::unique_ptr<vi::Application> vi::createApplication()
{
    return std::make_unique<sandbox::SandboxApp>();
}