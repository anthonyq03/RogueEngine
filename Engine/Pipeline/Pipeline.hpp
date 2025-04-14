#pragma once

#include "../EngineDevice/EngineDevice.hpp"

#include <string>
#include <vector>

namespace Engine
{
    struct PipelineConfigInfo
    {

    };

    class Pipeline
    {
    public:
        Pipeline(EngineDevice &device, const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo);
        ~Pipeline();

        Pipeline(const Pipeline &) = delete;
        void operator=(const Pipeline &) = delete;

        static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);


    private:
        static std::vector<char> readFile(const std::string& filePath);

        void createGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo);

        void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

        EngineDevice &engineDevice;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;
    };
} // namespace Engine