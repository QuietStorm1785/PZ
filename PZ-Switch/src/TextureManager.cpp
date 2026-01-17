#include "TextureManager.h"
#include "SpriteAnimation.h"
#include "TextureAtlas.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace zombie {
namespace assets {

TextureManager* TextureManager::instance = nullptr;

TextureManager* TextureManager::getInstance() {
    if (!instance) {
        instance = new TextureManager();
    }
    return instance;
}

TextureManager::TextureManager()
    : renderer(nullptr)
    , mediaPath("../media/") // Default relative to build directory
{
}

TextureManager::~TextureManager() {
    shutdown();
}

bool TextureManager::init(SDL_Renderer* r) {
    if (!r) {
        std::cerr << "TextureManager: Invalid renderer" << std::endl;
        return false;
    }
    
    renderer = r;
    
    // Initialize SDL_image for PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image init failed: " << IMG_GetError() << std::endl;
        return false;
    }
    
    std::cout << "TextureManager initialized with media path: " << mediaPath << std::endl;
    return true;
}

void TextureManager::shutdown() {
    clearCache();
    IMG_Quit();
    renderer = nullptr;
}

SDL_Texture* TextureManager::loadTexture(const std::string& path) {
    // Check cache first
    auto it = textureCache.find(path);
    if (it != textureCache.end()) {
        return it->second;
    }
    
    // Build full path
    std::string fullPath = mediaPath + path;
    
    // Load from file
    SDL_Texture* texture = loadFromFile(fullPath);
    
    if (texture) {
        textureCache[path] = texture;
        std::cout << "Loaded texture: " << path << std::endl;
    }
    
    return texture;
}

SDL_Texture* TextureManager::getTexture(const std::string& path) {
    auto it = textureCache.find(path);
    if (it != textureCache.end()) {
        return it->second;
    }
    
    // Try to load if not cached
    return loadTexture(path);
}

bool TextureManager::getTextureSize(const std::string& path, int* w, int* h) {
    SDL_Texture* tex = getTexture(path);
    if (!tex) {
        return false;
    }
    
    return SDL_QueryTexture(tex, nullptr, nullptr, w, h) == 0;
}

void TextureManager::clearCache() {
    for (auto& pair : textureCache) {
        if (pair.second) {
            SDL_DestroyTexture(pair.second);
        }
    }
    textureCache.clear();
    
    // Clean up atlases
    for (auto& pair : atlasCache) {
        delete pair.second;
    }
    atlasCache.clear();
}

SDL_Texture* TextureManager::loadFromFile(const std::string& fullPath) {
    if (!renderer) {
        std::cerr << "TextureManager: No renderer set" << std::endl;
        return nullptr;
    }
    
    // Load image
    SDL_Surface* surface = IMG_Load(fullPath.c_str());
    if (!surface) {
        std::cerr << "Failed to load image: " << fullPath << " - " << IMG_GetError() << std::endl;
        return nullptr;
    }
    
    // Create texture from surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    if (!texture) {
        std::cerr << "Failed to create texture: " << fullPath << " - " << SDL_GetError() << std::endl;
        return nullptr;
    }
    
    return texture;
}

zombie::graphics::AnimatedSprite* TextureManager::loadAnimatedSprite(const std::string& baseName) {
    if (!renderer) {
        std::cerr << "TextureManager: No renderer set" << std::endl;
        return nullptr;
    }
    
    // Load texture
    std::string pngPath = baseName + ".png";
    SDL_Texture* texture = loadTexture(pngPath);
    if (!texture) {
        std::cerr << "Failed to load texture: " << pngPath << std::endl;
        return nullptr;
    }
    
    // Create animated sprite
    auto* sprite = new zombie::graphics::AnimatedSprite(texture);
    
    // Parse animation definitions from .txt file
    std::string txtPath = mediaPath + baseName + ".txt";
    std::unordered_map<std::string, zombie::graphics::Animation> animations;
    
    if (parseAnimationFile(txtPath, animations)) {
        // Add all animations to sprite
        for (const auto& pair : animations) {
            sprite->addAnimation(pair.first, pair.second);
        }
        std::cout << "Loaded animated sprite: " << baseName << " (" 
                  << animations.size() << " animations)" << std::endl;
    } else {
        std::cerr << "Warning: No animation file found for " << baseName << std::endl;
    }
    
    return sprite;
}

bool TextureManager::parseAnimationFile(const std::string& txtPath,
                                        std::unordered_map<std::string, zombie::graphics::Animation>& animations) {
    std::ifstream file(txtPath);
    if (!file.is_open()) {
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) continue;
        
        // Parse line format: "AnimName_Frame = x y w h offsetX offsetY origW origH"
        size_t equalsPos = line.find('=');
        if (equalsPos == std::string::npos) continue;
        
        std::string frameName = line.substr(0, equalsPos);
        std::string frameData = line.substr(equalsPos + 1);
        
        // Trim whitespace
        frameName.erase(0, frameName.find_first_not_of(" \t"));
        frameName.erase(frameName.find_last_not_of(" \t") + 1);
        frameData.erase(0, frameData.find_first_not_of(" \t"));
        
        // Extract animation name (everything before last underscore + number)
        size_t lastUnderscorePos = frameName.find_last_of('_');
        if (lastUnderscorePos == std::string::npos) continue;
        
        std::string animName = frameName.substr(0, lastUnderscorePos);
        
        // Parse frame data: x y width height offsetX offsetY originalWidth originalHeight
        std::istringstream iss(frameData);
        int x, y, w, h, offsetX, offsetY, origW, origH;
        if (!(iss >> x >> y >> w >> h >> offsetX >> offsetY >> origW >> origH)) {
            continue; // Invalid format
        }
        
        // Create or get animation
        if (animations.find(animName) == animations.end()) {
            animations[animName] = zombie::graphics::Animation(animName);
            animations[animName].setLoop(true);
            animations[animName].setFrameDuration(0.1f); // 10 FPS default
        }
        
        // Add frame to animation
        zombie::graphics::AnimationFrame frame;
        frame.x = x;
        frame.y = y;
        frame.width = w;
        frame.height = h;
        frame.offsetX = offsetX;
        frame.offsetY = offsetY;
        frame.originalWidth = origW;
        frame.originalHeight = origH;
        frame.duration = 0.1f; // 10 FPS
        
        animations[animName].addFrame(frame);
    }
    
    file.close();
    return !animations.empty();
}

TextureAtlas* TextureManager::createAtlas(const std::string& name,
                                         const std::vector<std::string>& spritePaths,
                                         int maxWidth, int maxHeight) {
    // Check if already cached
    auto it = atlasCache.find(name);
    if (it != atlasCache.end()) {
        return it->second;
    }
    
    if (!renderer) {
        std::cerr << "TextureManager: No renderer for atlas creation" << std::endl;
        return nullptr;
    }
    
    // Create atlas builder
    TextureAtlas::Config config;
    config.maxWidth = maxWidth;
    config.maxHeight = maxHeight;
    config.padding = 2;  // 2 pixel padding to prevent bleeding
    config.powerOfTwo = true;
    
    TextureAtlas* atlas = new TextureAtlas(renderer, config);
    
    // Add all sprites to atlas
    for (const auto& path : spritePaths) {
        std::string fullPath = mediaPath + path;
        
        // Load surface for packing
        SDL_Surface* surface = IMG_Load(fullPath.c_str());
        if (surface) {
            atlas->addSprite(path, surface);
            SDL_FreeSurface(surface);
        } else {
            std::cerr << "Failed to load sprite for atlas: " << path << std::endl;
        }
    }
    
    // Build atlas
    if (atlas->build()) {
        atlasCache[name] = atlas;
        std::cout << "Created atlas '" << name << "' with " 
                  << spritePaths.size() << " sprites" << std::endl;
        return atlas;
    }
    
    delete atlas;
    return nullptr;
}

TextureAtlas* TextureManager::getAtlas(const std::string& name) {
    auto it = atlasCache.find(name);
    if (it != atlasCache.end()) {
        return it->second;
    }
    return nullptr;
}

zombie::graphics::AnimatedSprite* TextureManager::loadCharacterSpriteSheet(
    const std::string& characterName,
    const std::string& outfit) {
    
    // Character sprite sheets follow PZ naming convention:
    // media/textures/[Outfit]_[Action]_[Direction].png
    // e.g., "Bob_Walk_S.png", "Kate_Run_NE.png"
    
    std::vector<std::string> actions = {"Idle", "Walk", "Run"};
    std::vector<std::string> directions = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};
    
    // Load first texture to create sprite
    std::string firstTexPath = "textures/" + outfit + "_Idle_S.png";
    SDL_Texture* baseTexture = loadTexture(firstTexPath);
    
    if (!baseTexture) {
        std::cerr << "Failed to load character base texture: " << firstTexPath << std::endl;
        return nullptr;
    }
    
    auto* animSprite = new zombie::graphics::AnimatedSprite(baseTexture);
    
    // Load all animation combinations
    for (const auto& action : actions) {
        for (const auto& dir : directions) {
            std::string animName = action + "_" + dir;
            std::string texPath = "textures/" + outfit + "_" + action + "_" + dir;
            
            // Try to load animation from .txt file
            std::string txtPath = mediaPath + texPath + ".txt";
            std::string pngPath = "textures/" + outfit + "_" + action + "_" + dir + ".png";
            
            // Check if animation file exists
            std::ifstream file(txtPath);
            if (file.good()) {
                file.close();
                
                // Parse animation file
                std::unordered_map<std::string, zombie::graphics::Animation> anims;
                if (parseAnimationFile(txtPath, anims)) {
                    // Add all animations from file
                    for (auto& [name, anim] : anims) {
                        animSprite->addAnimation(animName, anim);
                    }
                }
            } else {
                // Create simple single-frame animation
                SDL_Texture* tex = loadTexture(pngPath);
                if (tex) {
                    zombie::graphics::Animation anim(animName);
                    
                    int w, h;
                    SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
                    
                    zombie::graphics::AnimationFrame frame;
                    frame.x = 0;
                    frame.y = 0;
                    frame.width = w;
                    frame.height = h;
                    frame.originalWidth = w;
                    frame.originalHeight = h;
                    frame.duration = 100.0f;  // 100ms default
                    anim.addFrame(frame);
                    anim.setLoop(true);
                    
                    animSprite->addAnimation(animName, anim);
                }
            }
        }
    }
    
    // Set default animation
    animSprite->setAnimation("Idle_S");
    animSprite->play();
    
    std::cout << "Loaded character sprite sheet: " << outfit << std::endl;
    return animSprite;
}

SDL_Texture* TextureManager::loadTileTexture(const std::string& tileName) {
    // Tile textures are in media/textures/tiles/
    std::string tilePath = "textures/tiles/" + tileName + ".png";
    
    SDL_Texture* tex = loadTexture(tilePath);
    if (!tex) {
        std::cerr << "Failed to load tile texture: " << tileName << std::endl;
        // Create fallback colored texture
        SDL_Surface* surface = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0);
        if (surface) {
            SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 100, 100, 100));
            tex = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
        }
    }
    
    return tex;
}

SDL_Texture* TextureManager::loadObjectTexture(const std::string& objectName) {
    // Object textures are in media/textures/objects/
    std::string objPath = "textures/objects/" + objectName + ".png";
    
    SDL_Texture* tex = loadTexture(objPath);
    if (!tex) {
        std::cerr << "Failed to load object texture: " << objectName << std::endl;
        // Create fallback colored texture
        SDL_Surface* surface = SDL_CreateRGBSurface(0, 64, 64, 32, 0, 0, 0, 0);
        if (surface) {
            SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 150, 100, 50));
            tex = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
        }
    }
    
    return tex;
}

TextureAtlas* TextureManager::createCharacterAtlas(
    const std::string& characterName,
    const std::string& outfit) {
    
    std::string atlasName = "character_" + outfit;
    
    // Check if already exists
    TextureAtlas* existing = getAtlas(atlasName);
    if (existing) {
        return existing;
    }
    
    // Collect all character sprite paths
    std::vector<std::string> spritePaths;
    std::vector<std::string> actions = {"Idle", "Walk", "Run", "Attack", "Death"};
    std::vector<std::string> directions = {"N", "NE", "E", "SE", "S", "SW", "W", "NW"};
    
    for (const auto& action : actions) {
        for (const auto& dir : directions) {
            std::string path = "textures/" + outfit + "_" + action + "_" + dir + ".png";
            spritePaths.push_back(path);
        }
    }
    
    // Create atlas (2048x2048 for character animations)
    TextureAtlas* atlas = createAtlas(atlasName, spritePaths, 2048, 2048);
    
    if (atlas) {
        std::cout << "Created character atlas for: " << outfit << std::endl;
    }
    
    return atlas;
}

TextureAtlas* TextureManager::createTileAtlas(
    const std::vector<std::string>& tileNames) {
    
    std::string atlasName = "tiles_common";
    
    // Check if already exists
    TextureAtlas* existing = getAtlas(atlasName);
    if (existing) {
        return existing;
    }
    
    // Build tile paths
    std::vector<std::string> tilePaths;
    for (const auto& tileName : tileNames) {
        tilePaths.push_back("textures/tiles/" + tileName + ".png");
    }
    
    // Create atlas (4096x4096 for many tiles)
    TextureAtlas* atlas = createAtlas(atlasName, tilePaths, 4096, 4096);
    
    if (atlas) {
        std::cout << "Created tile atlas with " << tileNames.size() << " tiles" << std::endl;
    }
    
    return atlas;
}

} // namespace assets
} // namespace zombie
