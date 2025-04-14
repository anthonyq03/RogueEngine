#include "Pipeline.hpp"

//std
#include <fstream>
#include <iostream>

namespace Engine
{
    Pipeline::Pipeline(EngineDevice& device, const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo): engineDevice{device}
    {
        createGraphicsPipeline(vertFilePath, fragFilePath, configInfo);
    }

    Pipeline::~Pipeline()
    {
        // Cleanup code for the pipeline (if needed)
    }

    std::vector<char> Pipeline::readFile(const std::string& filePath)
    {
        std::ifstream file(filePath, std::ios::ate | std::ios::binary);

        if (!file.is_open())
        {
            throw std::runtime_error("failed to open file: " + filePath);
        }
        size_t fileSize = static_cast<size_t>(file.tellg());
        std::vector<char> buffer(fileSize);
        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();
        return buffer;
    }

    void Pipeline::createGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo)
    {
        auto vertCode = readFile(vertFilePath);
        auto fragCode = readFile(fragFilePath);

        std::cout << "Vertex shader code size: " << vertCode.size() << std::endl;
        std::cout << "Fragment shader code size: " << fragCode.size() << std::endl;
    }

    void Pipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule){
        VkShaderModuleCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        if (vkCreateShaderModule(engineDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create shader module!");
        }
    };

    PipelineConfigInfo Pipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height)
    {
        PipelineConfigInfo configInfo{};
        // configInfo.viewport.x = 0.0f;
        // configInfo.viewport.y = 0.0f;
        // configInfo.viewport.width = static_cast<float>(width);
        // configInfo.viewport.height = static_cast<float>(height);
        // configInfo.scissor.offset = {0, 0};
        // configInfo.scissor.extent = {width, height};
        return configInfo;
    }
} // namespace Engine