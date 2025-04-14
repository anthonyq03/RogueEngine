#pragma once

#include "Engine/WindowHandler/window.hpp"
#include "Engine/Pipeline/Pipeline.hpp"
#include "Engine/EngineDevice/EngineDevice.hpp"

namespace Engine{
    class FirstApp
    {
        public:
            static constexpr int WIDTH = 800;
            static constexpr int HEIGHT = 600;
            void run();
        private:
            Window window{WIDTH, HEIGHT, "First App"};
            EngineDevice engineDevice{window};
            Pipeline pipeline{engineDevice, "../../compiledShaders/simple_shader_vert.spv", "../../compiledShaders/simple_shader_frag.spv", Pipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
    };
}