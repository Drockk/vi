#include <vi.hpp>

#include <memory>

namespace sandbox
{
class SandboxApp: public vi::Application
{
public:
    SandboxApp() = default;
    ~SandboxApp() override = default;
};
}

std::unique_ptr<vi::Application> vi::createApplication()
{
    return std::make_unique<sandbox::SandboxApp>();
}