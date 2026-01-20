#include <string>
#include "zombie\iso\objects/IsoRaindrop.h"

namespace zombie {
namespace iso {
namespace objects {

bool IsoRaindrop::Serialize() {
    // TODO: Implement Serialize
    return false;
}

public IsoRaindrop::IsoRaindrop(IsoCell var1, IsoGridSquare var2, bool var3) {
    // TODO: Implement IsoRaindrop
    return nullptr;
}

bool IsoRaindrop::HasTooltip() {
    // TODO: Implement HasTooltip
    return false;
}

std::string IsoRaindrop::getObjectName() {
    // TODO: Implement getObjectName
    return "";
}

bool IsoRaindrop::TestCollide(IsoMovingObject var1, IsoGridSquare var2) {
    // TODO: Implement TestCollide
    return false;
}

VisionResult IsoRaindrop::TestVision(IsoGridSquare var1, IsoGridSquare var2) {
    // TODO: Implement TestVision
    return nullptr;
}

void IsoRaindrop::ChangeTintMod(ColorInfo var1) {
    // TODO: Implement ChangeTintMod
}

void IsoRaindrop::update() {
    // TODO: Implement update
}

void IsoRaindrop::Reset(IsoGridSquare var1, bool var2) {
    // TODO: Implement Reset
}

} // namespace objects
} // namespace iso
} // namespace zombie
