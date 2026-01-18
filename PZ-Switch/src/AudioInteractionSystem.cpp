#include "AudioInteractionSystem.h"
#include "SoundManager.h"
#include "IsoObject.h"

AudioInteractionSystem* AudioInteractionSystem::instance = nullptr;

AudioInteractionSystem* AudioInteractionSystem::getInstance() {
 if (!instance) {
 instance = new AudioInteractionSystem();
 instance->initializeDefaultSounds();
 }
 return instance;
}

AudioInteractionSystem::AudioInteractionSystem() {}

AudioInteractionSystem::~AudioInteractionSystem() {}

void AudioInteractionSystem::registerInteractionSound(const std::string& objectType, const std::string& soundPath) {
 interactionSounds[objectType] = soundPath;
}

void AudioInteractionSystem::registerActionSound(const std::string& objectType, const std::string& actionName, const std::string& soundPath) {
 actionSounds[objectType][actionName] = soundPath;
}

bool AudioInteractionSystem::playInteractionSound(const std::string& objectType, float x, float y) {
 (void)x; (void)y; // Spatial audio not yet implemented
 auto it = interactionSounds.find(objectType);
 if (it != interactionSounds.end()) {
 auto soundManager = zombie::audio::SoundManager::getInstance();
 if (soundManager) {
 soundManager->playSound(it->second);
 return true;
 }
 }
 return false;
}

bool AudioInteractionSystem::playObjectSound(const std::string& objectType, const std::string& actionName, float x, float y) {
 (void)x; (void)y; // Spatial audio not yet implemented
 auto typeIt = actionSounds.find(objectType);
 if (typeIt != actionSounds.end()) {
 auto actionIt = typeIt->second.find(actionName);
 if (actionIt != typeIt->second.end()) {
 auto soundManager = zombie::audio::SoundManager::getInstance();
 if (soundManager) {
 soundManager->playSound(actionIt->second);
 return true;
 }
 }
 }
 return false;
}

void AudioInteractionSystem::registerContainerSounds() {
 registerActionSound("container", "open", "media/sound/container_open.wav");
 registerActionSound("container", "close", "media/sound/container_close.wav");
 registerActionSound("container", "pickup", "media/sound/item_pickup.wav");
 registerActionSound("container", "drop", "media/sound/item_drop.wav");
}

void AudioInteractionSystem::registerFurnitureSounds() {
 registerActionSound("furniture", "activate", "media/sound/furniture_activate.wav");
 registerActionSound("furniture", "push", "media/sound/furniture_push.wav");
 registerActionSound("furniture", "destroy", "media/sound/furniture_destroy.wav");
}

void AudioInteractionSystem::registerWeaponSounds() {
 registerActionSound("weapon", "equip", "media/sound/weapon_equip.wav");
 registerActionSound("weapon", "fire", "media/sound/weapon_fire.wav");
 registerActionSound("weapon", "reload", "media/sound/weapon_reload.wav");
}

void AudioInteractionSystem::initializeDefaultSounds() {
 // Register default interaction sounds for common object types
 registerInteractionSound("door", "media/sound/door_interact.wav");
 registerInteractionSound("window", "media/sound/window_interact.wav");
 registerInteractionSound("chest", "media/sound/chest_open.wav");
 
 // Register action-specific sounds
 registerContainerSounds();
 registerFurnitureSounds();
 registerWeaponSounds();
}

void AudioInteractionSystem::clearSounds() {
 interactionSounds.clear();
 actionSounds.clear();
}
