#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoGridSquare.h"

namespace zombie {
namespace chat {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Turbo
 */
class ChatElementOwner {
public:
 virtual ~ChatElementOwner() = default;
 float getX();

 float getY();

 float getZ();

 IsoGridSquare getSquare();
}
} // namespace chat
} // namespace zombie
