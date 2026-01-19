#include "Core.h"
#include "Sprite.h"
#include <SDL2/SDL.h>
#include <iostream>

namespace zombie {
namespace core {

Core* Core::instance = nullptr;
bool Core::bDebug = false;

Core* Core::getInstance() {
 if (!instance) {
 instance = new Core();
 }
 return instance;
}

Core::Core()
 : window(nullptr)
 , renderer(nullptr)
 , width(800)
 , height(600)
 , offscreenWidth(800)
 , offscreenHeight(600)
 , graphicLevel(5)
 , useShaders(true)
 , vsyncEnabled(true)
{
}

Core::~Core() {
 shutdown();
}

bool Core::init(int w, int h, const char* title) {
 width = w;
 height = h;
 offscreenWidth = w;
 offscreenHeight = h;
 
 // Initialize SDL video subsystem
 if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0) {
 std::cerr << "SDL initialization failed: " << SDL_GetError() << '\n';
 return false;
 }
 
 // Create window
 Uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
 window = SDL_CreateWindow(
 title,
 SDL_WINDOWPOS_CENTERED,
 SDL_WINDOWPOS_CENTERED,
 width,
 height,
 windowFlags
 );
 
 if (!window) {
 std::cerr << "Window creation failed: " << SDL_GetError() << '\n';
 return false;
 }
 
 // Create renderer (hardware accelerated)
 renderer = SDL_CreateRenderer(
 window,
 -1,
 SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
 );
 
 if (!renderer) {
 std::cerr << "Renderer creation failed: " << SDL_GetError() << '\n';
 return false;
 }
 
 // Set blend mode for transparency
 SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

 // Apply initial vsync state (may disable if configured off)
 setVSyncEnabled(vsyncEnabled);
 
 std::cout << "Core initialized: " << width << "x" << height << '\n';
 return true;
}

void Core::shutdown() {
 if (renderer) {
 SDL_DestroyRenderer(renderer);
 renderer = nullptr;
 }
 
 if (window) {
 SDL_DestroyWindow(window);
 window = nullptr;
 }
 
 SDL_Quit();
}

void Core::startFrame() {
 // Clear the screen
 SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
 SDL_RenderClear(renderer);
}

void Core::endFrame() {
 // Present will be called after UI rendering
}

void Core::startFrameUI() {
 // UI rendering setup
 // In the original, this switches to UI rendering mode
}

void Core::endFrameUI() {
 // Present the rendered frame
 SDL_RenderPresent(renderer);
}

void Core::setScreenSize(int w, int h) {
 if (w != width || h != height) {
 width = w;
 height = h;
 offscreenWidth = w;
 offscreenHeight = h;
 
 // Handle window resize
 if (window) {
 SDL_SetWindowSize(window, width, height);
 }
 }
}

// Sprite rendering methods

void Core::drawSprite(graphics::Sprite* sprite) {
 if (!sprite) return;
 sprite->render(renderer);
}

void Core::drawTexture(SDL_Texture* texture, float x, float y) {
 if (!texture) return;
 
 int w, h;
 SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
 
 SDL_Rect dstRect;
 dstRect.x = static_cast<int>(x);
 dstRect.y = static_cast<int>(y);
 dstRect.w = w;
 dstRect.h = h;
 
 SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

void Core::drawTexture(SDL_Texture* texture, float x, float y, float w, float h) {
 if (!texture) return;
 
 SDL_Rect dstRect;
 dstRect.x = static_cast<int>(x);
 dstRect.y = static_cast<int>(y);
 dstRect.w = static_cast<int>(w);
 dstRect.h = static_cast<int>(h);
 
 SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

void Core::drawTexture(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect) {
 if (!texture) return;
 SDL_RenderCopy(renderer, texture, srcRect, dstRect);
}

// Primitive rendering methods

void Core::drawRect(float x, float y, float w, float h, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
 SDL_SetRenderDrawColor(renderer, r, g, b, a);
 SDL_Rect rect;
 rect.x = static_cast<int>(x);
 rect.y = static_cast<int>(y);
 rect.w = static_cast<int>(w);
 rect.h = static_cast<int>(h);
 SDL_RenderDrawRect(renderer, &rect);
}

void Core::drawFilledRect(float x, float y, float w, float h, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
 SDL_SetRenderDrawColor(renderer, r, g, b, a);
 SDL_Rect rect;
 rect.x = static_cast<int>(x);
 rect.y = static_cast<int>(y);
 rect.w = static_cast<int>(w);
 rect.h = static_cast<int>(h);
 SDL_RenderFillRect(renderer, &rect);
}

void Core::drawLine(float x1, float y1, float x2, float y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
 SDL_SetRenderDrawColor(renderer, r, g, b, a);
 SDL_RenderDrawLine(renderer, 
 static_cast<int>(x1), static_cast<int>(y1),
 static_cast<int>(x2), static_cast<int>(y2));
}

bool Core::setVSyncEnabled(bool enabled) {
 vsyncEnabled = enabled;

#if SDL_VERSION_ATLEAST(2,0,18)
 if (renderer) {
 if (SDL_RenderSetVSync(renderer, enabled ? 1 : 0) != 0) {
 std::cerr << "SDL_RenderSetVSync failed: " << SDL_GetError() << '\n';
 return false;
 }
 }
#endif
 return true;
}

} // namespace core
} // namespace zombie
