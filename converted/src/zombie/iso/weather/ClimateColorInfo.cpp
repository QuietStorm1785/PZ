#include "zombie/iso/weather/ClimateColorInfo.h"

namespace zombie {
namespace iso {
namespace weather {

public ClimateColorInfo::ClimateColorInfo() {
 // TODO: Implement ClimateColorInfo
 return nullptr;
}

public ClimateColorInfo::ClimateColorInfo(float r, float g, float b, float a) {
 // TODO: Implement ClimateColorInfo
 return nullptr;
}

public ClimateColorInfo::ClimateColorInfo(float r, float g, float b, float a, float r2, float g2, float b2, float a2) {
 // TODO: Implement ClimateColorInfo
 return nullptr;
}

void ClimateColorInfo::setInterior(Color other) {
 // TODO: Implement setInterior
}

void ClimateColorInfo::setInterior(float r, float g, float b, float a) {
 // TODO: Implement setInterior
}

Color ClimateColorInfo::getInterior() {
 // TODO: Implement getInterior
 return nullptr;
}

void ClimateColorInfo::setExterior(Color other) {
 // TODO: Implement setExterior
}

void ClimateColorInfo::setExterior(float r, float g, float b, float a) {
 // TODO: Implement setExterior
}

Color ClimateColorInfo::getExterior() {
 // TODO: Implement getExterior
 return nullptr;
}

void ClimateColorInfo::setTo(ClimateColorInfo other) {
 // TODO: Implement setTo
}

ClimateColorInfo ClimateColorInfo::interp(ClimateColorInfo to, float t, ClimateColorInfo result) {
 // TODO: Implement interp
 return nullptr;
}

void ClimateColorInfo::scale(float val) {
 // TODO: Implement scale
}

ClimateColorInfo ClimateColorInfo::interp(ClimateColorInfo source, ClimateColorInfo target, float t, ClimateColorInfo resultColorInfo) {
 // TODO: Implement interp
 return nullptr;
}

void ClimateColorInfo::write(ByteBuffer output) {
 // TODO: Implement write
}

void ClimateColorInfo::read(ByteBuffer input) {
 // TODO: Implement read
}

void ClimateColorInfo::save(DataOutputStream output) {
 // TODO: Implement save
}

void ClimateColorInfo::load(DataInputStream input, int worldVersion) {
 // TODO: Implement load
}

bool ClimateColorInfo::writeColorInfoConfig() {
 // TODO: Implement writeColorInfoConfig
 return false;
}

void ClimateColorInfo::writeSeasonColor(int int0, ClimateColorInfo climateColorInfo, const std::string& string2, const std::string& string0, const std::string& string1) {
 // TODO: Implement writeSeasonColor
}

void ClimateColorInfo::writeColor(int int0, ClimateColorInfo climateColorInfo) {
 // TODO: Implement writeColor
}

void ClimateColorInfo::write(int int0, const std::string& string1) {
 // TODO: Implement write
}

void ClimateColorInfo::write(const std::string& string) {
 // TODO: Implement write
}

} // namespace weather
} // namespace iso
} // namespace zombie
