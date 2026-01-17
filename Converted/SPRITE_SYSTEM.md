# Sprite System Usage Guide

## Overview

The sprite rendering system provides a complete 2D graphics framework with support for:
- Sprite transformations (position, rotation, scale)
- Color modulation and alpha blending
- Sprite sheet support via source rectangles
- Efficient batch rendering
- Primitive shape rendering

## Quick Start

### Basic Sprite Rendering

```cpp
#include "Core.h"
#include "TextureManager.h"
#include "Sprite.h"

using namespace zombie;

// Load a texture
auto* texMgr = assets::TextureManager::getInstance();
SDL_Texture* texture = texMgr->loadTexture("ui/player.png");

// Create a sprite
graphics::Sprite sprite(texture);
sprite.setPosition(100, 200);      // Position on screen
sprite.setScale(2.0f, 2.0f);       // Scale to 2x size
sprite.setRotation(45.0f);         // Rotate 45 degrees
sprite.setAlpha(200);              // Semi-transparent

// Render it
auto* core = core::Core::getInstance();
core->drawSprite(&sprite);
```

### Using SpriteBatch for Performance

```cpp
#include "SpriteBatch.h"

graphics::SpriteBatch batch;
batch.init(core->getRenderer());

// Begin batch
batch.begin();

// Add multiple sprites (will be automatically sorted by texture)
batch.draw(&sprite1);
batch.draw(&sprite2);
batch.draw(&sprite3);

// Flush to screen (minimizes texture switches)
batch.end();

// Check performance stats
std::cout << "Draw calls: " << batch.getDrawCallCount() << std::endl;
std::cout << "Sprites: " << batch.getSpriteCount() << std::endl;
```

### Sprite Properties

```cpp
// Position
sprite.setPosition(x, y);
float x = sprite.getX();
float y = sprite.getY();

// Size
sprite.setSize(width, height);
float w = sprite.getWidth();
float h = sprite.getHeight();

// Scale (multiplies size)
sprite.setScale(scaleX, scaleY);

// Rotation (in degrees)
sprite.setRotation(angle);

// Origin/Pivot point (normalized 0-1)
sprite.setOrigin(0.5f, 0.5f);  // Center pivot
sprite.setOrigin(0.0f, 0.0f);  // Top-left pivot (default)
sprite.setOrigin(1.0f, 1.0f);  // Bottom-right pivot

// Color modulation
sprite.setColor(255, 128, 0);  // Orange tint
sprite.setAlpha(128);          // 50% transparent

// Flip
sprite.setFlipHorizontal(true);
sprite.setFlipVertical(false);
```

### Using Sprite Sheets

```cpp
// Load a sprite sheet
SDL_Texture* sheet = texMgr->loadTexture("sprites/characters.png");

// Create sprite and set source rectangle
graphics::Sprite sprite(sheet);
sprite.setSourceRect(0, 0, 32, 32);  // Top-left 32x32 region
sprite.setPosition(100, 100);

// Animate by changing source rect
int frame = 0;
sprite.setSourceRect(frame * 32, 0, 32, 32);
```

### Primitive Rendering

```cpp
auto* core = core::Core::getInstance();

// Filled rectangle
core->drawFilledRect(x, y, width, height, r, g, b, a);

// Outline rectangle
core->drawRect(x, y, width, height, r, g, b, a);

// Line
core->drawLine(x1, y1, x2, y2, r, g, b, a);
```

### Direct Texture Rendering

```cpp
auto* core = core::Core::getInstance();
SDL_Texture* tex = texMgr->getTexture("ui/icon.png");

// Simple draw at position
core->drawTexture(tex, x, y);

// Draw with size
core->drawTexture(tex, x, y, width, height);

// Draw with source and destination rects
SDL_Rect src = {0, 0, 32, 32};
SDL_Rect dst = {x, y, 64, 64};
core->drawTexture(tex, &src, &dst);
```

## Best Practices

1. **Reuse Sprites**: Create sprites once and update their properties each frame
2. **Use SpriteBatch**: For rendering many sprites, batch them to reduce draw calls
3. **Texture Caching**: TextureManager automatically caches, so getTexture() is fast
4. **Proper Cleanup**: Delete sprites in state exit() methods to avoid memory leaks
5. **Origin Points**: Set origin to (0.5, 0.5) for rotation around center

## Example: Animated Character

```cpp
class Character {
private:
    graphics::Sprite sprite;
    int currentFrame;
    float frameTime;
    
public:
    Character() : currentFrame(0), frameTime(0) {
        auto* texMgr = assets::TextureManager::getInstance();
        SDL_Texture* tex = texMgr->loadTexture("sprites/player_walk.png");
        sprite.setTexture(tex);
        sprite.setOrigin(0.5f, 1.0f);  // Center bottom (for ground alignment)
    }
    
    void update(float deltaTime) {
        frameTime += deltaTime;
        
        // Animate at 10 FPS
        if (frameTime >= 0.1f) {
            frameTime = 0;
            currentFrame = (currentFrame + 1) % 8;  // 8 frames
            sprite.setSourceRect(currentFrame * 32, 0, 32, 32);
        }
    }
    
    void render(core::Core* core) {
        core->drawSprite(&sprite);
    }
    
    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }
};
```

## Performance Tips

- **Batch Similar Sprites**: SpriteBatch sorts by texture to minimize state changes
- **Pre-allocate**: SpriteBatch pre-allocates space for 1000 sprites
- **Texture Atlases**: Combine multiple sprites into one texture for better batching
- **Minimize Rotation**: Rotated sprites are slightly slower to render
- **Alpha Blending**: Fully opaque sprites (alpha=255) render faster

## Implementation Details

- **Sprite**: 495 lines of code (84 header + 158 implementation)
- **SpriteBatch**: 253 lines of code (62 header + 191 implementation)
- **Memory**: Sprites are lightweight (~100 bytes each)
- **Rendering**: Uses SDL2's hardware-accelerated rendering
