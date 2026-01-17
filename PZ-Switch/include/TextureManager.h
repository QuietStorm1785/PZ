#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

namespace zombie {

// Forward declarations
namespace graphics { 
    class AnimatedSprite; 
    class Animation;
    struct AnimationFrame;
}

namespace assets {

/**
 * Texture asset manager with caching
 */
class TextureManager {
public:
    static TextureManager* getInstance();
    
    TextureManager();
    ~TextureManager();
    
    // Initialize with renderer
    bool init(SDL_Renderer* renderer);
    void shutdown();
    
    // Load texture from media directory
    SDL_Texture* loadTexture(const std::string& path);
    
    // Get cached texture
    SDL_Texture* getTexture(const std::string& path);
    
    // Get texture dimensions
    bool getTextureSize(const std::string& path, int* w, int* h);
    
    // Set media directory base path
    void setMediaPath(const std::string& path) { mediaPath = path; }
    std::string getMediaPath() const { return mediaPath; }
    
    // Clear cache
    void clearCache();
    
    // Load animated sprite from PZ texture pack format
    // Loads both .png and .txt files (e.g., "ShirtGrey_Walk" -> ShirtGrey_Walk.png + .txt)
    zombie::graphics::AnimatedSprite* loadAnimatedSprite(const std::string& baseName);
    
    // Parse PZ animation format (.txt file)
    bool parseAnimationFile(const std::string& txtPath, 
                           std::unordered_map<std::string, zombie::graphics::Animation>& animations);
    
private:
    static TextureManager* instance;
    
    SDL_Renderer* renderer;
    std::string mediaPath;
    
    // Texture cache
    std::unordered_map<std::string, SDL_Texture*> textureCache;
    
    // Load from file
    SDL_Texture* loadFromFile(const std::string& fullPath);
};

} // namespace assets
} // namespace zombie
