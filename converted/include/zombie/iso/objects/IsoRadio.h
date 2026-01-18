#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/sprite/IsoSprite.h"

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoRadio : public IsoWaveSignal {
public:
 public IsoRadio(IsoCell cell) {
 super(cell);
 }

 public IsoRadio(IsoCell cell, IsoGridSquare sq, IsoSprite spr) {
 super(cell, sq, spr);
 }

 std::string getObjectName() {
 return "Radio";
 }

 void init(bool boolean0) {
 super.init(boolean0);
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
