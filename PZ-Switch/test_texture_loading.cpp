// Example demonstrating texture loading system
#include <SDL2/SDL.h>
#include <iostream>
#include "TextureManager.h"
#include "SpriteLoader.h"
#include "IsoPlayer.h"
#include "IsoObject.h"
#include "Sprite.h"
#include "SpriteAnimation.h"

using namespace zombie::assets;
using namespace zombie::characters;
using namespace zombie::graphics;
using namespace zombie::world;

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL init failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    // Create window and renderer
    SDL_Window* window = SDL_CreateWindow(
        "Texture Loading Test",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280, 720,
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
    
    std::cout << "\n=== Texture Loading System Test ===" << std::endl;
    std::cout << "Testing character and tile loading functionality\n" << std::endl;
    
    // Initialize managers
    TextureManager* texMgr = TextureManager::getInstance();
    texMgr->init(renderer);
    texMgr->setMediaPath("../media/");
    
    SpriteLoader* spriteLoader = SpriteLoader::getInstance();
    spriteLoader->init(texMgr);
    
    // === Test 1: Character Sprite Loading ===
    std::cout << "\n--- Test 1: Character Sprite Loading ---" << std::endl;
    
    auto player = new IsoPlayer();
    player->setPosition(50, 50);
    
    std::cout << "Loading character 'Bob'..." << std::endl;
    spriteLoader->setupPlayer(player, "Bob", false);  // Without atlas
    
    if (player->getSprite()) {
        std::cout << "✓ Player sprite loaded successfully" << std::endl;
        
        // List available animations
        auto* sprite = player->getSprite();
        std::cout << "  Testing animation switching:" << std::endl;
        
        std::vector<std::string> testAnims = {
            "Idle_S", "Walk_E", "Run_N", "Idle_W"
        };
        
        for (const auto& animName : testAnims) {
            sprite->setAnimation(animName);
            if (sprite->getCurrentAnimation()) {
                std::cout << "    ✓ " << animName << " animation available" << std::endl;
            } else {
                std::cout << "    ℹ " << animName << " animation not found (expected if textures missing)" << std::endl;
            }
        }
    } else {
        std::cout << "ℹ Player sprite not loaded (expected if textures not present)" << std::endl;
    }
    
    // === Test 2: Character Atlas Loading ===
    std::cout << "\n--- Test 2: Character Atlas Loading ---" << std::endl;
    
    std::cout << "Creating character atlas for 'Bob'..." << std::endl;
    auto* charAtlas = texMgr->createCharacterAtlas("bob_atlas", "Bob");
    
    if (charAtlas) {
        int w, h;
        SDL_QueryTexture(charAtlas->getAtlasTexture(), nullptr, nullptr, &w, &h);
        std::cout << "✓ Character atlas created" << std::endl;
        std::cout << "  Atlas size: " << w << "x" << h << std::endl;
        
        // Try to get a region
        const AtlasRegion* region = charAtlas->getRegion("textures/Bob_Idle_S.png");
        if (region) {
            std::cout << "  ✓ Sample region found: " << region->name << std::endl;
            std::cout << "    Position: (" << region->rect.x << ", " << region->rect.y << ")" << std::endl;
            std::cout << "    Size: " << region->rect.w << "x" << region->rect.h << std::endl;
        }
    } else {
        std::cout << "ℹ Character atlas not created (expected if textures missing)" << std::endl;
    }
    
    // === Test 3: Tile Loading ===
    std::cout << "\n--- Test 3: Tile Texture Loading ---" << std::endl;
    
    std::vector<std::string> testTiles = {"grass_01", "floor_wood", "dirt_01"};
    
    for (const auto& tileName : testTiles) {
        std::cout << "Loading tile: " << tileName << "..." << std::endl;
        auto* tileSprite = spriteLoader->loadTile(tileName);
        
        if (tileSprite) {
            std::cout << "  ✓ Tile loaded (size: " << tileSprite->getWidth() 
                     << "x" << tileSprite->getHeight() << ")" << std::endl;
            delete tileSprite;
        } else {
            std::cout << "  ℹ Tile not found (fallback texture may be created)" << std::endl;
        }
    }
    
    // === Test 4: Tile Atlas ===
    std::cout << "\n--- Test 4: Tile Atlas Loading ---" << std::endl;
    
    std::cout << "Loading common tiles atlas..." << std::endl;
    auto* tileAtlas = spriteLoader->loadCommonTiles();
    
    if (tileAtlas) {
        int w, h;
        SDL_QueryTexture(tileAtlas->getAtlasTexture(), nullptr, nullptr, &w, &h);
        std::cout << "✓ Tile atlas created" << std::endl;
        std::cout << "  Atlas size: " << w << "x" << h << std::endl;
        std::cout << "  Common tiles count: " << spriteLoader->getCommonTileNames().size() << std::endl;
    } else {
        std::cout << "ℹ Tile atlas not created (expected if textures missing)" << std::endl;
    }
    
    // === Test 5: Object Loading ===
    std::cout << "\n--- Test 5: Object Texture Loading ---" << std::endl;
    
    std::vector<std::string> testObjects = {"tree_oak", "chair_wood", "table"};
    
    for (const auto& objName : testObjects) {
        std::cout << "Loading object: " << objName << "..." << std::endl;
        auto* objSprite = spriteLoader->loadObject(objName);
        
        if (objSprite) {
            std::cout << "  ✓ Object loaded (size: " << objSprite->getWidth() 
                     << "x" << objSprite->getHeight() << ")" << std::endl;
            std::cout << "    Origin: (" << objSprite->getOriginX() << ", " 
                     << objSprite->getOriginY() << ")" << std::endl;
            delete objSprite;
        } else {
            std::cout << "  ℹ Object not found (fallback texture may be created)" << std::endl;
        }
    }
    
    // === Test 6: Preload Assets ===
    std::cout << "\n--- Test 6: Batch Preloading ---" << std::endl;
    
    std::cout << "Preloading common assets..." << std::endl;
    spriteLoader->preloadCommonAssets();
    
    // === Visual Test ===
    std::cout << "\n--- Visual Test ---" << std::endl;
    std::cout << "Rendering loaded sprites..." << std::endl;
    
    bool running = true;
    SDL_Event event;
    float deltaTime = 0.016f;  // ~60 FPS
    
    // Position sprites for display
    float x = 100.0f, y = 300.0f;
    
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN) {
                running = false;
            }
        }
        
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 40, 40, 50, 255);
        SDL_RenderClear(renderer);
        
        // Render player sprite if loaded
        if (player->getSprite()) {
            auto* sprite = player->getSprite();
            sprite->update(deltaTime);
            sprite->setPosition(x, y);
            sprite->render(renderer);
            
            // Draw label
            // (In real game, would use text rendering)
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(16);  // ~60 FPS
    }
    
    std::cout << "\n=== Tests Complete ===" << std::endl;
    std::cout << "\nTexture loading system ready for integration!" << std::endl;
    
    // Cleanup
    delete player;
    texMgr->shutdown();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
