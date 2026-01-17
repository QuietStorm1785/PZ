#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace zombie {
namespace assets {

/**
 * AtlasRegion - Represents a sprite region within a texture atlas
 */
struct AtlasRegion {
    std::string name;           // Sprite identifier
    SDL_Rect rect;              // Position and size in atlas
    float u1, v1, u2, v2;       // Normalized UV coordinates (0-1)
    int originalWidth;          // Original sprite width before packing
    int originalHeight;         // Original sprite height before packing
    
    AtlasRegion() 
        : name(""), rect{0, 0, 0, 0}
        , u1(0), v1(0), u2(0), v2(0)
        , originalWidth(0), originalHeight(0) {}
};

/**
 * TextureAtlas - Packs multiple small textures into one large texture
 * 
 * Benefits:
 * - Reduces texture binding overhead (1 bind vs N binds)
 * - Improves batch rendering performance
 * - Reduces memory fragmentation
 * - Better cache coherency
 */
class TextureAtlas {
public:
    struct Config {
        int maxWidth;           // Maximum atlas width (power of 2)
        int maxHeight;          // Maximum atlas height (power of 2)
        int padding;            // Pixels between sprites (prevents bleeding)
        bool powerOfTwo;        // Force power-of-2 dimensions
        
        Config() 
            : maxWidth(2048), maxHeight(2048)
            , padding(1), powerOfTwo(true) {}
    };
    
    explicit TextureAtlas(SDL_Renderer* renderer, const Config& config = Config());
    ~TextureAtlas();
    
    // Add sprite from existing texture
    bool addSprite(const std::string& name, SDL_Texture* texture, 
                   int width, int height);
    
    // Add sprite from surface
    bool addSprite(const std::string& name, SDL_Surface* surface);
    
    // Add sprite from file
    bool addSprite(const std::string& name, const std::string& filePath);
    
    // Build the atlas texture (call after adding all sprites)
    bool build();
    
    // Get region for a sprite
    const AtlasRegion* getRegion(const std::string& name) const;
    
    // Get atlas texture
    SDL_Texture* getTexture() const { return atlasTexture; }
    
    // Get atlas dimensions
    int getWidth() const { return atlasWidth; }
    int getHeight() const { return atlasHeight; }
    
    // Get all regions
    const std::unordered_map<std::string, AtlasRegion>& getRegions() const { 
        return regions; 
    }
    
    // Statistics
    int getSpriteCount() const { return static_cast<int>(sprites.size()); }
    float getUsedSpace() const; // Returns 0-1 (percentage of atlas used)
    
    // Clear atlas (for rebuilding)
    void clear();
    
private:
    struct SpriteData {
        std::string name;
        SDL_Surface* surface;
        int width;
        int height;
        bool placed;
        int x, y;  // Position in atlas after packing
    };
    
    SDL_Renderer* renderer;
    Config config;
    
    // Atlas texture and dimensions
    SDL_Texture* atlasTexture;
    int atlasWidth;
    int atlasHeight;
    
    // Sprite data before packing
    std::vector<SpriteData> sprites;
    
    // Packed regions
    std::unordered_map<std::string, AtlasRegion> regions;
    
    // Packing algorithm (simple shelf packing)
    bool packSprites();
    
    // Render sprites to atlas
    bool renderToAtlas();
    
    // Helper to get next power of 2
    int nextPowerOfTwo(int n) const;
    
    // Free sprite surfaces
    void freeSurfaces();
};

/**
 * AtlasBuilder - Helper for building atlases from multiple sources
 */
class AtlasBuilder {
public:
    AtlasBuilder(SDL_Renderer* renderer);
    ~AtlasBuilder() = default;
    
    // Add sprites from directory
    bool addSpritesFromDirectory(const std::string& dirPath, 
                                 const std::string& pattern = "*.png");
    
    // Add sprites with prefix
    bool addSpritesWithPrefix(const std::string& dirPath,
                             const std::string& prefix);
    
    // Build atlas
    std::shared_ptr<TextureAtlas> build(const TextureAtlas::Config& config = TextureAtlas::Config());
    
private:
    SDL_Renderer* renderer;
    std::vector<std::string> spritePaths;
};

} // namespace assets
} // namespace zombie
