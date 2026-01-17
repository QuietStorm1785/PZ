#include "GameWindow.h"
#include "Core.h"
#include "GameTime.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "SpriteBatch.h"
#include "SpriteAnimation.h"
#include "BitmapFont.h"
#include "TileMap.h"
#include "Entity.h"
#include "Player.h"
#include "IsoPlayer.h"
#include "IsoZombie.h"
#include "IsoCell.h"
#include "IsoGridSquare.h"
#include "Collision.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "NetworkManager.h"
#include "WorldLoader.h"
#include "VisibilitySystem.h"
#include "AudioInteractionSystem.h"
#include "PathfindingThreadPool.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <unordered_map>

// Example states (simplified)
#include "GameState.h"

namespace zombie {

// Example MainMenuState
class MainMenuState : public gameStates::GameState {
public:
    MainMenuState() : timer(0.0f) {}
    
    void enter() override {
        std::cout << "Entering Main Menu State" << std::endl;
        timer = 0.0f;
        
        // Create logo sprite
        auto* texMgr = assets::TextureManager::getInstance();
        SDL_Texture* logoTex = texMgr->getTexture("ui/LoneMan.png");
        
        if (logoTex) {
            logoSprite = std::make_unique<graphics::Sprite>(logoTex);
            
            // Scale down to half size
            logoSprite->setScale(0.5f, 0.5f);
            
            // Center on screen
            auto* core = core::Core::getInstance();
            int w, h;
            texMgr->getTextureSize("ui/LoneMan.png", &w, &h);
            float centerX = core->getScreenWidth() / 2.0f;
            float centerY = core->getScreenHeight() / 2.0f;
            
            // Set position with center origin
            logoSprite->setOrigin(0.5f, 0.5f);
            logoSprite->setPosition(centerX, centerY);
        }
    }
    
    void exit() override {
        std::cout << "Exiting Main Menu State" << std::endl;
        logoSprite.reset();
    }
    
    gameStates::StateAction update() override {
        auto* gt = GameTime::getInstance();
        gt->update(false);
        timer += gt->getDeltaTime();
        
        // Gentle rotation animation
        if (logoSprite) {
            logoSprite->setRotation(timer * 5.0f); // Slow rotation
        }
        
        // Auto-transition after 0.5 seconds (quick for testing)
        if (timer >= 0.5f) {
            return gameStates::StateAction::Continue;
        }
        
        return gameStates::StateAction::Remain;
    }
    
    void render() override {
        auto* core = core::Core::getInstance();
        
        // Draw gradient background using new primitive rendering
        core->drawFilledRect(0, 0, 
            static_cast<float>(core->getScreenWidth()), 
            static_cast<float>(core->getScreenHeight()), 
            32, 64, 128, 255);
        
        // Draw logo sprite
        if (logoSprite) {
            core->drawSprite(logoSprite.get());
        }
    }
    
private:
    float timer;
    std::unique_ptr<graphics::Sprite> logoSprite;
};

// Example IngameState (simplified)
class IngameState : public gameStates::GameState {
public:
    IngameState() 
        : mouseSprite(nullptr)
        , tileMap(nullptr)
        , tileRegistry(nullptr)
        , entityManager(nullptr)
        , collisionSystem(nullptr)
        , player(nullptr)
        , isoPlayer(nullptr)
        , isoCell(nullptr)
        , cameraX(0)
        , cameraY(0)
        , showDemo(0)
        , netSendTimer(0.0f)
        , zombieSendTimer(0.0f)
        , server(nullptr)
        , client(nullptr)
        , mediaChecked(false)
        , playerTex(nullptr)
        , zombieTex(nullptr)
        , visibilityChecker(nullptr)
        , fogSystem(nullptr)
    {}

    void setNetworking(network::NetworkServer* srv, network::NetworkClient* cli) {
        server = srv;
        client = cli;
    }

    void onRemotePlayerPosition(const network::Packet& packet) {
        uint32_t remoteId = 0;
        float x = 0.0f, y = 0.0f, z = 0.0f, rot = 0.0f;
        network::NetworkProtocol::parsePlayerPosition(packet, remoteId, x, y, z, rot);
        remotePlayers[remoteId] = {x, y};
    }

    void onRemoteZombiePosition(const network::Packet& packet) {
        network::Packet& p = const_cast<network::Packet&>(packet);
        p.resetRead();
        uint32_t zid = p.readUint32();
        float x = p.readFloat();
        float y = p.readFloat();
        float z = p.readFloat();
        (void)z; // currently unused
        remoteZombies[zid] = {x, y};
    }
    
    void enter() override {
        std::cout << "Entering Ingame State" << std::endl;

        remotePlayers.clear();
        remoteZombies.clear();
        
        auto* texMgr = assets::TextureManager::getInstance();
        auto* inputMgr = input::InputManager::getInstance();
        auto* soundMgr = audio::SoundManager::getInstance();
        
        // Initialize sound system
        soundMgr->init();
        soundMgr->setMediaPath("media/");
        
        // Create mouse cursor sprite
        SDL_Texture* mouseTex = texMgr->getTexture("ui/mouse.png");
        if (mouseTex) {
            mouseSprite = std::make_unique<graphics::Sprite>(mouseTex);
        }
        else {
            missingAssets.push_back("ui/mouse.png");
        }

        // Load character textures (placeholders from media/ui)
        playerTex = texMgr->getTexture("ui/LoneMan.png");
        if (!playerTex) {
            missingAssets.push_back("ui/LoneMan.png");
        }
        // Use mouse as a temporary zombie texture if no dedicated asset
        zombieTex = texMgr->getTexture("ui/Mouse.png");
        if (!zombieTex) {
            // Fallback to mouse.png
            zombieTex = texMgr->getTexture("ui/mouse.png");
            if (!zombieTex) {
                missingAssets.push_back("ui/Mouse.png");
                missingAssets.push_back("ui/mouse.png");
            }
        }
        
        // Initialize tile system demo
        tileRegistry = std::make_unique<world::TileRegistry>();
        tileRegistry->init(texMgr);
        
        // Register some demo tiles using available UI textures
        tileRegistry->registerTile("Ground", "ui/GroundTile.png", 0, 0, 64, 64);
        if (!texMgr->getTexture("ui/GroundTile.png")) {
            missingAssets.push_back("ui/GroundTile.png");
        }
        
        // Create a simple tile map
        tileMap = std::make_unique<world::TileMap>();
        tileMap->setSize(30, 30, 1);
        tileMap->setTileSize(32);
        
        // Fill with ground tiles in a pattern
        int groundTileId = tileRegistry->getTileId("Ground");
        if (groundTileId >= 0) {
            for (int y = 0; y < 30; y++) {
                for (int x = 0; x < 30; x++) {
                    if ((x + y) % 2 == 0) {
                        tileMap->setTile(x, y, 0, groundTileId);
                    }
                }
            }
        }
        
        // Initialize entity system
        entityManager = std::make_unique<entities::EntityManager>();
        
        // Create player with shared_ptr
        auto playerPtr = std::make_shared<entities::Player>();
        player = playerPtr.get();  // Keep raw pointer for compatibility
        playerPtr->setPosition(400, 300);
        playerPtr->setMoveSpeed(200.0f);
        entityManager->addEntity(playerPtr);
        
        // Spawn some zombies with shared_ptr
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distX(100, 700);
        std::uniform_real_distribution<float> distY(100, 500);
        
        for (int i = 0; i < 5; i++) {
            auto zombie = std::make_shared<entities::Zombie>();
            zombie->setPosition(distX(gen), distY(gen));
            zombie->setMoveSpeed(80.0f);
            zombie->setAggroRange(200.0f);
            entityManager->addEntity(zombie);
        }
        
        // Initialize collision system
        collisionSystem = std::make_unique<physics::CollisionSystem>();
        
        // === NEW: Initialize Isometric World System ===
        // Create the world (300x300 tiles, loads 4x4 chunks at ground level)
        isoCell = std::make_unique<IsoCell>(300, 300);
        
        // Create IsoPlayer with smart pointer (new character system)
        isoPlayer = std::make_shared<zombie::characters::IsoPlayer>();
        isoPlayer->setPosition(64.0f, 64.0f); // Start at tile (2, 2)
        isoPlayer->setHealth(100.0f);
        
        // Add player to world
        isoCell->addCharacter(isoPlayer);

        // Load simple world content from a demo .lot file (trees, furniture, containers)
        WorldLoader::loadLotFile("media/lots/demo_generated.lot", isoCell.get(), 0);
        
        // Initialize visibility and fog of war systems
        visibilityChecker = std::make_unique<::VisibilityChecker>();
        visibilityChecker->setWorld(isoCell.get());
        fogSystem = std::make_unique<::FogOfWarSystem>(300, 300, 8);  // 300x300 grid, 8 Z levels
        
        std::cout << "Visibility and fog of war systems initialized" << std::endl;
        
        // Initialize pathfinding thread pool with auto-detected thread count
        auto* pathfindingPool = ::PathfindingThreadPool::getInstance();
        int optimalThreads = PathfindingThreadPool::getOptimalThreadCount();
        pathfindingPool->initialize(optimalThreads);  // 0 = auto-detect
        std::cout << "Pathfinding thread pool initialized with " << optimalThreads << " workers" << std::endl;
 
        // Spawn IsoZombies around the player with smart pointers
        // Reuse existing random generator from above
        std::uniform_real_distribution<float> distOffsetX(-10.0f, 10.0f);
        std::uniform_real_distribution<float> distOffsetY(-10.0f, 10.0f);
        
        for (int i = 0; i < 8; i++) {
            auto zombie = std::make_shared<IsoZombie>();
            float zx = isoPlayer->getX() + distOffsetX(gen) + (i * 5.0f);
            float zy = isoPlayer->getY() + distOffsetY(gen);
            zombie->setX(zx);
            zombie->setY(zy);
            zombie->setZ(0.0f);
            zombie->setHealth(100.0f);
            zombie->setTarget(isoPlayer);
            zombie->setWorld(isoCell.get());
            
            // Add to world
            isoCell->addZombie(zombie);
            
            // Track in grid square
            IsoGridSquare* zombieSquare = isoCell->getGridSquare(
                static_cast<int>(zx),
                static_cast<int>(zy),
                0
            );
            if (zombieSquare) {
                zombieSquare->addZombie(zombie);
            }
        }
        
        std::cout << "Gameplay systems initialized" << std::endl;
        std::cout << "=== WORLD SYSTEM ACTIVE ===" << std::endl;
        std::cout << "IsoCell: 300x300 tiles (4x4 chunks loaded)" << std::endl;
        std::cout << "IsoPlayer: Position (" << isoPlayer->getX() << ", " << isoPlayer->getY() << ")" << std::endl;
        std::cout << "IsoZombies: 8 spawned" << std::endl;
        std::cout << "Controls:" << std::endl;
        std::cout << "  WASD - Move player" << std::endl;
        std::cout << "  Hold B - Run" << std::endl;
        std::cout << "  Arrow Keys - Pan camera" << std::endl;
        std::cout << "  ESC - Quit" << std::endl;

        // Final media check marker
        mediaChecked = true;
        if (!missingAssets.empty()) {
            std::cerr << "Missing media assets (" << missingAssets.size() << "):\n";
            for (const auto& a : missingAssets) {
                std::cerr << "  - " << a << "\n";
            }
        }
    }
    
    void exit() override {
        std::cout << "Exiting Ingame State" << std::endl;
        
        // All unique_ptr members are automatically cleaned up
        mouseSprite.reset();
        collisionSystem.reset();
        entityManager.reset();
        tileMap.reset();
        tileRegistry.reset();
        isoCell.reset();
        
        // isoPlayer is shared_ptr and will be automatically cleaned up
        isoPlayer.reset();
        
        player = nullptr; // Non-owning pointer
    }
    
    gameStates::StateAction update() override {
        auto* inputMgr = input::InputManager::getInstance();
        auto* gameTime = GameTime::getInstance();
        float deltaTime = gameTime->getDeltaTime();
        
        // Update input system
        inputMgr->update();
        
        // Update game logic
        GameTime::getInstance()->update(false);
        
        // Update mouse sprite position
        if (mouseSprite) {
            mouseSprite->setPosition(
                static_cast<float>(inputMgr->getMouseX()), 
                static_cast<float>(inputMgr->getMouseY())
            );
        }
        
        // === IsoPlayer Input (WASD + Gamepad) ===
        if (isoPlayer && isoPlayer->isAlive()) {
            // Handle input (IsoPlayer manages its own square updates)
            isoPlayer->handleInput(inputMgr);
            isoPlayer->update(deltaTime);

            // Broadcast position periodically when connected
            netSendTimer += deltaTime;
            if (client && client->isConnected() && netSendTimer >= 0.05f) {
                auto packet = network::NetworkProtocol::createPlayerPositionPacket(
                    client->getClientId(), isoPlayer->getX(), isoPlayer->getY(), 0.0f, 0.0f);
                client->sendPacket(*packet);
                netSendTimer = 0.0f;
            }
        }
        
        // Player input (WASD) - Legacy Player system
        if (player && player->isAlive()) {
            float moveX = 0.0f;
            float moveY = 0.0f;
            
            if (inputMgr->isKeyDown(SDL_SCANCODE_W)) moveY -= 1.0f;
            if (inputMgr->isKeyDown(SDL_SCANCODE_S)) moveY += 1.0f;
            if (inputMgr->isKeyDown(SDL_SCANCODE_A)) moveX -= 1.0f;
            if (inputMgr->isKeyDown(SDL_SCANCODE_D)) moveX += 1.0f;
            
            // Normalize diagonal movement
            if (moveX != 0.0f && moveY != 0.0f) {
                float length = std::sqrt(moveX * moveX + moveY * moveY);
                moveX /= length;
                moveY /= length;
            }
            
            player->setVelocity(
                moveX * player->getMoveSpeed(),
                moveY * player->getMoveSpeed()
            );
        }
        
        // Update all entities
        if (entityManager) {
            // Update zombies AI
            for (int i = 0; i < entityManager->getEntityCount(); i++) {
                auto entity = entityManager->getEntity(i);  // Returns shared_ptr
                auto zombie = std::dynamic_pointer_cast<entities::Zombie>(entity);
                if (zombie && player && player->isAlive()) {
                    zombie->setTarget(player->getX(), player->getY());
                }
            }
            
            entityManager->updateAll(deltaTime);
        }
        
        // Check collisions
        if (collisionSystem && entityManager && player) {
            // Check player vs zombies
            for (int i = 0; i < entityManager->getEntityCount(); i++) {
                auto entity = entityManager->getEntity(i);  // Returns shared_ptr
                auto zombie = std::dynamic_pointer_cast<entities::Zombie>(entity);
                if (zombie && zombie->isAlive() && player->isAlive()) {
                    float px, py, pw, ph;
                    float zx, zy, zw, zh;
                    player->getBounds(px, py, pw, ph);
                    zombie->getBounds(zx, zy, zw, zh);
                    
                    // Simple AABB collision
                    if (px < zx + zw && px + pw > zx &&
                        py < zy + zh && py + ph > zy) {
                        // Zombie damages player on contact
                        player->setHealth(player->getHealth() - 0.5f * deltaTime);
                    }
                }
            }
        }
        
        // === Update IsoZombies (World System) ===
        if (isoCell) {
            // Update world (updates all chunks and squares)
            isoCell->update();
            
            // Update all zombies
            const auto& zombies = isoCell->getZombies();
            for (const auto& zombie : zombies) {  // Returns shared_ptr
                if (zombie && zombie->isAlive()) {
                    // Store old position for grid tracking
                    int oldX = static_cast<int>(zombie->getX());
                    int oldY = static_cast<int>(zombie->getY());
                    
                    // Update zombie AI and movement
                    zombie->update(deltaTime);
                    
                    // Check if zombie moved to new grid square
                    int newX = static_cast<int>(zombie->getX());
                    int newY = static_cast<int>(zombie->getY());
                    
                    if (oldX != newX || oldY != newY) {
                        // Remove from old square
                        IsoGridSquare* oldSquare = isoCell->getGridSquare(oldX, oldY, 0);
                        if (oldSquare) {
                            oldSquare->removeZombie(zombie);
                        }
                        
                        // Add to new square
                        IsoGridSquare* newSquare = isoCell->getGridSquare(newX, newY, 0);
                        if (newSquare) {
                            newSquare->addZombie(zombie);
                        }
                    }
                }
            }

            // Broadcast zombie positions periodically
            zombieSendTimer += deltaTime;
            if (client && client->isConnected() && zombieSendTimer >= 0.1f) {
                for (size_t i = 0; i < zombies.size(); ++i) {
                    const auto& z = zombies[i];
                    if (z && z->isAlive()) {
                        auto pkt = network::NetworkProtocol::createZombiePositionPacket(
                            static_cast<uint32_t>(i), z->getX(), z->getY(), z->getZ());
                        client->sendPacket(*pkt);
                    }
                }
                zombieSendTimer = 0.0f;
            }
            
            // Update fog of war based on player visibility
            if (fogSystem && isoPlayer && isoPlayer->isAlive()) {
                float visionRadius = 15.0f;  // Player can see 15 tiles in all directions
                fogSystem->updateVisibility(isoPlayer->getX(), isoPlayer->getY(), 
                                          0, visionRadius);  // Z=0 for ground level
            }
            
            // Periodic pathfinding maintenance (every frame is fine, it's lightweight)
            static float cleanupTimer = 0.0f;
            cleanupTimer += deltaTime;
            if (cleanupTimer >= 5.0f) {  // Every 5 seconds
                auto* pathfindingPool = ::PathfindingThreadPool::getInstance();
                pathfindingPool->clearOldRequests(10.0f);  // Clear requests older than 10s
                
                // Monitor queue health
                if (!pathfindingPool->isQueueHealthy()) {
                    std::cout << "WARNING: Pathfinding queue bottleneck detected! "
                              << "Pending requests: " << pathfindingPool->getPendingRequestCount() 
                              << std::endl;
                }
                
                cleanupTimer = 0.0f;
            }
        }
        
        // Camera control with arrow keys
        const int cameraSpeed = 3;
        if (inputMgr->isKeyDown(SDL_SCANCODE_LEFT)) cameraX -= cameraSpeed;
        if (inputMgr->isKeyDown(SDL_SCANCODE_RIGHT)) cameraX += cameraSpeed;
        if (inputMgr->isKeyDown(SDL_SCANCODE_UP)) cameraY -= cameraSpeed;
        if (inputMgr->isKeyDown(SDL_SCANCODE_DOWN)) cameraY += cameraSpeed;
        
        // Clamp camera
        cameraX = std::max(0, std::min(cameraX, 30 * 32 - 800));
        cameraY = std::max(0, std::min(cameraY, 30 * 32 - 600));
        
        // Follow player with camera (optional - comment out if you want manual camera)
        if (player) {
            cameraX = static_cast<int>(player->getX() - 400);
            cameraY = static_cast<int>(player->getY() - 300);
            cameraX = std::max(0, std::min(cameraX, 30 * 32 - 800));
            cameraY = std::max(0, std::min(cameraY, 30 * 32 - 600));
        }
        
        // Always remain in game state
        return gameStates::StateAction::Remain;
    }
    
    void render() override {
        auto* core = core::Core::getInstance();
        auto* gameTime = GameTime::getInstance();
        auto* renderer = core->getRenderer();
        
        // Calculate background color based on time of day
        float nightTint = gameTime->getNightTint();
        Uint8 skyR = static_cast<Uint8>(64 + nightTint * 100);
        Uint8 skyG = static_cast<Uint8>(128 + nightTint * 100);
        Uint8 skyB = static_cast<Uint8>(192 + nightTint * 63);
        
        // Draw sky background
        core->drawFilledRect(0, 0,
            static_cast<float>(core->getScreenWidth()),
            static_cast<float>(core->getScreenHeight()),
            skyR, skyG, skyB, 255);
        
        // Draw tile map
        if (tileMap && tileRegistry) {
            tileMap->render(renderer, tileRegistry.get(), 
                          cameraX, cameraY,
                          core->getScreenWidth(), 
                          core->getScreenHeight());
        }
        
        // === Render IsoPlayer (World System) ===
        if (isoPlayer && isoPlayer->isAlive()) {
            float posX = isoPlayer->getX();
            float posY = isoPlayer->getY();
            
            // Draw texture if available, else fallback square
            if (playerTex) {
                core->drawTexture(playerTex, posX - cameraX - 18, posY - cameraY - 18, 36, 36);
            } else {
                core->drawFilledRect(
                    posX - cameraX - 18, 
                    posY - cameraY - 18, 
                    36, 36, 
                    0, 100, 255, 255
                );
            }
            
            // Health bar
            int healthBarWidth = static_cast<int>(36 * (isoPlayer->getHealth() / 100.0f));
            core->drawFilledRect(
                posX - cameraX - 18, 
                posY - cameraY - 26, 
                healthBarWidth, 5, 
                0, 255, 0, 255
            );
            
            // Stamina bar (below health)
            int staminaBarWidth = static_cast<int>(36 * (isoPlayer->getStamina() / 100.0f));
            core->drawFilledRect(
                posX - cameraX - 18, 
                posY - cameraY - 20, 
                staminaBarWidth, 3, 
                255, 255, 0, 255
            );
        }

        // Render remote players (if any)
        for (const auto& kv : remotePlayers) {
            float posX = kv.second.x;
            float posY = kv.second.y;
            if (playerTex) {
                core->drawTexture(playerTex, posX - cameraX - 14, posY - cameraY - 14, 28, 28);
            } else {
                core->drawFilledRect(
                    posX - cameraX - 14,
                    posY - cameraY - 14,
                    28, 28,
                    0, 200, 120, 220
                );
            }
        }
        
        // === Render IsoZombies (World System) ===
        if (isoCell) {
            const auto& zombies = isoCell->getZombies();
            for (const auto& zombie : zombies) {  // Returns shared_ptr
                if (zombie && zombie->isAlive()) {
                    float posX = zombie->getX();
                    float posY = zombie->getY();
                    
                    // Draw zombie as red/pink square
                    Uint8 zombieR = 255;
                    Uint8 zombieG = 50;
                    Uint8 zombieB = 50;
                    
                    // Different colors based on state
                    switch (zombie->getState()) {
                        case IsoZombie::ZombieState::IDLE:
                            zombieG = 100; // Lighter red when idle
                            break;
                        case IsoZombie::ZombieState::WANDER:
                            zombieG = 80;
                            zombieB = 80; // More purple when wandering
                            break;
                        case IsoZombie::ZombieState::CHASE:
                            zombieR = 255; // Bright red when chasing
                            zombieG = 0;
                            zombieB = 0;
                            break;
                        case IsoZombie::ZombieState::ATTACK:
                            zombieR = 200; // Dark red pulsing when attacking
                            zombieG = 0;
                            zombieB = 0;
                            break;
                    }
                    
                    if (zombieTex) {
                        core->drawTexture(zombieTex, posX - cameraX - 14, posY - cameraY - 14, 28, 28);
                    } else {
                        core->drawFilledRect(
                            posX - cameraX - 14, 
                            posY - cameraY - 14, 
                            28, 28, 
                            zombieR, zombieG, zombieB, 255
                        );
                    }
                    
                    // Health bar
                    int healthBarWidth = static_cast<int>(28 * (zombie->getHealth() / 100.0f));
                    core->drawFilledRect(
                        posX - cameraX - 14, 
                        posY - cameraY - 22, 
                        healthBarWidth, 4, 
                        255, 0, 0, 255
                    );
                    
                    // Draw sight range circle (debug visualization)
                    // core->drawCircle(posX - cameraX, posY - cameraY, 
                    //                 zombie->getSightRange(), 255, 100, 100, 128);
                }
            }

            // Render remote zombies (networked)
            for (const auto& kv : remoteZombies) {
                float posX = kv.second.x;
                float posY = kv.second.y;
                if (zombieTex) {
                    core->drawTexture(zombieTex, posX - cameraX - 12, posY - cameraY - 12, 24, 24);
                } else {
                    core->drawFilledRect(
                        posX - cameraX - 12,
                        posY - cameraY - 12,
                        24, 24,
                        180, 90, 255, 220
                    );
                }
            }
        }
        
        // Render all entities (with camera offset) - Legacy system
        if (entityManager) {
            for (int i = 0; i < entityManager->getEntityCount(); i++) {
                auto entity = entityManager->getEntity(i);  // Returns shared_ptr
                if (entity) {
                    float posX = entity->getX();
                    float posY = entity->getY();
                    
                    // Create temporary sprite for visual representation
                    // (In real game, entities would have their own sprites)
                    if (auto playerEntity = std::dynamic_pointer_cast<entities::Player>(entity)) {
                        // Draw player as green circle
                        if (playerEntity->isAlive()) {
                            core->drawFilledRect(
                                posX - cameraX - 16, 
                                posY - cameraY - 16, 
                                32, 32, 
                                0, 255, 0, 255
                            );
                        } else {
                            core->drawFilledRect(
                                posX - cameraX - 16, 
                                posY - cameraY - 16, 
                                32, 32, 
                                128, 128, 128, 255
                            );
                        }
                        
                        // Health bar
                        int healthBarWidth = static_cast<int>(32 * (playerEntity->getHealth() / playerEntity->getMaxHealth()));
                        core->drawFilledRect(
                            posX - cameraX - 16, 
                            posY - cameraY - 24, 
                            healthBarWidth, 4, 
                            255, 0, 0, 255
                        );
                    } else if (auto zombie = std::dynamic_pointer_cast<entities::Zombie>(entity)) {
                        // Draw zombie as red circle
                        if (zombie->isAlive()) {
                            core->drawFilledRect(
                                posX - cameraX - 12, 
                                posY - cameraY - 12, 
                                24, 24, 
                                255, 0, 0, 255
                            );
                            
                            // Health bar
                            int healthBarWidth = static_cast<int>(24 * (zombie->getHealth() / zombie->getMaxHealth()));
                            core->drawFilledRect(
                                posX - cameraX - 12, 
                                posY - cameraY - 20, 
                                healthBarWidth, 3, 
                                255, 100, 100, 255
                            );
                        }
                    }
                }
            }
        }
        
        // === Render Fog of War Overlay ===
        if (fogSystem && tileMap) {
            int tileSize = tileMap->getTileSize();  // Usually 32 pixels
            int tilesX = (core->getScreenWidth() / tileSize) + 2;
            int tilesY = (core->getScreenHeight() / tileSize) + 2;
            
            int startTileX = cameraX / tileSize;
            int startTileY = cameraY / tileSize;
            
            for (int ty = 0; ty < tilesY; ty++) {
                for (int tx = 0; tx < tilesX; tx++) {
                    int worldX = startTileX + tx;
                    int worldY = startTileY + ty;
                    
                    auto fogState = fogSystem->getFogState(worldX, worldY, 0);  // Z=0 for ground level
                    
                    if (fogState == FogOfWarSystem::FogState::UNEXPLORED) {
                        // Completely black (unexplored)
                        int screenX = worldX * tileSize - cameraX;
                        int screenY = worldY * tileSize - cameraY;
                        core->drawFilledRect(
                            static_cast<float>(screenX),
                            static_cast<float>(screenY),
                            static_cast<float>(tileSize),
                            static_cast<float>(tileSize),
                            0, 0, 0, 255  // Solid black
                        );
                    } else if (fogState == FogOfWarSystem::FogState::EXPLORED) {
                        // Semi-transparent gray overlay (explored but not visible)
                        int screenX = worldX * tileSize - cameraX;
                        int screenY = worldY * tileSize - cameraY;
                        core->drawFilledRect(
                            static_cast<float>(screenX),
                            static_cast<float>(screenY),
                            static_cast<float>(tileSize),
                            static_cast<float>(tileSize),
                            0, 0, 0, 128  // 50% transparent black
                        );
                    }
                    // VISIBLE tiles get no overlay (rendered normally)
                }
            }
        }
        
        // Draw UI overlay
        core->drawFilledRect(0, 0, 
            static_cast<float>(core->getScreenWidth()), 100, 
            0, 0, 0, 180);
        
        // Draw time of day indicator bar
        float timePercent = gameTime->getTimeOfDay() / 24.0f;
        int barWidth = static_cast<int>(200 * timePercent);
        core->drawFilledRect(10, 10, static_cast<float>(barWidth), 30, 255, 255, 0, 255);
        core->drawRect(10, 10, 200, 30, 255, 255, 255, 255);
        
        // === IsoPlayer Status (World System) ===
        if (isoPlayer) {
            core->drawFilledRect(10, 50, 300, 40, 40, 40, 40, 200);
            
            // Health bar (red)
            int playerHealthWidth = static_cast<int>(290 * (isoPlayer->getHealth() / 100.0f));
            core->drawFilledRect(15, 55, playerHealthWidth, 12, 255, 0, 0, 255);
            core->drawRect(15, 55, 290, 12, 255, 255, 255, 255);
            
            // Stamina bar (yellow)
            int staminaWidth = static_cast<int>(290 * (isoPlayer->getStamina() / 100.0f));
            core->drawFilledRect(15, 70, staminaWidth, 8, 255, 255, 0, 255);
            core->drawRect(15, 70, 290, 8, 255, 255, 255, 255);
            
            // Status indicator
            if (!isoPlayer->isAlive()) {
                core->drawFilledRect(320, 50, 80, 40, 128, 0, 0, 255);
            } else if (isoPlayer->isRunning()) {
                core->drawFilledRect(320, 50, 80, 40, 255, 165, 0, 255); // Orange = running
            } else {
                core->drawFilledRect(320, 50, 80, 40, 0, 128, 0, 255); // Green = normal
            }
        }
        
        // Legacy player status
        if (player) {
            core->drawFilledRect(10, 50, 300, 25, 40, 40, 40, 200);
            
            // Health bar
            int playerHealthWidth = static_cast<int>(290 * (player->getHealth() / player->getMaxHealth()));
            core->drawFilledRect(15, 55, playerHealthWidth, 15, 255, 0, 0, 255);
            core->drawRect(15, 55, 290, 15, 255, 255, 255, 255);
            
            // Status indicator
            if (!player->isAlive()) {
                core->drawFilledRect(320, 50, 80, 25, 128, 0, 0, 255);
            } else {
                core->drawFilledRect(320, 50, 80, 25, 0, 128, 0, 255);
            }
        }
        
        // === IsoZombie Count (World System) ===
        if (isoCell) {
            int aliveIsoZombies = 0;
            const auto& zombies = isoCell->getZombies();
            for (const auto& zombie : zombies) {  // Returns shared_ptr
                if (zombie && zombie->isAlive()) {
                    aliveIsoZombies++;
                }
            }
            
            // Draw IsoZombie count indicator (below legacy zombies)
            core->drawFilledRect(420, 10, 180, 30, 40, 40, 40, 200);
            core->drawRect(420, 10, 180, 30, 255, 100, 100, 255);
            
            for (int i = 0; i < aliveIsoZombies && i < 12; i++) {
                // Use different colors based on state of first few zombies
                Uint8 r = 255, g = 50, b = 50;
                if (i < static_cast<int>(zombies.size())) {
                    const auto& z = zombies[i];  // Returns shared_ptr
                    if (z->getState() == IsoZombie::ZombieState::CHASE ||
                        z->getState() == IsoZombie::ZombieState::ATTACK) {
                        r = 255; g = 0; b = 0; // Bright red for aggressive
                    }
                }
                core->drawFilledRect(425 + i * 14, 15, 12, 20, r, g, b, 255);
            }
        }
        
        // Entity count - Legacy system
        if (entityManager) {
            int aliveZombies = 0;
            for (int i = 0; i < entityManager->getEntityCount(); i++) {
                auto entity = entityManager->getEntity(i);  // Returns shared_ptr
                auto zombie = std::dynamic_pointer_cast<entities::Zombie>(entity);
                if (zombie && zombie->isAlive()) {
                    aliveZombies++;
                }
            }
            
            // Draw zombie count indicator
            core->drawFilledRect(420, 50, 150, 25, 40, 40, 40, 200);
            for (int i = 0; i < aliveZombies && i < 10; i++) {
                core->drawFilledRect(425 + i * 14, 55, 12, 15, 255, 50, 50, 255);
            }
        }
        
        // Draw mouse cursor sprite
        if (mouseSprite) {
            core->drawSprite(mouseSprite.get());
        }

        // Debug overlay: center crosshair to verify rendering
        float cx = core->getScreenWidth() / 2.0f;
        float cy = core->getScreenHeight() / 2.0f;
        core->drawFilledRect(cx - 2, cy - 20, 4, 40, 255, 255, 255, 255);
        core->drawFilledRect(cx - 20, cy - 2, 40, 4, 255, 255, 255, 255);

        // Media check overlay (red banner + exclamation mark)
        if (mediaChecked && !missingAssets.empty()) {
            // Red banner at top
            core->drawFilledRect(0, 0, static_cast<float>(core->getScreenWidth()), 40,
                                 200, 0, 0, 200);
            core->drawRect(0, 0, core->getScreenWidth(), 40, 255, 255, 255, 255);
            // Exclamation mark on left
            core->drawFilledRect(10, 8, 8, 22, 255, 255, 255, 255);
            core->drawFilledRect(10, 32, 8, 6, 255, 255, 255, 255);
            // Simple indicator boxes for each missing asset
            int x = 30;
            int idx = 0;
            for (size_t i = 0; i < missingAssets.size() && i < 10; ++i) {
                core->drawFilledRect(x + idx * 16, 12, 12, 16, 255, 180, 180, 255);
                idx++;
            }
        }
    }
    
private:
    std::unique_ptr<graphics::Sprite> mouseSprite;
    std::unique_ptr<world::TileMap> tileMap;
    std::unique_ptr<world::TileRegistry> tileRegistry;
    std::unique_ptr<entities::EntityManager> entityManager;
    std::unique_ptr<physics::CollisionSystem> collisionSystem;
    entities::Player* player;  // Non-owning pointer (owned by EntityManager)
    std::shared_ptr<zombie::characters::IsoPlayer> isoPlayer;
    std::unique_ptr<IsoCell> isoCell;
    int cameraX, cameraY;
    int showDemo;
    float netSendTimer;
    float zombieSendTimer;
    network::NetworkServer* server;
    network::NetworkClient* client;
    std::unordered_map<uint32_t, SDL_FPoint> remotePlayers;
    std::unordered_map<uint32_t, SDL_FPoint> remoteZombies;
    bool mediaChecked;
    SDL_Texture* playerTex;
    SDL_Texture* zombieTex;
    std::vector<std::string> missingAssets;
    
    // Visibility and fog of war systems
    std::unique_ptr<::VisibilityChecker> visibilityChecker;
    std::unique_ptr<::FogOfWarSystem> fogSystem;
};

GameWindow::GameWindow()
    : stateMachine()
    , networkServer(nullptr)
    , networkClient(nullptr)
    , ingameState(nullptr)
    , networkReady(false)
    , lastFrame(0)
    , lastFPS(0)
    , average10FPS(60.0f)
    , last10Index(0)
    , last(0)
    , closeRequested(false)
    , initialized(false)
{
    for (int i = 0; i < 100; i++) {
        last10[i] = 60.0f;
    }
}

GameWindow::~GameWindow() {
    // Cleanup handled by shutdown
}

bool GameWindow::init(int width, int height, bool fullscreen) {
    std::cout << "Project Zomboid C++ Port v" << VERSION << std::endl;
    
    // Initialize core graphics
    if (!core::Core::getInstance()->init(width, height, "Project Zomboid")) {
        std::cerr << "Failed to initialize Core" << std::endl;
        return false;
    }
    
    // Initialize texture manager with media assets
    if (!assets::TextureManager::getInstance()->init(core::Core::getInstance()->getRenderer())) {
        std::cerr << "Failed to initialize TextureManager" << std::endl;
        return false;
    }
    
    // Set media path (relative to build directory)
    assets::TextureManager::getInstance()->setMediaPath("media/");
    
    // Initialize timing
    lastFrame = SDL_GetTicks64();
    lastFPS = lastFrame;
    last = lastFrame;
    
    // Setup states
    initStates();

    // Initialize networking (optional)
    networkReady = initNetworking();
    if (!networkReady) {
        std::cerr << "Networking initialization failed; continuing offline" << std::endl;
    }
    
    initialized = true;
    std::cout << "GameWindow initialized successfully" << std::endl;
    std::cout << "Media path: " << assets::TextureManager::getInstance()->getMediaPath() << std::endl;
    return true;
}

void GameWindow::initStates() {
    // Add game states
    auto mainMenu = std::make_unique<MainMenuState>();
    auto ingame = std::make_unique<IngameState>();
    ingameState = ingame.get();
    stateMachine.addState(std::move(mainMenu));
    stateMachine.addState(std::move(ingame));
    
    // Loop back to main menu if we exit all states
    stateMachine.setLooping(true);
    stateMachine.setLoopToState(1); // Loop to ingame (skip menu after first time)
}

bool GameWindow::initNetworking() {
    using namespace network;

    networkServer = std::make_unique<NetworkServer>();
    networkClient = std::make_unique<NetworkClient>();

    const uint16_t port = 7777;

    // Start server
    if (!networkServer->start(port)) {
        std::cerr << "Failed to start local server on port " << port << std::endl;
        return false;
    }

    // Server rebroadcasts player positions to other clients
    networkServer->registerPacketHandler(PacketType::PLAYER_POSITION,
        [this](const Packet& packet, NetworkPeer* peer) {
            if (networkServer) {
                networkServer->broadcastPacket(packet, peer);
            }
        });

    // Server rebroadcasts zombie positions
    networkServer->registerPacketHandler(PacketType::ZOMBIE_POSITION,
        [this](const Packet& packet, NetworkPeer* peer) {
            if (networkServer) {
                networkServer->broadcastPacket(packet, peer);
            }
        });

    // Server rebroadcasts chat
    networkServer->registerPacketHandler(PacketType::CHAT_MESSAGE,
        [this](const Packet& packet, NetworkPeer* peer) {
            if (networkServer) {
                networkServer->broadcastPacket(packet, peer);
            }
        });

    // Client handler: record remote player positions
    networkClient->registerPacketHandler(PacketType::PLAYER_POSITION,
        [this](const Packet& packet, NetworkPeer*) {
            if (ingameState) {
                ingameState->onRemotePlayerPosition(packet);
            }
        });

    // Client handler: record remote zombie positions
    networkClient->registerPacketHandler(PacketType::ZOMBIE_POSITION,
        [this](const Packet& packet, NetworkPeer*) {
            if (ingameState) {
                ingameState->onRemoteZombiePosition(packet);
            }
        });

    // Client handler: log chat messages
    networkClient->registerPacketHandler(PacketType::CHAT_MESSAGE,
        [](const Packet& packet, NetworkPeer*) {
            Packet& p = const_cast<Packet&>(packet);
            p.resetRead();
            uint32_t sender = p.readUint32();
            std::string msg = p.readString();
            std::cout << "[CHAT] (" << sender << ") " << msg << std::endl;
        });

    // Connect to local server
    if (!networkClient->connect("127.0.0.1", port, "Player")) {
        std::cerr << "Failed to connect to local server" << std::endl;
        return false;
    }

    // Announce join
    if (networkClient->isConnected()) {
        auto chat = NetworkProtocol::createChatMessagePacket(networkClient->getClientId(), "Player connected");
        networkClient->sendPacket(*chat);
    }

    // Wire networking into ingame state
    if (ingameState) {
        ingameState->setNetworking(networkServer.get(), networkClient.get());
    }

    std::cout << "Networking ready on port " << port << " (local host)" << std::endl;
    return true;
}

void GameWindow::run() {
    if (!initialized) {
        std::cerr << "Cannot run - not initialized" << std::endl;
        return;
    }
    
    std::cout << "Starting main game loop..." << std::endl;
    
    SDL_Event event;
    auto* inputMgr = input::InputManager::getInstance();
    
    // Main game loop
    while (!closeRequested) {
        Uint64 frameStart = SDL_GetTicks64();
        
        // Process events
        while (SDL_PollEvent(&event)) {
            // Pass event to input manager
            inputMgr->processEvent(event);
            
            if (event.type == SDL_QUIT) {
                closeRequested = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    closeRequested = true;
                }
            } else if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    core::Core::getInstance()->setScreenSize(
                        event.window.data1,
                        event.window.data2
                    );
                }
            }
        }
        
        // Update game logic
        logic();
        
        // Render frame
        render();
        
        // Update FPS
        updateFPS();
        
        // Frame timing (cap at 60 FPS if no vsync)
        Uint64 frameEnd = SDL_GetTicks64();
        Uint64 frameDuration = frameEnd - frameStart;
        
        if (frameDuration < FRAME_TIME) {
            SDL_Delay(static_cast<Uint32>(FRAME_TIME - frameDuration));
        }
    }
    
    std::cout << "Exiting game loop" << std::endl;
}

void GameWindow::logic() {
    // Update state machine
    stateMachine.update();

    // Network tick using latest delta time
    float deltaTime = GameTime::getInstance()->getDeltaTime();
    if (networkReady && networkServer) {
        networkServer->update(deltaTime);
    }
    if (networkReady && networkClient) {
        networkClient->update(deltaTime);
    }
}

void GameWindow::render() {
    auto* core = core::Core::getInstance();
    
    // Start rendering
    core->startFrame();
    
    // Render current state
    stateMachine.render();
    
    core->endFrame();
    
    // Render UI
    core->startFrameUI();
    
    // TODO: Render UI elements here
    
    core->endFrameUI();
}

Uint64 GameWindow::getTime() {
    return SDL_GetTicks64();
}

void GameWindow::updateFPS() {
    Uint64 now = getTime();
    Uint64 diff = now - last;
    last = now;
    
    // Calculate instantaneous FPS
    float fps = (diff > 0) ? (1000.0f / static_cast<float>(diff)) : 60.0f;
    
    // Store in rolling average
    last10[last10Index++] = fps;
    if (last10Index >= 100) {
        last10Index = 0;
    }
    
    // Calculate average
    float sum = 0.0f;
    int count = 0;
    for (int i = 0; i < 10; i++) {
        if (last10[i] > 1.0f) {
            sum += last10[i];
            count++;
        }
    }
    
    if (count > 0) {
        average10FPS = sum / count;
    } else {
        average10FPS = 60.0f;
    }
    
    // Update FPS multiplier for game time
    GameTime::getInstance()->setFPSMultiplier(60.0f / average10FPS);
    
    // Print FPS every second (debug)
    if (now - lastFPS > 1000) {
        std::cout << "FPS: " << average10FPS << std::endl;
        lastFPS = now;
    }
}

} // namespace zombie
