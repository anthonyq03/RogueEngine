#pragma once

#include "Engine/WindowHandler/window.hpp"
#include "Engine/Pipeline/Pipeline.hpp"
#include "Engine/EngineDevice/EngineDevice.hpp"
#include "Engine/SwapChain/SwapChain.hpp"

//std
#include <memory>
#include <vector>

namespace Engine{
    class FirstApp
    {
        public:
            static constexpr int WIDTH = 800;
            static constexpr int HEIGHT = 600;

            FirstApp();
            ~FirstApp();
            FirstApp(const FirstApp&) = delete;
            FirstApp& operator=(const FirstApp&) = delete;


            void run();
        private:
            void createPipelineLayout();
            void createPipeline();
            void createCommandBuffers();
            void drawFrame();

            Window window{WIDTH, HEIGHT, "First App"};
            EngineDevice engineDevice{window};
            SwapChain swapChain{engineDevice, window.getExtent()};
            //Pipeline pipeline{engineDevice, "../../compiledShaders/simple_shader_vert.spv", "../../compiledShaders/simple_shader_frag.spv", Pipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
            std::unique_ptr<Pipeline> pipeline;

            VkPipelineLayout pipelineLayout;
            std::vector<VkCommandBuffer> commandBuffers;
        };
}