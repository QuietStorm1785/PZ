#include "TileMap.h"
#include "TextureManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>

namespace zombie {
namespace world {

// TileMap implementation

TileMap::TileMap()
 : width(0)
 , height(0)
 , layers(1)
 , tileSize(32)
{
}

TileMap::~TileMap() {
}

void TileMap::setSize(int w, int h, int l) {
 width = w;
 height = h;
 layers = l;
 
 tiles.clear();
 tiles.resize(width * height * layers, -1);
}

int TileMap::getIndex(int x, int y, int layer) const {
 if (x < 0 || x >= width || y < 0 || y >= height || layer < 0 || layer >= layers) {
 return -1;
 }
 return layer * (width * height) + y * width + x;
}

void TileMap::setTile(int x, int y, int layer, int tileDefId) {
 int index = getIndex(x, y, layer);
 if (index >= 0 && index < static_cast<int>(tiles.size())) {
 tiles[index] = tileDefId;
 }
}

int TileMap::getTile(int x, int y, int layer) const {
 int index = getIndex(x, y, layer);
 if (index >= 0 && index < static_cast<int>(tiles.size())) {
 return tiles[index];
 }
 return -1;
}

void TileMap::clearTile(int x, int y, int layer) {
 setTile(x, y, layer, -1);
}

void TileMap::render(SDL_Renderer* renderer, TileRegistry* registry,
 int cameraX, int cameraY, int screenW, int screenH) {
 if (!registry) return;
 
 // Calculate visible tile range
 int startX = std::max(0, cameraX / tileSize);
 int startY = std::max(0, cameraY / tileSize);
 int endX = std::min(width, (cameraX + screenW) / tileSize + 1);
 int endY = std::min(height, (cameraY + screenH) / tileSize + 1);
 
 // Render all layers
 for (int layer = 0; layer < layers; layer++) {
 for (int y = startY; y < endY; y++) {
 for (int x = startX; x < endX; x++) {
 int tileId = getTile(x, y, layer);
 if (tileId < 0) continue;
 
 const TileDef* tileDef = registry->getTileDef(tileId);
 if (!tileDef || !tileDef->texture) continue;
 
 // Calculate screen position
 SDL_Rect dstRect;
 dstRect.x = x * tileSize - cameraX;
 dstRect.y = y * tileSize - cameraY;
 dstRect.w = tileSize;
 dstRect.h = tileSize;
 
 // Render tile
 SDL_RenderCopy(renderer, tileDef->texture, &tileDef->srcRect, &dstRect);
 }
 }
 }
}

// TileRegistry implementation

TileRegistry::TileRegistry()
 : texMgr(nullptr)
 , nextId(0)
{
}

TileRegistry::~TileRegistry() {
 clear();
}

void TileRegistry::init(assets::TextureManager* tm) {
 texMgr = tm;
}

int TileRegistry::registerTile(const std::string& name, const std::string& texturePath,
 int srcX, int srcY, int srcW, int srcH) {
 if (!texMgr) {
 std::cerr << "TileRegistry: TextureManager not initialized" << '\n';
 return -1;
 }
 
 // Check if already registered
 auto it = nameToId.find(name);
 if (it != nameToId.end()) {
 return it->second;
 }
 
 // Load texture
 SDL_Texture* texture = texMgr->getTexture(texturePath);
 if (!texture) {
 std::cerr << "Failed to load tile texture: " << texturePath << '\n';
 return -1;
 }
 
 // Create tile definition
 TileDef tileDef;
 tileDef.name = name;
 tileDef.texture = texture;
 tileDef.srcRect.x = srcX;
 tileDef.srcRect.y = srcY;
 tileDef.srcRect.w = srcW;
 tileDef.srcRect.h = srcH;
 tileDef.id = nextId++;
 
 tileDefs.push_back(tileDef);
 nameToId[name] = tileDef.id;
 
 return tileDef.id;
}

const TileDef* TileRegistry::getTileDef(int id) const {
 if (id < 0 || id >= static_cast<int>(tileDefs.size())) {
 return nullptr;
 }
 return &tileDefs[id];
}

const TileDef* TileRegistry::getTileDefByName(const std::string& name) const {
 auto it = nameToId.find(name);
 if (it != nameToId.end()) {
 return getTileDef(it->second);
 }
 return nullptr;
}

int TileRegistry::getTileId(const std::string& name) const {
 auto it = nameToId.find(name);
 if (it != nameToId.end()) {
 return it->second;
 }
 return -1;
}

bool TileRegistry::loadTileDefinitions(const std::string& path) {
 // This would load from tiledefinitions.tiles
 // For now, we'll register some basic tiles manually
 // In a full implementation, this would parse the tile definition file
 
 // Example: Register some common floor tiles
 // These would come from parsing the actual tile definition files
 
 std::cout << "TileRegistry: Tile definitions would be loaded from " << path << '\n';
 
 return true;
}

void TileRegistry::clear() {
 tileDefs.clear();
 nameToId.clear();
 nextId = 0;
}

// LotLoader implementation

bool LotLoader::loadFromFile(const std::string& path, TileMap* tileMap,
 TileRegistry* registry) {
 if (!tileMap || !registry) {
 return false;
 }
 
 std::vector<std::string> tileNames;
 if (!parseLotFile(path, tileNames)) {
 std::cerr << "Failed to parse lot file: " << path << '\n';
 return false;
 }
 
 if (tileNames.empty()) {
 std::cerr << "No tiles found in lot file: " << path << '\n';
 return false;
 }
 
 // For now, we'll create a simple demo map
 // In a full implementation, we'd parse the actual lot format
 // which includes position data
 
 // Create a small demo map with the loaded tiles
 int mapSize = std::min(20, static_cast<int>(tileNames.size()));
 tileMap->setSize(mapSize, mapSize, 1);
 
 // Fill with tiles from the lot
 for (int y = 0; y < mapSize; y++) {
 for (int x = 0; x < mapSize; x++) {
 int tileIndex = (x + y) % tileNames.size();
 const std::string& tileName = tileNames[tileIndex];
 
 int tileId = registry->getTileId(tileName);
 if (tileId >= 0) {
 tileMap->setTile(x, y, 0, tileId);
 }
 }
 }
 
 std::cout << "Loaded lot with " << tileNames.size() << " tile types" << '\n';
 
 return true;
}

bool LotLoader::parseLotFile(const std::string& path,
 std::vector<std::string>& tileNames) {
 std::ifstream file(path);
 if (!file.is_open()) {
 return false;
 }
 
 std::string line;
 while (std::getline(file, line)) {
 // Skip empty lines and comments
 if (line.empty() || line[0] == '#') {
 continue;
 }
 
 // Trim whitespace
 size_t start = line.find_first_not_of(" \t\r\n");
 size_t end = line.find_last_not_of(" \t\r\n");
 
 if (start != std::string::npos && end != std::string::npos) {
 std::string tileName = line.substr(start, end - start + 1);
 
 // Skip 'b' prefix lines (they appear to be markers in the format)
 if (!tileName.empty() && tileName[0] != 'b') {
 tileNames.push_back(tileName);
 } else if (tileName.length() > 1 && tileName[0] == 'b') {
 // Add without 'b' prefix
 tileNames.push_back(tileName.substr(1));
 }
 }
 }
 
 file.close();
 
 // Remove duplicates
 std::sort(tileNames.begin(), tileNames.end());
 tileNames.erase(std::unique(tileNames.begin(), tileNames.end()), tileNames.end());
 
 return !tileNames.empty();
}

} // namespace world
} // namespace zombie
