#include "first_app.hpp"

//std
#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main()
{
    Engine::FirstApp app{};

    try{
        app.run();

    }catch (const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
} // namespace WindowHandler