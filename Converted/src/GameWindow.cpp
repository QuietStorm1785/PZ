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
#include "Collision.h"
#include "InputManager.h"
#include "SoundManager.h"
#include <iostream>
#include <algorithm>
#include <random>

// Example states (simplified)
#include "GameState.h"

namespace zombie {

// Example MainMenuState
class MainMenuState : public gameStates::GameState {
public:
    MainMenuState() : timer(0.0f), logoSprite(nullptr) {}
    
    void enter() override {
        std::cout << "Entering Main Menu State" << std::endl;
        timer = 0.0f;
        
        // Create logo sprite
        auto* texMgr = assets::TextureManager::getInstance();
        SDL_Texture* logoTex = texMgr->getTexture("ui/LoneMan.png");
        
        if (logoTex) {
            logoSprite = new graphics::Sprite(logoTex);
            
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
        if (logoSprite) {
            delete logoSprite;
            logoSprite = nullptr;
        }
    }
    
    gameStates::StateAction update() override {
        timer += GameTime::getInstance()->getDeltaTime();
        
        // Gentle rotation animation
        if (logoSprite) {
            logoSprite->setRotation(timer * 5.0f); // Slow rotation
        }
        
        // Auto-transition after 3 seconds (for demo)
        if (timer >= 3.0f) {
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
            core->drawSprite(logoSprite);
        }
    }
    
private:
    float timer;
    graphics::Sprite* logoSprite;
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
        , cameraX(0)
        , cameraY(0)
        , showDemo(0)
    {}
    
    void enter() override {
        std::cout << "Entering Ingame State" << std::endl;
        
        auto* texMgr = assets::TextureManager::getInstance();
        auto* inputMgr = input::InputManager::getInstance();
        auto* soundMgr = audio::SoundManager::getInstance();
        
        // Initialize sound system
        soundMgr->init();
        soundMgr->setMediaPath("media/");
        
        // Create mouse cursor sprite
        SDL_Texture* mouseTex = texMgr->getTexture("ui/mouse.png");
        if (mouseTex) {
            mouseSprite = new graphics::Sprite(mouseTex);
        }
        
        // Initialize tile system demo
        tileRegistry = new world::TileRegistry();
        tileRegistry->init(texMgr);
        
        // Register some demo tiles using available UI textures
        tileRegistry->registerTile("Ground", "ui/GroundTile.png", 0, 0, 64, 64);
        
        // Create a simple tile map
        tileMap = new world::TileMap();
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
        entityManager = new entities::EntityManager();
        
        // Create player
        player = new entities::Player();
        player->setPosition(400, 300);
        player->setMoveSpeed(200.0f);
        entityManager->addEntity(player);
        
        // Spawn some zombies
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distX(100, 700);
        std::uniform_real_distribution<float> distY(100, 500);
        
        for (int i = 0; i < 5; i++) {
            auto* zombie = new entities::Zombie();
            zombie->setPosition(distX(gen), distY(gen));
            zombie->setMoveSpeed(80.0f);
            zombie->setAggroRange(200.0f);
            entityManager->addEntity(zombie);
        }
        
        // Initialize collision system
        collisionSystem = new physics::CollisionSystem();
        
        std::cout << "Gameplay systems initialized" << std::endl;
        std::cout << "Controls:" << std::endl;
        std::cout << "  WASD - Move player" << std::endl;
        std::cout << "  Arrow Keys - Pan camera" << std::endl;
        std::cout << "  ESC - Quit" << std::endl;
    }
    
    void exit() override {
        std::cout << "Exiting Ingame State" << std::endl;
        
        if (mouseSprite) {
            delete mouseSprite;
            mouseSprite = nullptr;
        }
        
        if (collisionSystem) {
            delete collisionSystem;
            collisionSystem = nullptr;
        }
        
        if (entityManager) {
            delete entityManager;
            entityManager = nullptr;
        }
        
        if (tileMap) {
            delete tileMap;
            tileMap = nullptr;
        }
        
        if (tileRegistry) {
            delete tileRegistry;
            tileRegistry = nullptr;
        }
        
        player = nullptr; // EntityManager owns this
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
        
        // Player input (WASD)
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
                auto* entity = entityManager->getEntity(i);
                auto* zombie = dynamic_cast<entities::Zombie*>(entity);
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
                auto* entity = entityManager->getEntity(i);
                auto* zombie = dynamic_cast<entities::Zombie*>(entity);
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
            tileMap->render(renderer, tileRegistry, 
                          cameraX, cameraY,
                          core->getScreenWidth(), 
                          core->getScreenHeight());
        }
        
        // Render all entities (with camera offset)
        if (entityManager) {
            for (int i = 0; i < entityManager->getEntityCount(); i++) {
                auto* entity = entityManager->getEntity(i);
                if (entity) {
                    float posX = entity->getX();
                    float posY = entity->getY();
                    
                    // Create temporary sprite for visual representation
                    // (In real game, entities would have their own sprites)
                    if (auto* playerEntity = dynamic_cast<entities::Player*>(entity)) {
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
                    } else if (auto* zombie = dynamic_cast<entities::Zombie*>(entity)) {
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
        
        // Draw UI overlay
        core->drawFilledRect(0, 0, 
            static_cast<float>(core->getScreenWidth()), 80, 
            0, 0, 0, 180);
        
        // Draw time of day indicator bar
        float timePercent = gameTime->getTimeOfDay() / 24.0f;
        int barWidth = static_cast<int>(200 * timePercent);
        core->drawFilledRect(10, 10, static_cast<float>(barWidth), 30, 255, 255, 0, 255);
        core->drawRect(10, 10, 200, 30, 255, 255, 255, 255);
        
        // Player status
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
        
        // Entity count
        if (entityManager) {
            int aliveZombies = 0;
            for (int i = 0; i < entityManager->getEntityCount(); i++) {
                auto* entity = entityManager->getEntity(i);
                auto* zombie = dynamic_cast<entities::Zombie*>(entity);
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
            core->drawSprite(mouseSprite);
        }
    }
    
private:
    graphics::Sprite* mouseSprite;
    world::TileMap* tileMap;
    world::TileRegistry* tileRegistry;
    entities::EntityManager* entityManager;
    physics::CollisionSystem* collisionSystem;
    entities::Player* player;
    int cameraX, cameraY;
    int showDemo;
};

GameWindow::GameWindow()
    : lastFrame(0)
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
    
    initialized = true;
    std::cout << "GameWindow initialized successfully" << std::endl;
    std::cout << "Media path: " << assets::TextureManager::getInstance()->getMediaPath() << std::endl;
    return true;
}

void GameWindow::initStates() {
    // Add game states
    stateMachine.addState(std::make_unique<MainMenuState>());
    stateMachine.addState(std::make_unique<IngameState>());
    
    // Loop back to main menu if we exit all states
    stateMachine.setLooping(true);
    stateMachine.setLoopToState(1); // Loop to ingame (skip menu after first time)
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
