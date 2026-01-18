#pragma once
#include <SDL2/SDL.h>
#include <string>

namespace zombie {

// Forward declarations
namespace assets { struct AtlasRegion; }

namespace graphics {

/**
 * Sprite - Represents a drawable 2D image
 * Handles position, rotation, scale, and texture reference
 */
class Sprite {
public:
    Sprite();
    Sprite(SDL_Texture* texture);
    ~Sprite();
    
    // Texture management
    void setTexture(SDL_Texture* tex);
    SDL_Texture* getTexture() const { return texture; }
    
    // Position and dimensions
    void setPosition(float x, float y);
    void setSize(float w, float h);
    void setScale(float sx, float sy);
    void setRotation(float angle); // In degrees
    
    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    float getScaleX() const { return scaleX; }
    float getScaleY() const { return scaleY; }
    float getRotation() const { return rotation; }
    
    // Color modulation and alpha
    void setColor(Uint8 r, Uint8 g, Uint8 b);
    void setAlpha(Uint8 a);
    void getColor(Uint8* r, Uint8* g, Uint8* b) const;
    Uint8 getAlpha() const { return alpha; }
    
    // Source rectangle (for sprite sheets)
    void setSourceRect(int sx, int sy, int sw, int sh);
    void clearSourceRect();
    bool hasSourceRect() const { return useSourceRect; }
    const SDL_Rect& getSourceRect() const { return sourceRect; }
    
    // Atlas support
    void setAtlasRegion(const assets::AtlasRegion* region);
    bool isFromAtlas() const { return fromAtlas; }
    const assets::AtlasRegion* getAtlasRegion() const { return atlasRegion; }
    
    // Origin/pivot point (normalized 0-1, default 0,0 = top-left)
    void setOrigin(float ox, float oy);
    float getOriginX() const { return originX; }
    float getOriginY() const { return originY; }
    
    // Flip
    void setFlipHorizontal(bool flip) { flipH = flip; }
    void setFlipVertical(bool flip) { flipV = flip; }
    bool isFlippedHorizontal() const { return flipH; }
    bool isFlippedVertical() const { return flipV; }
    
    // Render the sprite
    void render(SDL_Renderer* renderer);
    
private:
    SDL_Texture* texture;
    
    // Transform
    float x, y;
    float width, height;
    float scaleX, scaleY;
    float rotation; // degrees
    float originX, originY; // normalized pivot point
    
    // Color modulation
    Uint8 red, green, blue, alpha;
    
    // Source rectangle for sprite sheets
    bool useSourceRect;
    SDL_Rect sourceRect;
    
    // Flip flags
    bool flipH, flipV;
    
    // Atlas support
    bool fromAtlas;
    const assets::AtlasRegion* atlasRegion;
};

} // namespace graphics
} // namespace zombie
