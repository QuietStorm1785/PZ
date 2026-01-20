#include <string>
#include "zombie\iso\weather/ThunderStorm.h"

namespace zombie {
namespace iso {
namespace weather {

public ThunderStorm::ThunderStorm(ClimateManager var1) {
    // TODO: Implement ThunderStorm
    return nullptr;
}

ThunderEvent ThunderStorm::getFreeEvent() {
    // TODO: Implement getFreeEvent
    return nullptr;
}

ThunderCloud ThunderStorm::getFreeCloud() {
    // TODO: Implement getFreeCloud
    return nullptr;
}

ThunderCloud ThunderStorm::getCloud(int var1) {
    // TODO: Implement getCloud
    return nullptr;
}

bool ThunderStorm::HasActiveThunderClouds() {
    // TODO: Implement HasActiveThunderClouds
    return false;
}

void ThunderStorm::noise(const std::string& var1) {
    // TODO: Implement noise
}

void ThunderStorm::stopAllClouds() {
    // TODO: Implement stopAllClouds
}

void ThunderStorm::stopCloud(int var1) {
    // TODO: Implement stopCloud
}

float ThunderStorm::addToAngle(float var0, float var1) {
    // TODO: Implement addToAngle
    return 0;
}

int ThunderStorm::getMapDiagonal() {
    // TODO: Implement getMapDiagonal
    return 0;
}

void ThunderStorm::startThunderCloud(float var1, float var2, float var3, float var4, float var5, double var6, bool var8) {
    // TODO: Implement startThunderCloud
}

ThunderCloud ThunderStorm::startThunderCloud(float var1, float var2, float var3, float var4, float var5, double var6, bool var8, float var9) {
    // TODO: Implement startThunderCloud
    return nullptr;
}

void ThunderStorm::update(double var1) {
    // TODO: Implement update
}

void ThunderStorm::applyLightningForPlayer(PlayerRenderSettings var1, int var2, IsoPlayer var3) {
    // TODO: Implement applyLightningForPlayer
}

bool ThunderStorm::isModifyingNight() {
    // TODO: Implement isModifyingNight
    return false;
}

void ThunderStorm::triggerThunderEvent(int var1, int var2, bool var3, bool var4, bool var5) {
    // TODO: Implement triggerThunderEvent
}

void ThunderStorm::writeNetThunderEvent(ByteBuffer var1) {
    // TODO: Implement writeNetThunderEvent
}

void ThunderStorm::readNetThunderEvent(ByteBuffer var1) {
    // TODO: Implement readNetThunderEvent
}

void ThunderStorm::enqueueThunderEvent(int var1, int var2, bool var3, bool var4, bool var5) {
    // TODO: Implement enqueueThunderEvent
}

int ThunderStorm::GetDistance(int var1, int var2, int var3, int var4) {
    // TODO: Implement GetDistance
    return 0;
}

void ThunderStorm::save(DataOutputStream var1) {
    // TODO: Implement save
}

void ThunderStorm::load(DataInputStream var1) {
    // TODO: Implement load
}

} // namespace weather
} // namespace iso
} // namespace zombie
