#pragma once

#include "Renderer/WindowHandler/window.hpp"
#include "Renderer/Pipeline/Pipeline.hpp"
#include "Renderer/EngineDevice/EngineDevice.hpp"
#include "Renderer/SwapChain/SwapChain.hpp"
#include "Renderer/Model/Model.hpp"

//std
#include <memory>
#include <vector>

namespace Renderer{
    class FirstApp
    {
        public:
            static constexpr int WIDTH = 1600;
            static constexpr int HEIGHT = 1200;

            FirstApp();
            ~FirstApp();
            FirstApp(const FirstApp&) = delete;
            FirstApp& operator=(const FirstApp&) = delete;


            void run();
        private:
            void loadAnimatingTriangle(int depth);
            void loadModels();
            void createPipelineLayout();
            void createPipeline();
            void createCommandBuffers();
            void drawFrame();

            static void generateSierpinskiTriangle(
                std::vector<Model::Vertex>& vertices,
                Model::Vertex a,
                Model::Vertex b,
                Model::Vertex c,
                int depth);

            Window window{WIDTH, HEIGHT, "First App"};
            EngineDevice engineDevice{window};
            SwapChain swapChain{engineDevice, window.getExtent()};
            //Pipeline pipeline{engineDevice, "../../compiledShaders/simple_shader_vert.spv", "../../compiledShaders/simple_shader_frag.spv", Pipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
            std::unique_ptr<Pipeline> pipeline;

            VkPipelineLayout pipelineLayout;
            std::vector<VkCommandBuffer> commandBuffers;
            std::unique_ptr<Model> model;



            //For triangle shit
            int currentDepth = 0;
            int maxDepth = 8; // Or whatever
            float lastUpdateTime = 0.0f;
        };
}