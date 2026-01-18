#include "zombie/iso/objects/RainManager.h"

namespace zombie {
namespace iso {
namespace objects {

void RainManager::reset() {
 // TODO: Implement reset
}

void RainManager::AddRaindrop(IsoRaindrop NewRaindrop) {
 // TODO: Implement AddRaindrop
}

void RainManager::AddRainSplash(IsoRainSplash NewRainSplash) {
 // TODO: Implement AddRainSplash
}

void RainManager::AddSplashes() {
 // TODO: Implement AddSplashes
}

void RainManager::RemoveRaindrop(IsoRaindrop DyingRaindrop) {
 // TODO: Implement RemoveRaindrop
}

void RainManager::RemoveRainSplash(IsoRainSplash DyingRainSplash) {
 // TODO: Implement RemoveRainSplash
}

void RainManager::SetPlayerLocation(int playerIndex,
 IsoGridSquare PlayerCurrentSquare) {
 // TODO: Implement SetPlayerLocation
}

bool RainManager::isRaining() {
 // TODO: Implement isRaining
 return false;
}

void RainManager::stopRaining() {
 // TODO: Implement stopRaining
}

void RainManager::startRaining() {
 // TODO: Implement startRaining
}

void RainManager::StartRaindrop(IsoCell cell, IsoGridSquare gridSquare,
 bool CanSee) {
 // TODO: Implement StartRaindrop
}

void RainManager::StartRainSplash(IsoCell cell, IsoGridSquare gridSquare,
 bool CanSee) {
 // TODO: Implement StartRainSplash
}

void RainManager::Update() {
 // TODO: Implement Update
}

void RainManager::UpdateServer() {
 // TODO: Implement UpdateServer
}

void RainManager::setRandRainMax(int pRandRainMax) {
 // TODO: Implement setRandRainMax
}

void RainManager::setRandRainMin(int pRandRainMin) {
 // TODO: Implement setRandRainMin
}

bool RainManager::inBounds(IsoGridSquare sq) {
 // TODO: Implement inBounds
 return false;
}

void RainManager::RemoveAllOn(IsoGridSquare sq) {
 // TODO: Implement RemoveAllOn
}

float RainManager::getRainIntensity() {
 // TODO: Implement getRainIntensity
 return 0;
}

void RainManager::removeAll() {
 // TODO: Implement removeAll
}

bool RainManager::interruptSleep(IsoPlayer player) {
 // TODO: Implement interruptSleep
 return false;
}

} // namespace objects
} // namespace iso
} // namespace zombie
