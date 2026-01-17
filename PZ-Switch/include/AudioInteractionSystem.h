#pragma once
#include <string>
#include <memory>
#include <unordered_map>

class IsoObject;
class SoundManager;

/**
 * AudioInteractionSystem - Trigger sounds on object interactions
 * 
 * Provides a simple system to hook audio playback to object interactions.
 * Each object type can have associated sound effects that play on interaction.
 * 
 * Example:
 *   auto audio = AudioInteractionSystem::getInstance();
 *   audio->registerInteractionSound("furniture", "furniture_interact.wav");
 *   audio->playInteractionSound("furniture", playerX, playerY);
 */
class AudioInteractionSystem {
public:
    static AudioInteractionSystem* getInstance();

    /**
     * Register a sound effect for an object type interaction
     * @param objectType - Type of object (e.g., "furniture", "container", "door")
     * @param soundPath - Path to sound file relative to media/sound/
     */
    void registerInteractionSound(const std::string& objectType, const std::string& soundPath);

    /**
     * Register a sound effect for a specific object action
     * @param objectType - Type of object
     * @param actionName - Action name (e.g., "open", "close")
     * @param soundPath - Path to sound file
     */
    void registerActionSound(const std::string& objectType, const std::string& actionName, const std::string& soundPath);

    /**
     * Play interaction sound for object type
     * @param objectType - Type of object interacted with
     * @param x, y - World position for spatial audio
     * @return true if sound played successfully
     */
    bool playInteractionSound(const std::string& objectType, float x, float y);

    /**
     * Play sound for specific object action
     * @param objectType - Type of object
     * @param actionName - Specific action (e.g., "open", "close", "break")
     * @param x, y - World position
     */
    bool playObjectSound(const std::string& objectType, const std::string& actionName, float x, float y);

    /**
     * Register container-specific sounds
     */
    void registerContainerSounds();

    /**
     * Register furniture-specific sounds
     */
    void registerFurnitureSounds();

    /**
     * Register weapon-specific sounds
     */
    void registerWeaponSounds();

    /**
     * Clear all registered sounds (for testing/reset)
     */
    void clearSounds();

private:
    AudioInteractionSystem();
    ~AudioInteractionSystem();

    /**
     * Initialize default sound registry
     */
    void initializeDefaultSounds();

    // Map: objectType -> soundPath
    std::unordered_map<std::string, std::string> interactionSounds;
    
    // Map: objectType -> (actionName -> soundPath)
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> actionSounds;

    static AudioInteractionSystem* instance;
};
