cmake_minimum_required(VERSION 3.15)
project(Triangle)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Vulkan
find_package(Vulkan REQUIRED)

# Use GLFW via FetchContent
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        latest
)
FetchContent_MakeAvailable(glfw)

#Compile shaders
add_custom_target(
    RunCompileScript ALL
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/compile.bat
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(VulkanApp
main.cpp
Engine/WindowHandler/Window.cpp
Engine/Pipeline/Pipeline.cpp
first_app.cpp
Engine/EngineDevice/EngineDevice.cpp
Engine/SwapChain/SwapChain.cpp
)

add_dependencies(VulkanApp RunCompileScript)
target_link_libraries(VulkanApp PRIVATE glfw Vulkan::Vulkan)

target_include_directories(VulkanApp PRIVATE
    ${glfw_SOURCE_DIR}/include
)
