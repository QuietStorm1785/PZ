#include "IsometricRenderer.h"
#include "IsoPlayer.h"
#include "IsoObject.h"
#include "SpriteBatch.h"
#include <algorithm>
#include <cmath>

using namespace zombie::graphics;
using namespace zombie::animation;
using namespace std;

// ===== IsometricRenderer =====

IsometricRenderer::IsometricRenderer(SDL_Renderer* renderer)
 : renderer(renderer) {
}

IsometricRenderer::~IsometricRenderer() = default;

void IsometricRenderer::worldToScreen(float worldX, float worldY, int z,
 float& screenX, float& screenY) {
 // Isometric projection formula
 const float TILE_WIDTH = 32.0f;
 const float TILE_HEIGHT = 16.0f;
 const float Z_HEIGHT = 8.0f;
 
 screenX = (worldX - worldY) * (TILE_WIDTH / 2.0f);
 screenY = (worldX + worldY) * (TILE_HEIGHT / 2.0f) + z * Z_HEIGHT;
}

void IsometricRenderer::screenToWorld(float screenX, float screenY, float cameraX, float cameraY,
 float& worldX, float& worldY) {
 // Inverse isometric projection (approximate, for click detection)
 const float TILE_WIDTH = 32.0f;
 const float TILE_HEIGHT = 16.0f;
 
 // Add camera offset
 float camScreenX = screenX + cameraX;
 float camScreenY = screenY + cameraY;
 
 // Inverse formula (approximate)
 worldX = (camScreenX / (TILE_WIDTH / 2.0f) + camScreenY / (TILE_HEIGHT / 2.0f)) / 2.0f;
 worldY = (camScreenY / (TILE_HEIGHT / 2.0f) - camScreenX / (TILE_WIDTH / 2.0f)) / 2.0f;
}

void IsometricRenderer::renderPlayer(zombie::characters::IsoPlayer* player, const zombie::graphics::Sprite* sprite,
 float cameraX, float cameraY, zombie::graphics::SpriteBatch* batch) {
 if (!player || !sprite || !batch) return;

 float screenX, screenY;
 // IsoPlayer doesn't have getZ, so use 0
 worldToScreen(player->getX(), player->getY(), 0, screenX, screenY);
 
 // Apply camera offset
 screenX -= cameraX;
 screenY -= cameraY;

 // Render using sprite batch
 auto spriteCopy = std::make_unique<Sprite>(*sprite);
 spriteCopy->setPosition(screenX, screenY);
 batch->draw(spriteCopy.get());
 
 lastStats.spritesRendered++;
}

void IsometricRenderer::renderObject(IsoObject* obj, const zombie::graphics::Sprite* sprite,
 float cameraX, float cameraY, zombie::graphics::SpriteBatch* batch) {
 if (!obj || !sprite || !batch) return;

 float screenX, screenY;
 worldToScreen(obj->getX(), obj->getY(), obj->getZ(), screenX, screenY);
 
 // Apply camera offset
 screenX -= cameraX;
 screenY -= cameraY;

 // Render using sprite batch
 auto spriteCopy = std::make_unique<Sprite>(*sprite);
 spriteCopy->setPosition(screenX, screenY);
 batch->draw(spriteCopy.get());
 
 lastStats.spritesRendered++;
}

void IsometricRenderer::renderEntities(const std::vector<RenderEntity>& entities,
 float cameraX, float cameraY, zombie::graphics::SpriteBatch* batch) {
 if (!batch) return;

 // Sort entities by depth (isometric Y-order)
 std::vector<RenderEntity> sortedEntities = entities;
 std::sort(sortedEntities.begin(), sortedEntities.end(),
 [](const RenderEntity& a, const RenderEntity& b) {
 // Sort by Y first (top to bottom), then Z
 if (a.worldY != b.worldY) {
 return a.worldY < b.worldY;
 }
 return a.z < b.z;
 });

 // Render in sorted order
 for (const auto& entity : sortedEntities) {
 if (!entity.sprite) continue;

 float screenX, screenY;
 worldToScreen(entity.worldX, entity.worldY, entity.z, screenX, screenY);
 
 // Apply camera offset
 screenX -= cameraX;
 screenY -= cameraY;

 // Create sprite copy and set position
 auto spriteCopy = std::make_unique<Sprite>(*entity.sprite);
 spriteCopy->setPosition(screenX, screenY);
 
 // Apply animation frame if available (simplified - SpriteAnimation doesn't have frame info)
 // This would need to be expanded with actual animation controller
 
 batch->draw(spriteCopy.get());
 lastStats.spritesRendered++;
 }

 lastStats.entitiesRendered = sortedEntities.size();
}

void IsometricRenderer::updateAnimation(zombie::animation::SpriteAnimation* anim, float deltaTime) {
 (void)deltaTime;
 if (!anim) return;
 // SpriteAnimation doesn't have an update method in current implementation
}

void IsometricRenderer::renderCollisionDebug(float worldX, float worldY, int z,
 float width, float height,
 float cameraX, float cameraY,
 SDL_Renderer* renderer, Uint8 alpha) {
 float screenX, screenY;
 worldToScreen(worldX, worldY, z, screenX, screenY);
 
 // Apply camera offset
 screenX -= cameraX;
 screenY -= cameraY;

 // Draw bounding box
 SDL_SetRenderDrawColor(renderer, 0, 255, 0, alpha);
 SDL_Rect rect = {
 (int)screenX,
 (int)screenY,
 (int)width,
 (int)height
 };
 SDL_RenderDrawRect(renderer, &rect);
}

void IsometricRenderer::getSpriteBounds(const zombie::graphics::Sprite* sprite,
 float& width, float& height) {
 if (!sprite) {
 width = 0;
 height = 0;
 return;
 }
 
 width = sprite->getWidth();
 height = sprite->getHeight();
}

// ===== SpriteManager =====

SpriteManager::SpriteManager(SDL_Renderer* renderer)
 : renderer(renderer) {
}

SpriteManager::~SpriteManager() = default;

std::shared_ptr<zombie::graphics::Sprite> SpriteManager::createSprite(SDL_Texture* texture) {
 return std::make_shared<Sprite>(texture);
}

std::shared_ptr<zombie::animation::SpriteAnimation> SpriteManager::createAnimation(
 const std::string& name, SDL_Texture* texture,
 int frameWidth, int frameHeight, int frameCount, float frameDuration) {
 (void)frameDuration;
 
 auto anim = std::make_shared<zombie::animation::SpriteAnimation>(name, frameWidth, frameHeight);
 anim->setGridSize((texture != nullptr) ? frameCount : 1, 1);
 
 animations[name] = anim;
 
 return anim;
}

std::shared_ptr<zombie::animation::SpriteAnimation> SpriteManager::getAnimation(const std::string& name) {
 auto it = animations.find(name);
 if (it != animations.end()) {
 return it->second;
 }
 return nullptr;
}

std::shared_ptr<zombie::animation::SpriteAnimation> SpriteManager::getCharacterAnimation(
 CharacterAnimation anim, const std::string& characterType) {
 
 std::string animName = characterType + "_";
 
 switch (anim) {
 case CharacterAnimation::IDLE:
 animName += "idle";
 break;
 case CharacterAnimation::WALK_N:
 animName += "walk_n";
 break;
 case CharacterAnimation::WALK_S:
 animName += "walk_s";
 break;
 case CharacterAnimation::WALK_E:
 animName += "walk_e";
 break;
 case CharacterAnimation::WALK_W:
 animName += "walk_w";
 break;
 case CharacterAnimation::RUN:
 animName += "run";
 break;
 case CharacterAnimation::ATTACK:
 animName += "attack";
 break;
 case CharacterAnimation::HIT:
 animName += "hit";
 break;
 case CharacterAnimation::DEAD:
 animName += "dead";
 break;
 }
 
 return getAnimation(animName);
}
