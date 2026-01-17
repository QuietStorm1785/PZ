# Texture Loading Quick Reference

## Initialization
```cpp
// Setup managers
TextureManager* texMgr = TextureManager::getInstance();
texMgr->init(renderer);
texMgr->setMediaPath("../media/");

SpriteLoader* loader = SpriteLoader::getInstance();
loader->init(texMgr);
```

## Character Loading

### Simple Player Setup
```cpp
auto* player = new IsoPlayer();
loader->setupPlayer(player, "Bob", true);  // With atlas
```

### Character Sprite Sheet
```cpp
auto* sprite = texMgr->loadCharacterSpriteSheet("player", "Bob");
// Loads all animations: Idle/Walk/Run × 8 directions
```

### Character Atlas
```cpp
auto* atlas = texMgr->createCharacterAtlas("bob", "Bob");
// Creates 2048x2048 atlas with all character sprites
```

## Tile Loading

### Single Tile
```cpp
auto* tile = loader->loadTile("grass_01");
tile->setPosition(x, y);
tile->render(renderer);
```

### Tile Atlas
```cpp
auto* atlas = loader->loadCommonTiles();
// Loads common tiles into 4096x4096 atlas

const AtlasRegion* region = atlas->getRegion("textures/tiles/grass_01.png");
sprite.setTexture(atlas->getTexture());
sprite.setAtlasRegion(region);
```

### Custom Tile Atlas
```cpp
std::vector<std::string> tiles = {"grass_01", "dirt_01", "floor_wood"};
auto* atlas = texMgr->createTileAtlas(tiles);
```

## Object Loading

### Single Object
```cpp
auto* object = new IsoObject();
loader->setupObject(object, "tree_oak");
// Automatically sizes: 64x96, origin bottom-center
```

### Manual Object Texture
```cpp
SDL_Texture* tex = texMgr->loadObjectTexture("chair_wood");
auto* sprite = new Sprite(tex);
sprite->setSize(32, 48);
sprite->setOrigin(0.5f, 1.0f);
```

## Batch Preloading

### All Common Assets
```cpp
loader->preloadCommonAssets();
// Preloads: tile atlas + Bob + Kate character atlases
```

### Character Atlases
```cpp
loader->preloadCharacterAtlases({"Bob", "Kate", "Peter"});
```

### Tile Atlas
```cpp
loader->preloadTileAtlas();
```

## Common Tile Names
```cpp
auto tiles = SpriteLoader::getCommonTileNames();
// Returns: grass_01/02/03, floor_wood/carpet/tile,
//          dirt_01/02, sand_01, stone_floor, concrete_floor,
//          water_01/02, asphalt_01, road_line, tile_checkered, wood_planks
```

## Animation Names

### Format
`{Action}_{Direction}`

### Actions
- Idle
- Walk
- Run
- Attack
- Death

### Directions
- N, NE, E, SE, S, SW, W, NW

### Examples
```cpp
sprite->setAnimation("Idle_S");   // Facing south, idle
sprite->setAnimation("Walk_NE");  // Walking northeast
sprite->setAnimation("Run_W");    // Running west
```

## Object Sizes

| Type | Width | Height | Origin |
|------|-------|--------|--------|
| tree | 64 | 96 | (0.5, 1.0) |
| chair | 32 | 48 | (0.5, 1.0) |
| table | 64 | 48 | (0.5, 1.0) |
| door | 32 | 64 | (0.5, 1.0) |
| bed | 64 | 96 | (0.5, 1.0) |
| fridge | 48 | 96 | (0.5, 1.0) |
| default | 32 | 32 | (0.5, 1.0) |

## File Paths

### Characters
```
media/textures/{Outfit}_{Action}_{Direction}.png
Examples:
  media/textures/Bob_Idle_S.png
  media/textures/Kate_Walk_NE.png
```

### Tiles
```
media/textures/tiles/{tileName}.png
Examples:
  media/textures/tiles/grass_01.png
  media/textures/tiles/floor_wood.png
```

### Objects
```
media/textures/objects/{objectName}.png
Examples:
  media/textures/objects/tree_oak.png
  media/textures/objects/chair_wood.png
```

## Error Handling

### Check Return Values
```cpp
auto* sprite = loader->loadCharacter("Bob");
if (!sprite) {
    // Texture not found - use fallback
}

auto* atlas = texMgr->createCharacterAtlas("bob", "Bob");
if (!atlas) {
    // Atlas creation failed - use individual textures
}
```

### Fallback Textures
```cpp
// TextureManager creates colored fallbacks automatically
SDL_Texture* tex = texMgr->loadTileTexture("missing");
// Returns gray 32x32 texture

SDL_Texture* obj = texMgr->loadObjectTexture("missing");
// Returns brown 64x64 texture
```

## Performance Tips

### ✅ DO
- Use atlases for batch rendering
- Preload during loading screens
- Cache SpriteLoader instance
- Batch render by atlas
- Check atlas exists before creating

### ❌ DON'T
- Load in render loop
- Create sprites every frame
- Mix atlas/non-atlas rendering
- Skip return value checks
- Create duplicate atlases

## Common Patterns

### Loading Screen
```cpp
void loadingScreen() {
    auto* loader = SpriteLoader::getInstance();
    loader->preloadCommonAssets();
}
```

### Player Setup
```cpp
void createPlayer() {
    auto* player = new IsoPlayer();
    player->setPosition(50, 50);
    
    auto* loader = SpriteLoader::getInstance();
    loader->setupPlayer(player, "Bob", true);
    
    return player;
}
```

### Tile Rendering
```cpp
void renderTile(const std::string& tileName, float x, float y) {
    auto* atlas = loader->loadCommonTiles();
    const AtlasRegion* region = atlas->getRegion(
        "textures/tiles/" + tileName + ".png"
    );
    
    if (region) {
        Sprite sprite;
        sprite.setTexture(atlas->getTexture());
        sprite.setAtlasRegion(region);
        sprite.setPosition(x, y);
        sprite.render(renderer);
    }
}
```

## Files
- `include/TextureManager.h` - Core texture management
- `include/SpriteLoader.h` - Utility class (110 lines)
- `src/TextureManager.cpp` - Implementation (+180 lines)
- `src/SpriteLoader.cpp` - Implementation (323 lines)
- `test_texture_loading.cpp` - Test program (190 lines)

## See Also
- [TEXTURE_LOADING_GUIDE.md](TEXTURE_LOADING_GUIDE.md) - Complete guide
- [ATLAS_USAGE_EXAMPLE.md](ATLAS_USAGE_EXAMPLE.md) - Atlas examples
- [TEXTURE_ANIMATION_GUIDE.md](TEXTURE_ANIMATION_GUIDE.md) - Animation system
