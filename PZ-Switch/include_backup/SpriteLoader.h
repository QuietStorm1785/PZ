#pragma once
#include <SDL2/SDL.h>
#include <string>
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
        const std::string& outfit = "Bob"
    );
    
    // Setup player with sprite
    void setupPlayer(
        zombie::characters::IsoPlayer* player,
        const std::string& outfit = "Bob",
        bool useAtlas = true
    );
    
    // === Tile Sprite Loading ===
    
    // Load single tile sprite
    zombie::graphics::Sprite* loadTile(const std::string& tileName);
    
    // Load common tiles into atlas
    zombie::assets::TextureAtlas* loadCommonTiles();
    
    // Get common tile names
    static std::vector<std::string> getCommonTileNames();
    
    // === Object Sprite Loading ===
    
    // Load object sprite by type
    zombie::graphics::Sprite* loadObject(const std::string& objectType);
    
    // Setup object with sprite
    void setupObject(
        IsoObject* object,
        const std::string& objectType
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
    static void getObjectSize(const std::string& objectType, int& width, int& height);
    
    // Get sprite origin for object type (0-1 range)
    static void getObjectOrigin(const std::string& objectType, float& originX, float& originY);
    
private:
    static SpriteLoader* instance;
    TextureManager* textureManager;
    
    // Track loaded atlases
    bool commonTilesLoaded;
    std::vector<std::string> loadedCharacters;
};

} // namespace assets
} // namespace zombie
