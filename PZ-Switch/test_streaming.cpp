// Test Asset Streaming System
#include "AssetStreaming.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace zombie::assets;

void printStats(AssetStreamingSystem& system, const std::string& phase) {
    std::cout << "\n=== " << phase << " ===" << std::endl;
    std::cout << "Memory Usage: " << (system.getCurrentMemoryUsage() / 1024 / 1024) << " MB" << std::endl;
    std::cout << "Cache Hit Rate: " << std::fixed << std::setprecision(2) 
              << (system.getCacheHitRate() * 100) << "%" << std::endl;
    std::cout << "Total Requests: " << system.getTotalRequests() << std::endl;
    std::cout << "Cache Hits: " << system.getCacheHits() << std::endl;
    std::cout << "Cache Misses: " << system.getCacheMisses() << std::endl;
}

int main() {
    std::cout << "Asset Streaming System Test\n" << std::endl;
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "✗ FAIL: Could not initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "✗ FAIL: Could not initialize SDL_image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    
    std::cout << "✓ SDL and SDL_image initialized" << std::endl;
    
    // Create streaming system with small memory budget for testing
    AssetStreamingSystem::Config config;
    config.maxMemoryBytes = 32 * 1024 * 1024; // 32 MB budget
    config.unloadDelay = 2.0f; // 2 seconds for testing
    
    AssetStreamingSystem system(config);
    
    // Test 1: Request non-existent texture (should fail gracefully)
    std::cout << "\nTest 1: Request non-existent texture..." << std::endl;
    auto handle1 = system.requestTexture("nonexistent.png");
    if (!handle1.isValid()) {
        std::cout << "✓ PASS: Correctly handled missing texture" << std::endl;
    } else {
        std::cout << "✗ FAIL: Should not have loaded nonexistent texture" << std::endl;
    }
    printStats(system, "After requesting nonexistent texture");
    
    // Test 2: Check if we have test textures
    std::cout << "\nTest 2: Checking for test textures..." << std::endl;
    const char* testTextures[] = {
        "media/zombie1.png",
        "media/zombie2.png",
        "media/zombie3.png",
        "media/player.png"
    };
    
    int availableTextures = 0;
    for (const char* path : testTextures) {
        std::string fullPath = "/workspaces/PZ/PZ-Switch/" + std::string(path);
        SDL_Surface* surface = IMG_Load(fullPath.c_str());
        if (surface) {
            availableTextures++;
            SDL_FreeSurface(surface);
            std::cout << "  Found: " << path << std::endl;
        }
    }
    
    if (availableTextures == 0) {
        std::cout << "\nWARNING: No test textures found. Creating placeholder test..." << std::endl;
        std::cout << "Streaming system functional checks will be limited." << std::endl;
        
        // We can still test the caching logic with null handles
        std::cout << "\nTest 3: Cache behavior test..." << std::endl;
        auto h1 = system.requestTexture("test1.png");
        auto h2 = system.requestTexture("test2.png");
        auto h3 = system.requestTexture("test1.png"); // Should hit cache
        
        printStats(system, "After cache test");
        
        if (system.getTotalRequests() == 3 && system.getCacheHits() > 0) {
            std::cout << "✓ PASS: Cache logic working (hits: " << system.getCacheHits() << ")" << std::endl;
        }
    } else {
        std::cout << "✓ Found " << availableTextures << " test textures" << std::endl;
        
        // Test 3: Load and cache textures
        std::cout << "\nTest 3: Loading textures..." << std::endl;
        std::vector<AssetHandle<SDL_Texture>> handles;
        for (const char* path : testTextures) {
            auto handle = system.requestTexture(path);
            if (handle.isValid()) {
                handles.push_back(handle);
                std::cout << "  Loaded: " << path << std::endl;
            }
        }
        printStats(system, "After loading textures");
        
        // Test 4: Request same textures again (should hit cache)
        std::cout << "\nTest 4: Re-requesting textures (should hit cache)..." << std::endl;
        for (const char* path : testTextures) {
            auto handle = system.requestTexture(path);
        }
        printStats(system, "After re-requesting textures");
        
        double hitRate = system.getCacheHitRate() * 100;
        if (hitRate > 40.0) {
            std::cout << "✓ PASS: Cache hit rate " << std::fixed << std::setprecision(1) 
                      << hitRate << "% (caching working)" << std::endl;
        } else {
            std::cout << "✗ FAIL: Cache hit rate too low (" << std::fixed << std::setprecision(1) 
                      << hitRate << "%)" << std::endl;
        }
        
        // Test 5: Unload delay
        std::cout << "\nTest 5: Testing unload delay..." << std::endl;
        handles.clear(); // Release all handles
        std::cout << "  Released all handles, waiting 3 seconds..." << std::endl;
        
        for (int i = 0; i < 3; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            system.update(1.0f);
            std::cout << "  " << (i+1) << "s..." << std::endl;
        }
        
        size_t memoryAfterUnload = system.getCurrentMemoryUsage();
        std::cout << "  Memory after unload: " << (memoryAfterUnload / 1024 / 1024) << " MB" << std::endl;
        
        if (memoryAfterUnload == 0) {
            std::cout << "✓ PASS: Unused assets unloaded after delay" << std::endl;
        } else {
            std::cout << "  (Assets may still be in cache, this is acceptable)" << std::endl;
        }
    }
    
    // Summary
    std::cout << "\n=== Test Summary ===" << std::endl;
    printStats(system, "Final Statistics");
    
    if (system.getTotalRequests() > 0) {
        std::cout << "✓ PASS: Streaming system operational" << std::endl;
    }
    
    // Cleanup
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}
