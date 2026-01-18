#include "GameTime.h"
#include <SDL2/SDL.h>
#include <algorithm>

namespace zombie {

GameTime* GameTime::instance = nullptr;

GameTime* GameTime::getInstance() {
 if (!instance) {
 instance = new GameTime();
 }
 return instance;
}

GameTime::GameTime()
 : timeOfDay(13.0f)
 , day(22)
 , month(1)
 , nightTint(0.0f)
 , ambient(0.9f)
 , ambientMax(0.6f)
 , ambientMin(0.0f)
 , fpsMultiplier(1.0f)
 , multiplier(1.0f)
 , deltaTime(0.0f)
 , lastUpdate(0.0f)
{
}

void GameTime::update(bool sleeping) {
 // Calculate delta time
 float currentTime = SDL_GetTicks() / 1000.0f;
 deltaTime = currentTime - lastUpdate;
 lastUpdate = currentTime;
 
 // Clamp delta time to prevent huge jumps
 deltaTime = std::min(deltaTime, 0.1f);
 
 // Update time of day
 // Game runs at accelerated time (configurable multiplier)
 float timeIncrement = deltaTime * multiplier * fpsMultiplier;
 
 if (sleeping) {
 // Speed up time when sleeping
 timeIncrement *= 60.0f; // 60x faster
 }
 
 timeOfDay += timeIncrement / 60.0f; // Convert to hours
 
 // Handle day rollover
 if (timeOfDay >= 24.0f) {
 timeOfDay -= 24.0f;
 day++;
 
 // Handle month rollover (simplified)
 if (day >= 30) {
 day = 0;
 month++;
 if (month > 12) {
 month = 1;
 }
 }
 }
 
 // Calculate night tint (0.0 at night, 1.0 during day)
 // Sunrise around 6am, sunset around 8pm
 if (timeOfDay < 6.0f) {
 // Night (12am - 6am)
 nightTint = 0.0f;
 } else if (timeOfDay < 8.0f) {
 // Sunrise (6am - 8am)
 nightTint = (timeOfDay - 6.0f) / 2.0f;
 } else if (timeOfDay < 18.0f) {
 // Day (8am - 6pm)
 nightTint = 1.0f;
 } else if (timeOfDay < 20.0f) {
 // Sunset (6pm - 8pm)
 nightTint = 1.0f - ((timeOfDay - 18.0f) / 2.0f);
 } else {
 // Night (8pm - 12am)
 nightTint = 0.0f;
 }
 
 // Calculate ambient light
 ambient = ambientMin + (ambientMax - ambientMin) * nightTint;
}

} // namespace zombie
