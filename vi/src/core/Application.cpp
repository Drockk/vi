#include "core/Application.hpp"
#include "events/ApplicationEvent.hpp"
#include "core/Log.hpp"


namespace vi
{
    void Application::run()
    {
        WindowResizeEvent e(1280, 720);
        if (e.isInCategory(EventCategoryApplication)) {
            VI_TRACE(e.toString());
        }

        if (e.isInCategory(EventCategoryInput)) {
            VI_TRACE(e.toString());
        }

        while (true);
    }
}
