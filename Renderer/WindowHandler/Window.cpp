#include "window.hpp"
#include <stdexcept>

namespace Renderer
{
    Window::Window(int width, int height, const std::string title) : width(width), height(height), title(title)
    {
        initWindow();
    }
    Window::Window::~Window()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::initWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
        }
    }
    
    bool Window::shouldClose()
    {
        return glfwWindowShouldClose(window);
    }

    void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface)
    {
        if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create window surface!");
        }
    }
} // namespace windowHandler
