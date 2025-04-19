cmake_minimum_required(VERSION 3.15)
project(RogueEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Vulkan
find_package(Vulkan REQUIRED)

# GLFW via FetchContent
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        latest
)
FetchContent_MakeAvailable(glfw)

# Add engine source files
file(GLOB_RECURSE ENGINE_SRC
    Renderer/*.cpp
    Renderer/*.hpp
)
add_custom_target(
    RunCompileScript ALL
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/compile.bat
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
add_library(RogueEngine STATIC ${ENGINE_SRC})

add_dependencies(RogueEngine RunCompileScript)


target_include_directories(RogueEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${glfw_SOURCE_DIR}/include
)

target_link_libraries(RogueEngine PUBLIC glfw Vulkan::Vulkan)
