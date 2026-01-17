#pragma once
#include "GameStateMachine.h"
#include "NetworkManager.h"
#include <SDL2/SDL.h>
#include <memory>

namespace zombie {

// Forward declarations
namespace network { class NetworkServer; class NetworkClient; }

/**
 * Main game window and loop management
 * Converted from zombie.GameWindow
 */
class GameWindow {
public:
    GameWindow();
    ~GameWindow();
    
    // Initialize the game
    bool init(int width, int height, bool fullscreen);
    
    // Main game loop
    void run();
    
    // Frame management
    void logic();
    void render();
    
    // Timing
    static Uint64 getTime();
    void updateFPS();
    
    // FPS tracking
    float getAverageFPS() const { return average10FPS; }
    
    // State machine access
    gameStates::GameStateMachine& getStateMachine() { return stateMachine; }
    
    // Exit request
    void requestClose() { closeRequested = true; }
    bool isCloseRequested() const { return closeRequested; }
    
    // Version info
    static constexpr const char* VERSION = "0.2.0q-cpp";
    
private:
    void initStates();
    bool initNetworking();
    
    gameStates::GameStateMachine stateMachine;

    // Networking
    std::unique_ptr<network::NetworkServer> networkServer;
    std::unique_ptr<network::NetworkClient> networkClient;
    class IngameState* ingameState; // Non-owning pointer to live state for network hooks
    bool networkReady;
    
    // Timing
    Uint64 lastFrame;
    Uint64 lastFPS;
    float average10FPS;
    float last10[100];
    int last10Index;
    Uint64 last;
    
    bool closeRequested;
    bool initialized;
    
    // FPS cap (60 FPS target)
    static constexpr int TARGET_FPS = 60;
    static constexpr Uint32 FRAME_TIME = 1000 / TARGET_FPS;
};

} // namespace zombie
