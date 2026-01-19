#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <string_view>
#include <vector>
#include <memory>

// Forward declarations (global namespace)
class IsoObject;

namespace zombie {

// Forward declarations
namespace graphics {
 class Sprite;
 class AnimatedSprite;
}

namespace assets {
 class TextureManager;
 class TextureAtlas;
}

namespace characters {
 class IsoPlayer;
}

namespace assets {

/**
 * Utility class for loading sprites and configuring game objects
 */
class SpriteLoader {
public:
 static SpriteLoader* getInstance();
 
 SpriteLoader();
 ~SpriteLoader();
 
 // Initialize with texture manager
 void init(TextureManager* texMgr);
 
 // === Character Sprite Loading ===
 
 // Load complete character with all animations
 zombie::graphics::AnimatedSprite* loadCharacter(
 std::string_view outfit = "Bob"
 );
 
 // Setup player with sprite
 void setupPlayer(
 zombie::characters::IsoPlayer* player,
 std::string_view outfit = "Bob",
 bool useAtlas = true
 );
 
 // === Tile Sprite Loading ===
 
 // Load single tile sprite
 zombie::graphics::Sprite* loadTile(std::string_view tileName);
 
 // Load common tiles into atlas
 zombie::assets::TextureAtlas* loadCommonTiles();
 
 // Get common tile names
 static std::vector<std::string> getCommonTileNames();
 
 // === Object Sprite Loading ===
 
 // Load object sprite by type
 zombie::graphics::Sprite* loadObject(std::string_view objectType);
 
 // Setup object with sprite
 void setupObject(
 IsoObject* object,
 std::string_view objectType
 );
 
 // === Batch Loading ===
 
 // Preload all common assets
 void preloadCommonAssets();
 
 // Preload character atlases
 void preloadCharacterAtlases(const std::vector<std::string>& outfits);
 
 // Preload tile atlas
 void preloadTileAtlas();
 
 // === Helper Methods ===
 
 // Get sprite size for object type
 static void getObjectSize(std::string_view objectType, int& width, int& height);
 
 // Get sprite origin for object type (0-1 range)
 static void getObjectOrigin(std::string_view objectType, float& originX, float& originY);
 
private:
 static SpriteLoader* instance;
 TextureManager* textureManager;
 
 // Track loaded atlases
 bool commonTilesLoaded;
 std::vector<std::string> loadedCharacters;
};

} // namespace assets
} // namespace zombie
