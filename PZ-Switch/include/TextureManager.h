#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <string_view>
#include <unordered_map>
#include <memory>
#include <vector>
#include "AssetStreaming.h"

namespace zombie {

// Forward declarations
namespace graphics { 
 class AnimatedSprite; 
 class Animation;
 struct AnimationFrame;
}

namespace assets {
 class TextureAtlas; // Forward declaration
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
 SDL_Texture* loadTexture(std::string_view path);
 
 // Get cached texture
 SDL_Texture* getTexture(std::string_view path);
 
 // Get texture dimensions
 bool getTextureSize(std::string_view path, int* w, int* h);
 
 // Set media directory base path
 void setMediaPath(std::string_view path) { mediaPath = path; }
 std::string getMediaPath() const { return mediaPath; }

 // Atlas knobs
 void setAtlasTextureFormat(SDL_PixelFormatEnum format) { preferredAtlasFormat = format; }
 void enableAtlasMipmaps(bool enable, int maxLevels = 4);

 // Streaming controls
 void setStreamingEnabled(bool enabled);
 bool isStreamingEnabled() const { return streamingEnabled; }
 void updateStreaming(float deltaTime);
 
 // Clear cache
 void clearCache();
 
 // Load animated sprite from PZ texture pack format
 // Loads both .png and .txt files (e.g., "ShirtGrey_Walk" -> ShirtGrey_Walk.png + .txt)
 zombie::graphics::AnimatedSprite* loadAnimatedSprite(std::string_view baseName);
 
 // Parse PZ animation format (.txt file)
 bool parseAnimationFile(std::string_view txtPath, 
 std::unordered_map<std::string, zombie::graphics::Animation>& animations);
 
 // Create texture atlas from multiple sprites
 zombie::assets::TextureAtlas* createAtlas(std::string_view name, 
 const std::vector<std::string>& spritePaths,
 int maxWidth = 2048, int maxHeight = 2048);
 
 // Get cached atlas
 zombie::assets::TextureAtlas* getAtlas(std::string_view name);

 // Load a Project Zomboid texture pack (directory with .png + .txt definitions)
 // Returns map of base sprite name -> AnimatedSprite*
 bool loadTexturePack(std::string_view packName,
 std::unordered_map<std::string, zombie::graphics::AnimatedSprite*>& outSprites,
 bool buildAtlas = false,
 int atlasMaxWidth = 2048,
 int atlasMaxHeight = 2048);
 
 // Load character sprite sheet (8-direction animations)
 zombie::graphics::AnimatedSprite* loadCharacterSpriteSheet(
 std::string_view characterName,
 std::string_view outfit = "Bob"
 );
 
 // Load tile texture by name (e.g., "grass_01", "dirt_floor")
 SDL_Texture* loadTileTexture(std::string_view tileName);
 
 // Load object texture (furniture, containers, etc.)
 SDL_Texture* loadObjectTexture(std::string_view objectName);
 
 // Create character atlas from all animations
 zombie::assets::TextureAtlas* createCharacterAtlas(
 std::string_view characterName,
 std::string_view outfit = "Bob"
 );
 
 // Create tile atlas from common tiles
 zombie::assets::TextureAtlas* createTileAtlas(
 const std::vector<std::string>& tileNames
 );

 // Build atlas from hottest requested textures
 zombie::assets::TextureAtlas* buildUsageAtlas(
 std::string_view atlasName,
 int minUsage = 3,
 int maxSprites = 256,
 int maxWidth = 2048,
 int maxHeight = 2048
 );

 // Dynamically add a sprite to an existing atlas and rebuild
 bool addSpriteToAtlas(std::string_view atlasName, std::string_view spritePath);
 
private:
 static TextureManager* instance;
 
 SDL_Renderer* renderer;
 std::string mediaPath;

 SDL_PixelFormatEnum preferredAtlasFormat;
 bool atlasGenerateMipmaps;
 int atlasMaxMipLevels;
 
 struct CachedTextureEntry {
 SDL_Texture* texture{nullptr};
 AssetHandle<SDL_Texture> streamingHandle;
 };

 // Texture cache
 std::unordered_map<std::string, CachedTextureEntry> textureCache;
 
 // Atlas cache
 std::unordered_map<std::string, zombie::assets::TextureAtlas*> atlasCache;

 // Owned animated sprites loaded via texture packs
 std::vector<std::unique_ptr<zombie::graphics::AnimatedSprite>> packSpriteStore;
 
 // Optional streaming
 std::unique_ptr<AssetStreamingSystem> streamingSystem;
 bool streamingEnabled;

 // Usage tracking for auto-atlas generation
 std::unordered_map<std::string, int> usageCounts;
 
 // Load from file
 SDL_Texture* loadFromFile(std::string_view fullPath);
 void registerUsage(std::string_view path);
};

} // namespace assets
} // namespace zombie
