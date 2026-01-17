#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <unordered_map>

namespace zombie {

// Forward declarations
namespace assets { class TextureManager; }

namespace world {

/**
 * Tile definition - represents a single tile type
 */
struct TileDef {
    std::string name;      // e.g., "TileFloorExt_3"
    SDL_Texture* texture;  // Texture reference
    SDL_Rect srcRect;      // Source rectangle in texture
    int id;                // Unique tile ID
    
    TileDef() : texture(nullptr), id(0) {
        srcRect = {0, 0, 0, 0};
    }
};

/**
 * Tile instance in the world
 */
struct Tile {
    int tileDefId;    // Reference to TileDef
    int x, y, z;      // Position in world (z = layer/floor)
    
    Tile() : tileDefId(-1), x(0), y(0), z(0) {}
    Tile(int id, int px, int py, int pz) 
        : tileDefId(id), x(px), y(py), z(pz) {}
};

/**
 * TileMap - manages a grid of tiles
 */
class TileMap {
public:
    TileMap();
    ~TileMap();
    
    // Dimensions
    void setSize(int width, int height, int layers = 1);
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getLayerCount() const { return layers; }
    
    // Tile management
    void setTile(int x, int y, int layer, int tileDefId);
    int getTile(int x, int y, int layer) const;
    void clearTile(int x, int y, int layer);
    
    // Rendering
    void render(SDL_Renderer* renderer, class TileRegistry* registry,
               int cameraX, int cameraY, int screenW, int screenH);
    
    // Properties
    void setTileSize(int size) { tileSize = size; }
    int getTileSize() const { return tileSize; }
    
private:
    int width, height, layers;
    int tileSize;
    std::vector<int> tiles; // Flat array: [layer][y][x]
    
    int getIndex(int x, int y, int layer) const;
};

/**
 * TileRegistry - manages tile definitions
 */
class TileRegistry {
public:
    TileRegistry();
    ~TileRegistry();
    
    // Initialize with texture manager
    void init(assets::TextureManager* texMgr);
    
    // Register tile definitions
    int registerTile(const std::string& name, const std::string& texturePath, 
                    int srcX, int srcY, int srcW, int srcH);
    
    // Get tile definition
    const TileDef* getTileDef(int id) const;
    const TileDef* getTileDefByName(const std::string& name) const;
    int getTileId(const std::string& name) const;
    
    // Load tile definitions from scripts
    bool loadTileDefinitions(const std::string& path);
    
    // Cleanup
    void clear();
    
private:
    assets::TextureManager* texMgr;
    std::vector<TileDef> tileDefs;
    std::unordered_map<std::string, int> nameToId;
    int nextId;
};

/**
 * LotLoader - loads .lot files
 */
class LotLoader {
public:
    static bool loadFromFile(const std::string& path, TileMap* tileMap, 
                            TileRegistry* registry);
    
private:
    static bool parseLotFile(const std::string& path,
                            std::vector<std::string>& tileNames);
};

} // namespace world
} // namespace zombie
