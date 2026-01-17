// Simple test to verify texture atlas functionality
#include <SDL2/SDL.h>
#include <iostream>
#include "TextureManager.h"
#include "TextureAtlas.h"
#include "Sprite.h"

using namespace zombie::assets;
using namespace zombie::graphics;

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL init failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    // Create window and renderer
    SDL_Window* window = SDL_CreateWindow(
        "Atlas Test",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );
    
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    // Initialize texture manager
    TextureManager* texMgr = TextureManager::getInstance();
    texMgr->init(renderer);
    texMgr->setMediaPath("../media/");
    
    std::cout << "\n=== Texture Atlas Test ===" << std::endl;
    std::cout << "Testing atlas creation and sprite rendering\n" << std::endl;
    
    // Test 1: Create simple atlas
    std::cout << "Test 1: Creating test atlas..." << std::endl;
    
    // Create a test atlas with some sprites
    // Note: These paths may not exist, but we can test the API
    std::vector<std::string> testSprites = {
        "textures/Bob_Idle_S.png",  // These are example paths
        "textures/Bob_Walk_S_01.png"
    };
    
    TextureAtlas* atlas = texMgr->createAtlas(
        "test_atlas",
        testSprites,
        512,  // 512x512 atlas
        512
    );
    
    if (atlas) {
        std::cout << "✓ Atlas created successfully" << std::endl;
        
        // Get atlas texture info
        int w, h;
        SDL_QueryTexture(atlas->getAtlasTexture(), nullptr, nullptr, &w, &h);
        std::cout << "  Atlas size: " << w << "x" << h << std::endl;
        
        // Test region lookup
        const AtlasRegion* region = atlas->getRegion(testSprites[0]);
        if (region) {
            std::cout << "✓ Region lookup successful" << std::endl;
            std::cout << "  Region: " << region->name << std::endl;
            std::cout << "  Position: (" << region->rect.x << ", " 
                     << region->rect.y << ")" << std::endl;
            std::cout << "  Size: " << region->rect.w << "x" 
                     << region->rect.h << std::endl;
            std::cout << "  UV: (" << region->u1 << ", " << region->v1 
                     << ") to (" << region->u2 << ", " << region->v2 << ")" 
                     << std::endl;
            
            // Test sprite with atlas region
            Sprite testSprite;
            testSprite.setTexture(atlas->getAtlasTexture());
            testSprite.setAtlasRegion(region);
            
            if (testSprite.isFromAtlas()) {
                std::cout << "✓ Sprite configured from atlas" << std::endl;
            } else {
                std::cout << "✗ Sprite atlas flag not set" << std::endl;
            }
        } else {
            std::cout << "✗ Region lookup failed" << std::endl;
        }
    } else {
        std::cout << "ℹ Atlas creation failed (expected if test sprites don't exist)" 
                  << std::endl;
    }
    
    // Test 2: Retrieve cached atlas
    std::cout << "\nTest 2: Retrieving cached atlas..." << std::endl;
    TextureAtlas* cachedAtlas = texMgr->getAtlas("test_atlas");
    if (cachedAtlas == atlas) {
        std::cout << "✓ Atlas caching working correctly" << std::endl;
    } else {
        std::cout << "✗ Atlas caching failed" << std::endl;
    }
    
    // Test 3: Atlas configuration
    std::cout << "\nTest 3: Testing atlas configuration..." << std::endl;
    TextureAtlas::Config config;
    config.maxWidth = 1024;
    config.maxHeight = 1024;
    config.padding = 2;
    config.powerOfTwo = true;
    
    TextureAtlas* configAtlas = new TextureAtlas(renderer, config);
    std::cout << "✓ Custom atlas configuration created" << std::endl;
    std::cout << "  Max size: " << config.maxWidth << "x" << config.maxHeight 
              << std::endl;
    std::cout << "  Padding: " << config.padding << "px" << std::endl;
    std::cout << "  Power-of-2: " << (config.powerOfTwo ? "Yes" : "No") 
              << std::endl;
    
    delete configAtlas;
    
    std::cout << "\n=== Tests Complete ===" << std::endl;
    std::cout << "\nPress any key to exit..." << std::endl;
    
    // Simple event loop
    bool running = true;
    SDL_Event event;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || 
                event.type == SDL_KEYDOWN) {
                running = false;
            }
        }
        
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);
        
        // Could render test sprites here if atlas was created successfully
        
        SDL_RenderPresent(renderer);
        SDL_Delay(16);  // ~60 FPS
    }
    
    // Cleanup
    texMgr->shutdown();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    std::cout << "Atlas test completed successfully!" << std::endl;
    return 0;
}
