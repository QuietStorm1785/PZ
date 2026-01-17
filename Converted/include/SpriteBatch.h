#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "Sprite.h"

namespace zombie {
namespace graphics {

/**
 * SpriteBatch - Efficient batch rendering of sprites
 * Groups draw calls to minimize state changes
 */
class SpriteBatch {
public:
    SpriteBatch();
    ~SpriteBatch();
    
    // Initialize with renderer
    void init(SDL_Renderer* renderer);
    
    // Begin/end batch
    void begin();
    void end();
    
    // Add sprites to batch
    void draw(Sprite* sprite);
    void draw(SDL_Texture* texture, float x, float y);
    void draw(SDL_Texture* texture, float x, float y, float width, float height);
    void draw(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect, 
              float rotation = 0.0f, const SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    // Flush current batch to screen
    void flush();
    
    // Stats
    int getDrawCallCount() const { return drawCallCount; }
    int getSpriteCount() const { return spriteCount; }
    void resetStats();
    
private:
    struct BatchItem {
        SDL_Texture* texture;
        SDL_Rect srcRect;
        SDL_Rect dstRect;
        float rotation;
        SDL_Point center;
        SDL_RendererFlip flip;
        Uint8 r, g, b, a;
        bool hasSourceRect;
    };
    
    SDL_Renderer* renderer;
    std::vector<BatchItem> batch;
    bool isDrawing;
    
    // Stats
    int drawCallCount;
    int spriteCount;
};

} // namespace graphics
} // namespace zombie
