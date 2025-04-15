#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace Engine
{
    class Window
    {
    public:
        Window(int width, int height, const std::string title);
        ~Window();
        bool shouldClose();
        VkExtent2D getExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }

        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;


    private:
        void initWindow();
        GLFWwindow *window;
        int width;
        int height;
        const std::string title;
    };
} // namespace windowHandler