#include "first_app.hpp"
#include <stdexcept>
#include <array>

namespace Engine
{

    FirstApp::FirstApp()
    {
        loadAnimatingTriangle(currentDepth); // Load initial model
        createPipelineLayout();
        createPipeline();
        createCommandBuffers();
    }
    FirstApp::~FirstApp()
    {
        vkDestroyPipelineLayout(engineDevice.device(), pipelineLayout, nullptr);
    }

    void FirstApp::run()
    {
        float startTime = glfwGetTime();
        float lastUpdateTime = startTime;



        while (!window.shouldClose())
        {
            glfwPollEvents();
            float currentTime = glfwGetTime();
            if (currentTime - lastUpdateTime >= 1.0f) {
                if(currentDepth > maxDepth){
                    currentDepth = 0;
                }
                vkDeviceWaitIdle(engineDevice.device());     // ensure GPU is idle
                loadAnimatingTriangle(currentDepth);                    // recreate model + buffer
                createCommandBuffers();                      // re-record with new buffer
                currentDepth++;
                lastUpdateTime = currentTime;
            }
            drawFrame();
        }

        vkDeviceWaitIdle(engineDevice.device());
    }

    void FirstApp::generateSierpinskiTriangle(
        std::vector<Model::Vertex>& vertices,
        Model::Vertex a,
        Model::Vertex b,
        Model::Vertex c,
        int depth)
        {

            
            Model::Vertex midAB = Model::Vertex{(a.position + b.position) / 2.0f,(a.color + b.color) / 2.0f};
            Model::Vertex midBC = Model::Vertex{(b.position + c.position) / 2.0f, (b.color + c.color) / 2.0f};
            Model::Vertex midCA = Model::Vertex{(c.position + a.position) / 2.0f, (c.color + a.color) / 2.0f};
            if (depth > 0) {
                generateSierpinskiTriangle(vertices, a, midAB, midCA, depth - 1);
                generateSierpinskiTriangle(vertices, b, midAB, midBC, depth - 1);
                generateSierpinskiTriangle(vertices, c, midBC, midCA, depth - 1);
            }
            else {
                vertices.push_back(a);
                vertices.push_back(b);
                vertices.push_back(c);
            }



    }

    void FirstApp::loadAnimatingTriangle(int depth){
        vkDeviceWaitIdle(engineDevice.device());  // Ensure GPU isn't using the old buffer

        int triangleCount = pow(3, depth);
        std::vector<Model::Vertex> vertices;
        vertices.reserve(triangleCount * 3);
    
        generateSierpinskiTriangle(
            vertices,
            Model::Vertex{glm::vec2{0.0f, -1.0f},{1.0f, 0.0f, 0.0f}},
            Model::Vertex{glm::vec2{-1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
            Model::Vertex{glm::vec2{1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
            depth
        );
    
        model = std::make_unique<Model>(engineDevice, vertices);

    }


    void FirstApp::loadModels()
    {
        int depth = 6;
        int triangleCount = pow(3, depth);
        std::vector<Model::Vertex> vertices;
        vertices.reserve(triangleCount * 3);
    
        generateSierpinskiTriangle(
            vertices,
            Model::Vertex{glm::vec2{0.0f, -1.0f}},
            Model::Vertex{glm::vec2{-1.0f, 1.0f}},
            Model::Vertex{glm::vec2{1.0f, 1.0f}},
            depth
        );
    
        model = std::make_unique<Model>(engineDevice, vertices);
    }

    void FirstApp::createPipelineLayout()
    {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
        pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
        pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

        if (vkCreatePipelineLayout(engineDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create pipeline layout!");
        }
    } 

    void FirstApp::createPipeline(){

        PipelineConfigInfo pipelineConfig{};
        Pipeline::defaultPipelineConfigInfo(pipelineConfig, swapChain.width(), swapChain.height()); 

        pipelineConfig.renderPass = swapChain.getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;
        pipeline = std::make_unique<Pipeline>(engineDevice,
            "../../compiledShaders/simple_shader_vert.spv",
            "../../compiledShaders/simple_shader_frag.spv",
            pipelineConfig);
        
    }

    void FirstApp::createCommandBuffers(){
        commandBuffers.resize(swapChain.imageCount());

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = engineDevice.getCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

        if (vkAllocateCommandBuffers(engineDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to allocate command buffers!");
        }

        for( int i = 0; i<commandBuffers.size(); i++){
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to begin recording command buffer!");
            }

            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = swapChain.getRenderPass();
            renderPassInfo.framebuffer = swapChain.getFrameBuffer(i);

            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = swapChain.getSwapChainExtent();

            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = {{0.1f, 0.1f, 0.1f, 1.0f}};
            clearValues[1].depthStencil = {1.0f, 0};
            
            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            pipeline->bind(commandBuffers[i]);
            model->bind(commandBuffers[i]);
            model->draw(commandBuffers[i]);
            vkCmdEndRenderPass(commandBuffers[i]);

            if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to record command buffer!");
            }
        }
    };
    void FirstApp::drawFrame(){
        uint32_t imageIndex;
        auto result = swapChain.acquireNextImage(&imageIndex);

        if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        result = swapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);

        if (result != VK_SUCCESS){
            throw std::runtime_error("failed to present swap chain image!");
        }
    };

} // namespace WindowHandler