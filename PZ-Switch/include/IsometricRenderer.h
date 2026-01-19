#pragma once
#include <SDL2/SDL.h>
#include "Sprite.h"
#include "SpriteBatch.h"
#include "SpriteAnimation.h"
#include "Animation.h"
#include "ChunkRenderer.h"
#include <memory>
#include <vector>
#include <map>

namespace zombie {
namespace characters {
class IsoPlayer;
}
}

class IsoObject;

/**
 * IsometricRenderer - Renders sprites in isometric projection
 * 
 * Converts screen-space sprite rendering to isometric game world
 * Handles character animation, object graphics, and z-ordering
 */
class IsometricRenderer {
public:
 explicit IsometricRenderer(SDL_Renderer* renderer);
 ~IsometricRenderer();

 // Coordinate conversion
 static void worldToScreen(float worldX, float worldY, int z,
 float& screenX, float& screenY);
 static void screenToWorld(float screenX, float screenY, float cameraX, float cameraY,
 float& worldX, float& worldY);
 
 // Render player character
 void renderPlayer(zombie::characters::IsoPlayer* player, const zombie::graphics::Sprite* sprite,
 float cameraX, float cameraY, zombie::graphics::SpriteBatch* batch);
 
 // Render game object
 void renderObject(IsoObject* obj, const zombie::graphics::Sprite* sprite,
 float cameraX, float cameraY, zombie::graphics::SpriteBatch* batch);
 
 // Render multiple entities with sorting
 struct RenderEntity {
 float worldX, worldY;
 int z;
 const zombie::graphics::Sprite* sprite;
 const zombie::animation::SpriteAnimation* animation;
 float animationTime;
 bool isPlayer;
 };
 
 void renderEntities(const std::vector<RenderEntity>& entities,
 float cameraX, float cameraY, zombie::graphics::SpriteBatch* batch);

 // Animation management
 void updateAnimation(zombie::animation::SpriteAnimation* anim, float deltaTime);

 // Collision rendering (debug mode)
 void renderCollisionDebug(float worldX, float worldY, int z,
 float width, float height,
 float cameraX, float cameraY,
 SDL_Renderer* renderer, Uint8 alpha = 128);

 // Statistics
 struct Stats {
 int spritesRendered = 0;
 int entitiesRendered = 0;
 float lastRenderTime = 0.0f;
 };
 const Stats& getStats() const { return lastStats; }

private:
 SDL_Renderer* renderer;
 mutable Stats lastStats;

 // Helper: Get sprite dimensions
 void getSpriteBounds(const zombie::graphics::Sprite* sprite,
 float& width, float& height);
};

/**
 * SpriteManager - Manages sprite assets and animations
 */
class SpriteManager {
public:
 explicit SpriteManager(SDL_Renderer* renderer);
 ~SpriteManager();

 // Load sprite from texture
 std::shared_ptr<zombie::graphics::Sprite> createSprite(SDL_Texture* texture);
 
 // Create animation from sprite sheet
 std::shared_ptr<zombie::animation::SpriteAnimation> createAnimation(
 std::string_view name, SDL_Texture* texture,
 int frameWidth, int frameHeight, int frameCount, float frameDuration);

 // Get animation by name
 std::shared_ptr<zombie::animation::SpriteAnimation> getAnimation(std::string_view name);

 // Preset animations
 enum class CharacterAnimation {
 IDLE = 0,
 WALK_N,
 WALK_S,
 WALK_E,
 WALK_W,
 RUN,
 ATTACK,
 HIT,
 DEAD
 };

 // Get or create character animation
 std::shared_ptr<zombie::animation::SpriteAnimation> getCharacterAnimation(
 CharacterAnimation anim, std::string_view characterType = "default");

private:
 SDL_Renderer* renderer;
 std::map<std::string, std::shared_ptr<zombie::animation::SpriteAnimation>> animations;
};
