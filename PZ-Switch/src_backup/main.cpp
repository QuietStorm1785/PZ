#include "GameWindow.h"
#include "Core.h"
#include "Config.h"
#include "TextureManager.h"
#include "SpriteAnimation.h"
#include "InputManager.h"
#include "SoundManager.h"
#include <iostream>
#include <unordered_map>
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    std::cout << "=== Project Zomboid C++ Port ===" << std::endl;
    std::cout << "Target Platform: Nintendo Switch (SDL2)" << std::endl;
    std::cout << "Build: " << __DATE__ << " " << __TIME__ << std::endl;
    std::cout << "====================================" << std::endl;
    
    // Load Switch configuration (defaults baked into struct)
    zombie::config::SwitchConfig switchConfig;
    zombie::config::loadSwitchConfig("config/switch_config.cfg", switchConfig);

    // Load options and controller keys
    zombie::config::loadOptionsConfig("config/Options.ini", zombie::config::gOptionsConfig);
    zombie::config::loadKeysConfig("config/keys.ini", zombie::config::gKeysConfig);

    // Parse command line arguments (override config values)
    int width = switchConfig.width;
    int height = switchConfig.height;
    bool fullscreen = switchConfig.fullscreen;
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        
        if (arg == "-width" && i + 1 < argc) {
            width = std::atoi(argv[++i]);
        } else if (arg == "-height" && i + 1 < argc) {
            height = std::atoi(argv[++i]);
        } else if (arg == "-fullscreen") {
            fullscreen = true;
        } else if (arg == "-debug") {
            zombie::core::Core::bDebug = true;
        }
    }
    
    // Create game window
    zombie::GameWindow gameWindow;
    
    // Initialize
    if (!gameWindow.init(width, height, fullscreen, switchConfig.mediaPath)) {
        std::cerr << "Failed to initialize game" << std::endl;
        return 1;
    }

    // Configure media path again post-init (TextureManager is available now)
    zombie::assets::TextureManager::getInstance()->setMediaPath(switchConfig.mediaPath);
    // Configure controller bindings and tuning
    zombie::input::InputManager::getInstance()->configureFromSwitchConfig(switchConfig);

    // Apply key bindings from keys.ini (overrides defaults)
    for (const auto& kv : zombie::config::gKeysConfig.bindings) {
        zombie::input::InputManager::getInstance()->rebindAction(kv.first, kv.second);
    }

    // Apply audio settings from Options.ini
    auto* snd = zombie::audio::SoundManager::getInstance();
    snd->setMasterVolume(zombie::config::gOptionsConfig.masterVolume);
    snd->setMusicVolume(zombie::config::gOptionsConfig.musicVolume);
    snd->setSoundVolume(zombie::config::gOptionsConfig.sfxVolume);

    // Apply vsync preference
    zombie::core::Core::getInstance()->setVSyncEnabled(zombie::config::gOptionsConfig.vsync);

    // Preload texture packs defined in config (optional atlas build)
    for (const auto& packName : switchConfig.texturePacks) {
        std::unordered_map<std::string, zombie::graphics::AnimatedSprite*> sprites;
        if (zombie::assets::TextureManager::getInstance()->loadTexturePack(
                packName,
                sprites,
                switchConfig.buildPackAtlas,
                switchConfig.atlasMaxWidth,
                switchConfig.atlasMaxHeight)) {
        }
    }
    
    // Run main game loop
    gameWindow.run();
    
    // Cleanup (handled by destructors)
    std::cout << "Game exited cleanly" << std::endl;
    
    return 0;
}
