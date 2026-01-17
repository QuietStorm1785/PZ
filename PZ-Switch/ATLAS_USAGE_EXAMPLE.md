# Texture Atlas Usage Examples

This guide demonstrates how to use the texture atlas system for optimal rendering performance.

## Overview

The texture atlas system packs multiple sprites into a single texture, dramatically reducing GPU texture binding overhead. This is critical for rendering many sprites efficiently.

**Performance Benefits:**
- Reduces texture binds from N sprites → 1 atlas texture
- Enables batch rendering of sprites from same atlas
- Minimizes GPU state changes
- Reduces memory bandwidth usage

## Basic Atlas Creation

### Example 1: Creating a Character Atlas

```cpp
#include "TextureManager.h"
#include "TextureAtlas.h"
#include "Sprite.h"

using namespace zombie::assets;

// In your initialization code
TextureManager* texMgr = TextureManager::getInstance();

// Define sprites to pack into atlas
std::vector<std::string> characterSprites = {
    "textures/Bob_Idle_N.png",
    "textures/Bob_Idle_E.png",
    "textures/Bob_Idle_S.png",
    "textures/Bob_Idle_W.png",
    "textures/Bob_Walk_N_01.png",
    "textures/Bob_Walk_N_02.png",
    "textures/Bob_Walk_E_01.png",
    "textures/Bob_Walk_E_02.png"
};

// Create atlas (2048x2048 max, power-of-2 sizing)
TextureAtlas* charAtlas = texMgr->createAtlas(
    "character_atlas",    // Atlas name
    characterSprites,     // Sprite paths
    2048,                 // Max width
    2048                  // Max height
);

if (!charAtlas) {
    std::cerr << "Failed to create character atlas!" << std::endl;
}
```

### Example 2: Using Sprites from Atlas

```cpp
#include "Sprite.h"
#include "TextureAtlas.h"

using namespace zombie::graphics;
using namespace zombie::assets;

// Get atlas from manager
TextureAtlas* atlas = texMgr->getAtlas("character_atlas");

// Create sprite from atlas region
Sprite* playerSprite = new Sprite();
playerSprite->setTexture(atlas->getAtlasTexture());

// Get region for specific sprite
const AtlasRegion* region = atlas->getRegion("textures/Bob_Idle_S.png");
if (region) {
    playerSprite->setAtlasRegion(region);
    // Sprite now renders using UV coordinates from atlas
}

// Position and render
playerSprite->setPosition(100.0f, 200.0f);
playerSprite->render(renderer);
```

## Advanced Atlas Usage

### Example 3: Multiple Atlases for Different Categories

```cpp
// Create separate atlases for different sprite types
TextureAtlas* uiAtlas = texMgr->createAtlas("ui_atlas", {
    "ui/button_normal.png",
    "ui/button_hover.png",
    "ui/button_pressed.png",
    "ui/health_bar.png",
    "ui/inventory_slot.png"
}, 1024, 1024);

TextureAtlas* tileAtlas = texMgr->createAtlas("tile_atlas", {
    "tiles/grass_01.png",
    "tiles/grass_02.png",
    "tiles/dirt_01.png",
    "tiles/stone_01.png",
    "tiles/water_01.png"
}, 2048, 2048);

TextureAtlas* itemAtlas = texMgr->createAtlas("item_atlas", {
    "items/axe.png",
    "items/hammer.png",
    "items/bandage.png",
    "items/canned_food.png"
}, 1024, 1024);
```

### Example 4: Batch Rendering with Atlas

```cpp
void ChunkRenderer::renderSpritesOptimized(
    const std::vector<Sprite*>& sprites,
    SDL_Renderer* renderer
) {
    // Group sprites by atlas
    std::unordered_map<SDL_Texture*, std::vector<Sprite*>> atlasBatches;
    
    for (Sprite* sprite : sprites) {
        if (sprite->isFromAtlas()) {
            atlasBatches[sprite->getTexture()].push_back(sprite);
        } else {
            // Render non-atlas sprites individually
            sprite->render(renderer);
        }
    }
    
    // Render each atlas batch
    for (auto& [atlasTexture, batchSprites] : atlasBatches) {
        // Texture is bound once for all sprites in batch
        for (Sprite* sprite : batchSprites) {
            sprite->render(renderer);
        }
    }
}
```

### Example 5: Dynamic Atlas Management

```cpp
class SpriteAtlasManager {
public:
    void loadWorldAtlases() {
        // Load all world sprites into atlases by category
        loadCharacterAtlas();
        loadEnvironmentAtlas();
        loadItemAtlas();
    }
    
    void loadCharacterAtlas() {
        std::vector<std::string> sprites;
        
        // Add all character animation frames
        for (const auto& character : {"Bob", "Kate", "Peter"}) {
            for (const auto& action : {"Idle", "Walk", "Run"}) {
                for (const auto& dir : {"N", "E", "S", "W"}) {
                    sprites.push_back(
                        fmt::format("characters/{}_{}_{}_.png", 
                                  character, action, dir)
                    );
                }
            }
        }
        
        auto* texMgr = TextureManager::getInstance();
        charAtlas = texMgr->createAtlas("all_characters", sprites, 4096, 4096);
    }
    
    Sprite* createCharacterSprite(const std::string& name, 
                                 const std::string& action,
                                 const std::string& direction) {
        if (!charAtlas) return nullptr;
        
        std::string spriteName = fmt::format("characters/{}_{}_{}.png",
                                           name, action, direction);
        
        const AtlasRegion* region = charAtlas->getRegion(spriteName);
        if (!region) return nullptr;
        
        Sprite* sprite = new Sprite();
        sprite->setTexture(charAtlas->getAtlasTexture());
        sprite->setAtlasRegion(region);
        return sprite;
    }
    
private:
    TextureAtlas* charAtlas = nullptr;
};
```

## Atlas Configuration

### Atlas Configuration Options

```cpp
// Configure atlas packing parameters
TextureAtlas::Config config;
config.maxWidth = 2048;      // Maximum atlas width
config.maxHeight = 2048;     // Maximum atlas height
config.padding = 2;          // Pixels between sprites (prevents bleeding)
config.powerOfTwo = true;    // Use power-of-2 dimensions (GPU friendly)

TextureAtlas* atlas = new TextureAtlas(renderer, config);

// Add sprites from files
atlas->addSprite("sprite_1", "path/to/sprite1.png");
atlas->addSprite("sprite_2", "path/to/sprite2.png");

// Or add from surfaces
SDL_Surface* surface = IMG_Load("sprite.png");
atlas->addSprite("sprite_3", surface);
SDL_FreeSurface(surface);

// Build the atlas
if (atlas->build()) {
    std::cout << "Atlas built successfully!" << std::endl;
} else {
    std::cerr << "Atlas packing failed - sprites too large!" << std::endl;
}
```

## Integration with AnimatedSprite

### Example 6: Animated Sprites with Atlas

```cpp
#include "SpriteAnimation.h"
#include "TextureAtlas.h"

// Create atlas with animation frames
std::vector<std::string> walkFrames;
for (int i = 0; i < 8; ++i) {
    walkFrames.push_back(
        fmt::format("animations/walk_frame_{:02d}.png", i)
    );
}

TextureAtlas* animAtlas = texMgr->createAtlas(
    "walk_animation",
    walkFrames,
    1024, 1024
);

// Create animated sprite using atlas regions
auto* animSprite = new zombie::graphics::AnimatedSprite();
animSprite->setTexture(animAtlas->getAtlasTexture());

// Create animation from atlas regions
zombie::graphics::Animation walkAnim("walk");
for (const auto& framePath : walkFrames) {
    const AtlasRegion* region = animAtlas->getRegion(framePath);
    if (region) {
        zombie::graphics::AnimationFrame frame;
        frame.sourceRect = region->rect;
        frame.duration = 100.0f;  // 100ms per frame
        walkAnim.addFrame(frame);
    }
}

animSprite->addAnimation(walkAnim);
animSprite->setAnimation("walk");

// Update and render
animSprite->update(deltaTime);
animSprite->render(renderer);
```

## Performance Monitoring

### Example 7: Atlas Statistics

```cpp
void printAtlasStats(TextureAtlas* atlas) {
    if (!atlas) return;
    
    int atlasWidth, atlasHeight;
    SDL_QueryTexture(atlas->getAtlasTexture(), 
                    nullptr, nullptr, 
                    &atlasWidth, &atlasHeight);
    
    std::cout << "Atlas Statistics:" << std::endl;
    std::cout << "  Dimensions: " << atlasWidth << "x" << atlasHeight << std::endl;
    std::cout << "  Total Sprites: " << atlas->getSpriteCount() << std::endl;
    
    // Calculate utilization
    int usedPixels = 0;
    for (const auto& [name, region] : atlas->getAllRegions()) {
        usedPixels += region.rect.w * region.rect.h;
    }
    
    int totalPixels = atlasWidth * atlasHeight;
    float utilization = (float)usedPixels / totalPixels * 100.0f;
    
    std::cout << "  Utilization: " << utilization << "%" << std::endl;
}

// Usage
TextureAtlas* atlas = texMgr->getAtlas("character_atlas");
printAtlasStats(atlas);
```

## Best Practices

### 1. **Group Sprites Logically**
   - Create separate atlases for different sprite categories (characters, tiles, items, UI)
   - Keeps atlas sizes manageable
   - Easier to load/unload based on game state

### 2. **Optimize Atlas Size**
   - Use power-of-2 dimensions (512, 1024, 2048, 4096)
   - Add padding (2-4 pixels) between sprites to prevent bleeding
   - Monitor atlas utilization - aim for 70-90%

### 3. **Batch Rendering**
   - Sort sprites by atlas before rendering
   - Minimize texture binding by rendering all sprites from same atlas together
   - Use SpriteBatch for automatic batching

### 4. **Memory Management**
   - Create atlases during loading screens
   - Cache atlases in TextureManager
   - Clean up atlases when changing levels/scenes

### 5. **Size Limits**
   - Stay within GPU texture size limits (usually 2048-8192)
   - Split large sprite sets into multiple atlases
   - Use TextureAtlas::Config to enforce limits

## Common Patterns

### Pattern 1: Load Screen Atlas Creation
```cpp
void LoadingScreen::loadAssets() {
    showProgress("Loading character sprites...");
    createCharacterAtlases();
    
    showProgress("Loading environment tiles...");
    createTileAtlases();
    
    showProgress("Loading UI elements...");
    createUIAtlases();
    
    showProgress("Loading complete!");
}
```

### Pattern 2: Lazy Atlas Loading
```cpp
TextureAtlas* getOrCreateAtlas(const std::string& name) {
    auto* texMgr = TextureManager::getInstance();
    TextureAtlas* atlas = texMgr->getAtlas(name);
    
    if (!atlas) {
        // Load atlas sprites from configuration
        auto sprites = loadAtlasConfig(name);
        atlas = texMgr->createAtlas(name, sprites);
    }
    
    return atlas;
}
```

### Pattern 3: Level-Based Atlas Management
```cpp
class LevelRenderer {
public:
    void loadLevel(const std::string& levelName) {
        // Unload previous atlases
        unloadAtlases();
        
        // Load level-specific atlases
        atlases["tiles"] = createTileAtlas(levelName);
        atlases["objects"] = createObjectAtlas(levelName);
        atlases["enemies"] = createEnemyAtlas(levelName);
    }
    
    void unloadAtlases() {
        atlases.clear();  // TextureManager handles cleanup
    }
    
private:
    std::unordered_map<std::string, TextureAtlas*> atlases;
};
```

## Troubleshooting

### Atlas Packing Fails
- **Symptom:** `build()` returns false
- **Cause:** Sprites don't fit in maxWidth/maxHeight
- **Solution:** Increase atlas size or split into multiple atlases

### Texture Bleeding
- **Symptom:** Visible artifacts at sprite edges
- **Cause:** Insufficient padding between sprites
- **Solution:** Increase `config.padding` to 2-4 pixels

### Poor Performance
- **Symptom:** Low FPS despite using atlases
- **Cause:** Not batch rendering by atlas
- **Solution:** Group sprites by atlas before rendering

### Missing Sprites
- **Symptom:** Some sprites render as blank
- **Cause:** Region name doesn't match sprite path
- **Solution:** Verify sprite names with `atlas->getRegion()`

## See Also

- [include/TextureAtlas.h](include/TextureAtlas.h) - Atlas class definition
- [src/TextureAtlas.cpp](src/TextureAtlas.cpp) - Implementation details
- [include/TextureManager.h](include/TextureManager.h) - Texture and atlas management
- [TEXTURE_ANIMATION_GUIDE.md](TEXTURE_ANIMATION_GUIDE.md) - Animation system integration
