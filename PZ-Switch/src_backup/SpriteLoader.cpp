#include "SpriteLoader.h"
#include "TextureManager.h"
#include "TextureAtlas.h"
#include "Sprite.h"
#include "SpriteAnimation.h"
#include "IsoPlayer.h"
#include "IsoObject.h"
#include <iostream>

namespace zombie {
namespace assets {

SpriteLoader* SpriteLoader::instance = nullptr;

SpriteLoader* SpriteLoader::getInstance() {
    if (!instance) {
        instance = new SpriteLoader();
    }
    return instance;
}

SpriteLoader::SpriteLoader()
    : textureManager(nullptr)
    , commonTilesLoaded(false)
{
}

SpriteLoader::~SpriteLoader() {
}

void SpriteLoader::init(TextureManager* texMgr) {
    textureManager = texMgr;
    std::cout << "SpriteLoader initialized" << std::endl;
}

// === Character Sprite Loading ===

zombie::graphics::AnimatedSprite* SpriteLoader::loadCharacter(
    const std::string& outfit) {
    
    if (!textureManager) {
        std::cerr << "SpriteLoader: TextureManager not initialized" << std::endl;
        return nullptr;
    }
    
    // Load character sprite sheet with all animations
    auto* sprite = textureManager->loadCharacterSpriteSheet("character", outfit);
    
    if (sprite) {
        std::cout << "Loaded character: " << outfit << std::endl;
    }
    
    return sprite;
}

void SpriteLoader::setupPlayer(
    zombie::characters::IsoPlayer* player,
    const std::string& outfit,
    bool useAtlas) {
    
    if (!player || !textureManager) {
        return;
    }
    
    zombie::graphics::AnimatedSprite* sprite = nullptr;
    
    if (useAtlas) {
        // Create character atlas and use it
        auto* atlas = textureManager->createCharacterAtlas("player", outfit);
        
        if (atlas) {
            // Create animated sprite from atlas
            sprite = new zombie::graphics::AnimatedSprite(atlas->getTexture());
            
            // Setup animations from atlas regions
            std::vector<std::string> actions = {"Idle", "Walk", "Run"};
            std::vector<std::string> directions = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};
            
            for (const auto& action : actions) {
                for (const auto& dir : directions) {
                    std::string animName = action + "_" + dir;
                    std::string spritePath = "textures/" + outfit + "_" + action + "_" + dir + ".png";
                    
                    const AtlasRegion* region = atlas->getRegion(spritePath);
                    if (region) {
                        zombie::graphics::Animation anim(animName);
                        
                        zombie::graphics::AnimationFrame frame;
                        frame.x = region->rect.x;
                        frame.y = region->rect.y;
                        frame.width = region->rect.w;
                        frame.height = region->rect.h;
                        frame.originalWidth = region->originalWidth;
                        frame.originalHeight = region->originalHeight;
                        frame.duration = 100.0f;
                        anim.addFrame(frame);
                        anim.setLoop(true);
                        
                        sprite->addAnimation(animName, anim);
                    }
                }
            }
            
            sprite->setAnimation("Idle_S");
            sprite->play();
            
            std::cout << "Setup player with atlas: " << outfit << std::endl;
        }
    } else {
        // Load without atlas
        sprite = loadCharacter(outfit);
    }
    
    if (sprite) {
        player->setSprite(std::shared_ptr<zombie::graphics::AnimatedSprite>(sprite));
        std::cout << "Player sprite configured" << std::endl;
    }
}

// === Tile Sprite Loading ===

zombie::graphics::Sprite* SpriteLoader::loadTile(const std::string& tileName) {
    if (!textureManager) {
        std::cerr << "SpriteLoader: TextureManager not initialized" << std::endl;
        return nullptr;
    }
    
    SDL_Texture* tex = textureManager->loadTileTexture(tileName);
    
    if (tex) {
        auto* sprite = new zombie::graphics::Sprite(tex);
        sprite->setSize(32.0f, 32.0f);  // Standard tile size
        return sprite;
    }
    
    return nullptr;
}

zombie::assets::TextureAtlas* SpriteLoader::loadCommonTiles() {
    if (!textureManager) {
        return nullptr;
    }
    
    if (commonTilesLoaded) {
        return textureManager->getAtlas("tiles_common");
    }
    
    auto tileNames = getCommonTileNames();
    auto* atlas = textureManager->createTileAtlas(tileNames);
    
    if (atlas) {
        commonTilesLoaded = true;
        std::cout << "Loaded common tiles atlas" << std::endl;
    }
    
    return atlas;
}

std::vector<std::string> SpriteLoader::getCommonTileNames() {
    return {
        // Grass tiles
        "grass_01", "grass_02", "grass_03",
        
        // Floor tiles
        "floor_wood", "floor_carpet", "floor_tile",
        
        // Dirt/ground
        "dirt_01", "dirt_02", "sand_01",
        
        // Stone/concrete
        "stone_floor", "concrete_floor",
        
        // Water
        "water_01", "water_02",
        
        // Road
        "asphalt_01", "road_line",
        
        // Common patterns
        "tile_checkered", "wood_planks"
    };
}

// === Object Sprite Loading ===

zombie::graphics::Sprite* SpriteLoader::loadObject(const std::string& objectType) {
    if (!textureManager) {
        std::cerr << "SpriteLoader: TextureManager not initialized" << std::endl;
        return nullptr;
    }
    
    SDL_Texture* tex = textureManager->loadObjectTexture(objectType);
    
    if (tex) {
        auto* sprite = new zombie::graphics::Sprite(tex);
        
        // Set size and origin based on object type
        int width, height;
        float originX, originY;
        
        getObjectSize(objectType, width, height);
        getObjectOrigin(objectType, originX, originY);
        
        sprite->setSize(static_cast<float>(width), static_cast<float>(height));
        sprite->setOrigin(originX, originY);
        
        return sprite;
    }
    
    return nullptr;
}

void SpriteLoader::setupObject(
    IsoObject* object,
    const std::string& objectType) {
    
    if (!object) {
        return;
    }
    
    auto* sprite = loadObject(objectType);
    
    if (sprite) {
        object->setSprite(std::shared_ptr<zombie::graphics::Sprite>(sprite));
        std::cout << "Object sprite configured: " << objectType << std::endl;
    }
}

// === Batch Loading ===

void SpriteLoader::preloadCommonAssets() {
    if (!textureManager) {
        std::cerr << "SpriteLoader: Cannot preload, TextureManager not initialized" << std::endl;
        return;
    }
    
    std::cout << "\n=== Preloading Common Assets ===" << std::endl;
    
    // Load tile atlas
    preloadTileAtlas();
    
    // Load default character
    preloadCharacterAtlases({"Bob", "Kate"});
    
    std::cout << "=== Preload Complete ===\n" << std::endl;
}

void SpriteLoader::preloadCharacterAtlases(const std::vector<std::string>& outfits) {
    for (const auto& outfit : outfits) {
        auto* atlas = textureManager->createCharacterAtlas("character", outfit);
        if (atlas) {
            loadedCharacters.push_back(outfit);
            std::cout << "  ✓ Preloaded character atlas: " << outfit << std::endl;
        } else {
            std::cout << "  ✗ Failed to preload character: " << outfit << std::endl;
        }
    }
}

void SpriteLoader::preloadTileAtlas() {
    auto* atlas = loadCommonTiles();
    if (atlas) {
        std::cout << "  ✓ Preloaded tile atlas" << std::endl;
    } else {
        std::cout << "  ✗ Failed to preload tile atlas" << std::endl;
    }
}

// === Helper Methods ===

void SpriteLoader::getObjectSize(const std::string& objectType, int& width, int& height) {
    // Default sizes for different object types
    if (objectType.find("tree") != std::string::npos) {
        width = 64;
        height = 96;
    } else if (objectType.find("chair") != std::string::npos) {
        width = 32;
        height = 48;
    } else if (objectType.find("table") != std::string::npos) {
        width = 64;
        height = 48;
    } else if (objectType.find("door") != std::string::npos) {
        width = 32;
        height = 64;
    } else if (objectType.find("window") != std::string::npos) {
        width = 32;
        height = 32;
    } else if (objectType.find("fridge") != std::string::npos ||
               objectType.find("freezer") != std::string::npos) {
        width = 48;
        height = 96;
    } else if (objectType.find("bed") != std::string::npos) {
        width = 64;
        height = 96;
    } else {
        // Default object size
        width = 32;
        height = 32;
    }
}

void SpriteLoader::getObjectOrigin(const std::string& objectType, float& originX, float& originY) {
    // Default origins for different object types
    if (objectType.find("tree") != std::string::npos) {
        // Trees anchor at bottom-center
        originX = 0.5f;
        originY = 1.0f;
    } else if (objectType.find("wall") != std::string::npos ||
               objectType.find("door") != std::string::npos ||
               objectType.find("window") != std::string::npos) {
        // Walls anchor at bottom-center
        originX = 0.5f;
        originY = 1.0f;
    } else if (objectType.find("floor") != std::string::npos ||
               objectType.find("carpet") != std::string::npos) {
        // Floor items center
        originX = 0.5f;
        originY = 0.5f;
    } else {
        // Most objects anchor at bottom-center
        originX = 0.5f;
        originY = 1.0f;
    }
}

} // namespace assets
} // namespace zombie
