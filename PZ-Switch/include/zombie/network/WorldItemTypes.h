#pragma once
#include "zombie/iso/IsoObject.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldItemTypes {
public:
 static IsoObject createFromBuffer(ByteBuffer byteBuffer) {
 void *object = nullptr;
 return IsoObject.factoryFromFileInput(nullptr, byteBuffer);
 }
}
} // namespace network
} // namespace zombie
