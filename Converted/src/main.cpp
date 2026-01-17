#include "GameWindow.h"
#include "Core.h"
#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    std::cout << "=== Project Zomboid C++ Port ===" << std::endl;
    std::cout << "Target Platform: Nintendo Switch (SDL2)" << std::endl;
    std::cout << "Build: " << __DATE__ << " " << __TIME__ << std::endl;
    std::cout << "====================================" << std::endl;
    
    // Parse command line arguments
    int width = 1280;
    int height = 720;
    bool fullscreen = false;
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        
        if (arg == "-width" && i + 1 < argc) {
            width = std::atoi(argv[++i]);
        } else if (arg == "-height" && i + 1 < argc) {
            height = std::atoi(argv[++i]);
        } else if (arg == "-fullscreen") {
            fullscreen = true;
        } else if (arg == "-debug") {
            zombie::core::Core::bDebug = true;
        }
    }
    
    // Create game window
    zombie::GameWindow gameWindow;
    
    // Initialize
    if (!gameWindow.init(width, height, fullscreen)) {
        std::cerr << "Failed to initialize game" << std::endl;
        return 1;
    }
    
    // Run main game loop
    gameWindow.run();
    
    // Cleanup (handled by destructors)
    std::cout << "Game exited cleanly" << std::endl;
    
    return 0;
}
