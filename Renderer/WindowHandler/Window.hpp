#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace Renderer
{
    class Window
    {
    public:
        Window(int width, int height, const std::string title);
        ~Window();
        bool shouldClose();
        VkExtent2D getExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }
        bool wasWindowResized() { return framebufferResized; }
        void resetWindowResizedFlag() { framebufferResized = false; }

        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;


    private:
        static void framebufferResizeCallback(GLFWwindow *window, int width, int height);

        void initWindow();
        int width;
        int height;
        bool framebufferResized = false;
        
        GLFWwindow *window;
        const std::string title;
    };
} // namespace windowHandler