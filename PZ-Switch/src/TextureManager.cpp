#include "TextureManager.h"
#include <SDL2/SDL_image.h>
#include <iostream>

namespace zombie {
namespace assets {

TextureManager* TextureManager::instance = nullptr;

TextureManager* TextureManager::getInstance() {
    if (!instance) {
        instance = new TextureManager();
    }
    return instance;
}

TextureManager::TextureManager()
    : renderer(nullptr)
    , mediaPath("../media/") // Default relative to build directory
{
}

TextureManager::~TextureManager() {
    shutdown();
}

bool TextureManager::init(SDL_Renderer* r) {
    if (!r) {
        std::cerr << "TextureManager: Invalid renderer" << std::endl;
        return false;
    }
    
    renderer = r;
    
    // Initialize SDL_image for PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image init failed: " << IMG_GetError() << std::endl;
        return false;
    }
    
    std::cout << "TextureManager initialized with media path: " << mediaPath << std::endl;
    return true;
}

void TextureManager::shutdown() {
    clearCache();
    IMG_Quit();
    renderer = nullptr;
}

SDL_Texture* TextureManager::loadTexture(const std::string& path) {
    // Check cache first
    auto it = textureCache.find(path);
    if (it != textureCache.end()) {
        return it->second;
    }
    
    // Build full path
    std::string fullPath = mediaPath + path;
    
    // Load from file
    SDL_Texture* texture = loadFromFile(fullPath);
    
    if (texture) {
        textureCache[path] = texture;
        std::cout << "Loaded texture: " << path << std::endl;
    }
    
    return texture;
}

SDL_Texture* TextureManager::getTexture(const std::string& path) {
    auto it = textureCache.find(path);
    if (it != textureCache.end()) {
        return it->second;
    }
    
    // Try to load if not cached
    return loadTexture(path);
}

bool TextureManager::getTextureSize(const std::string& path, int* w, int* h) {
    SDL_Texture* tex = getTexture(path);
    if (!tex) {
        return false;
    }
    
    return SDL_QueryTexture(tex, nullptr, nullptr, w, h) == 0;
}

void TextureManager::clearCache() {
    for (auto& pair : textureCache) {
        if (pair.second) {
            SDL_DestroyTexture(pair.second);
        }
    }
    textureCache.clear();
}

SDL_Texture* TextureManager::loadFromFile(const std::string& fullPath) {
    if (!renderer) {
        std::cerr << "TextureManager: No renderer set" << std::endl;
        return nullptr;
    }
    
    // Load image
    SDL_Surface* surface = IMG_Load(fullPath.c_str());
    if (!surface) {
        std::cerr << "Failed to load image: " << fullPath << " - " << IMG_GetError() << std::endl;
        return nullptr;
    }
    
    // Create texture from surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    if (!texture) {
        std::cerr << "Failed to create texture: " << fullPath << " - " << SDL_GetError() << std::endl;
        return nullptr;
    }
    
    return texture;
}

} // namespace assets
} // namespace zombie
