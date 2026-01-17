#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

namespace zombie {

// Forward declarations
namespace graphics { class Sprite; }

namespace core {

/**
 * Core graphics and rendering system
 * Converted from zombie.core.Core
 */
class Core {
public:
    static Core* getInstance();
    
    Core();
    ~Core();
    
    // Initialize the graphics system
    bool init(int width, int height, const char* title);
    void shutdown();
    
    // Frame management
    void startFrame();
    void endFrame();
    void startFrameUI();
    void endFrameUI();
    
    // Screen management
    void setScreenSize(int w, int h);
    int getScreenWidth() const { return width; }
    int getScreenHeight() const { return height; }
    int getOffscreenWidth() const { return offscreenWidth; }
    int getOffscreenHeight() const { return offscreenHeight; }
    
    // Render target management
    SDL_Renderer* getRenderer() const { return renderer; }
    SDL_Window* getWindow() const { return window; }
    
    // Sprite rendering
    void drawSprite(graphics::Sprite* sprite);
    void drawTexture(SDL_Texture* texture, float x, float y);
    void drawTexture(SDL_Texture* texture, float x, float y, float width, float height);
    void drawTexture(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect);
    
    // Primitive rendering
    void drawRect(float x, float y, float width, float height, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
    void drawFilledRect(float x, float y, float width, float height, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
    void drawLine(float x1, float y1, float x2, float y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
    
    // Graphics settings
    void setGraphicLevel(int level) { graphicLevel = level; }
    int getGraphicLevel() const { return graphicLevel; }
    
    // Debug
    static bool bDebug;
    
private:
    static Core* instance;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    int width;
    int height;
    int offscreenWidth;
    int offscreenHeight;
    
    int graphicLevel;
    bool useShaders;
};

} // namespace core
} // namespace zombie
