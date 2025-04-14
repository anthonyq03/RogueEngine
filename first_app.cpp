#include "first_app.hpp"

namespace Engine
{

    void FirstApp::run()
    {
        while (!window.shouldClose())
        {
            glfwPollEvents();
        }
    }

} // namespace WindowHandler