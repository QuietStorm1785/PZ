# Texture Atlas Quick Reference

## Core Classes

### TextureAtlas
**Location:** `include/TextureAtlas.h`, `src/TextureAtlas.cpp`

**Purpose:** Pack multiple sprites into single texture for batch rendering

**Key Methods:**
```cpp
// Configuration
struct Config {
    int maxWidth = 2048;
    int maxHeight = 2048;
    int padding = 1;
    bool powerOfTwo = false;
};

// Construction
TextureAtlas(SDL_Renderer* renderer, const Config& config);

// Building atlas
bool addSprite(const std::string& name, SDL_Texture* texture);
bool addSprite(const std::string& name, SDL_Surface* surface);
bool addSprite(const std::string& name, const std::string& filename);
bool build();  // Pack sprites and create atlas texture

// Accessing regions
const AtlasRegion* getRegion(const std::string& name) const;
SDL_Texture* getAtlasTexture() const { return atlasTexture; }
```

### AtlasRegion
**Structure:** Sprite location within atlas

```cpp
struct AtlasRegion {
    std::string name;         // Sprite identifier
    SDL_Rect rect;            // Position in atlas (x, y, w, h)
    int originalWidth;        // Original sprite width
    int originalHeight;       // Original sprite height
    float u1, v1, u2, v2;    // Normalized UV coordinates (0-1)
};
```

### TextureManager Integration
**Location:** `include/TextureManager.h`

**Atlas Methods:**
```cpp
// Create atlas from sprite paths
TextureAtlas* createAtlas(
    const std::string& name,
    const std::vector<std::string>& spritePaths,
    int maxWidth = 2048,
    int maxHeight = 2048
);

// Get cached atlas
TextureAtlas* getAtlas(const std::string& name);
```

## Quick Usage Patterns

### Create Atlas
```cpp
auto* texMgr = TextureManager::getInstance();

std::vector<std::string> sprites = {
    "char_idle.png",
    "char_walk_01.png",
    "char_walk_02.png"
};

TextureAtlas* atlas = texMgr->createAtlas(
    "character", sprites, 1024, 1024
);
```

### Use Atlas with Sprite
```cpp
// Get atlas and region
TextureAtlas* atlas = texMgr->getAtlas("character");
const AtlasRegion* region = atlas->getRegion("char_idle.png");

// Setup sprite
Sprite* sprite = new Sprite();
sprite->setTexture(atlas->getAtlasTexture());
sprite->setAtlasRegion(region);

// Render
sprite->render(renderer);
```

### Batch Render from Atlas
```cpp
// Group sprites by atlas
for (auto* sprite : sprites) {
    if (sprite->isFromAtlas()) {
        // Already batched by atlas texture
    }
}
```

## Performance Tips

### ✅ DO
- Group related sprites in same atlas (characters, tiles, UI)
- Use power-of-2 dimensions (512, 1024, 2048, 4096)
- Add 2-4 pixel padding to prevent bleeding
- Batch render sprites from same atlas
- Create atlases during loading screens

### ❌ DON'T
- Mix frequently updated sprites with static sprites
- Create atlases larger than GPU supports (usually max 4096)
- Forget padding between sprites
- Create one giant atlas for everything
- Rebuild atlases at runtime frequently

## Common Configurations

### Character Atlas (Medium)
```cpp
Config config;
config.maxWidth = 2048;
config.maxHeight = 2048;
config.padding = 2;
config.powerOfTwo = true;
```

### Tile Atlas (Large)
```cpp
Config config;
config.maxWidth = 4096;
config.maxHeight = 4096;
config.padding = 1;
config.powerOfTwo = true;
```

### UI Atlas (Small)
```cpp
Config config;
config.maxWidth = 1024;
config.maxHeight = 1024;
config.padding = 2;
config.powerOfTwo = true;
```

## Sprite Class Atlas Support

### Check if Sprite Uses Atlas
```cpp
if (sprite->isFromAtlas()) {
    // Sprite renders from atlas
}
```

### Set Atlas Region
```cpp
sprite->setAtlasRegion(region);  // Automatically sets sourceRect and size
```

## Troubleshooting

| Problem | Solution |
|---------|----------|
| `build()` returns false | Sprites too large - increase maxWidth/maxHeight or split into multiple atlases |
| Texture bleeding at edges | Increase `config.padding` to 2-4 pixels |
| Poor batching performance | Group sprites by atlas before rendering |
| Sprite not found | Verify sprite name matches path used in `addSprite()` |
| Memory issues | Reduce atlas count, use smaller max dimensions |

## API at a Glance

```cpp
// === TextureManager ===
TextureAtlas* createAtlas(name, paths, maxW, maxH);
TextureAtlas* getAtlas(name);

// === TextureAtlas ===
bool addSprite(name, texture/surface/file);
bool build();
const AtlasRegion* getRegion(name);
SDL_Texture* getAtlasTexture();

// === Sprite ===
void setAtlasRegion(const AtlasRegion* region);
bool isFromAtlas() const;

// === AtlasRegion ===
std::string name;
SDL_Rect rect;
int originalWidth, originalHeight;
float u1, v1, u2, v2;  // UV coordinates
```

## Example Workflow

```cpp
// 1. Initialize
auto* texMgr = TextureManager::getInstance();

// 2. Create atlas
std::vector<std::string> paths = {"sprite1.png", "sprite2.png"};
TextureAtlas* atlas = texMgr->createAtlas("game_atlas", paths);

// 3. Create sprite from atlas
Sprite* sprite = new Sprite();
sprite->setTexture(atlas->getAtlasTexture());
sprite->setAtlasRegion(atlas->getRegion("sprite1.png"));

// 4. Render
sprite->setPosition(100, 200);
sprite->render(renderer);

// 5. Cleanup (handled by TextureManager)
// atlas deleted in TextureManager::clearCache()
```

## Files

- **Headers:** `include/TextureAtlas.h`, `include/TextureManager.h`, `include/Sprite.h`
- **Implementation:** `src/TextureAtlas.cpp`, `src/TextureManager.cpp`, `src/Sprite.cpp`
- **Documentation:** `ATLAS_USAGE_EXAMPLE.md` (detailed examples)
