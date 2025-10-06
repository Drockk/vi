#pragma once

#include <memory>

namespace vi
{
class Application
{
public:
    virtual ~Application() = default;

    void run();
};

// To be defined in CLIENT
std::unique_ptr<Application> createApplication();
}
