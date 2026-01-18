#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlRootElement.h"

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class TriggerXmlFile {
public:
 std::string outfitName;
 std::string clothingItemGUID;
 bool isMale;
}
} // namespace characters
} // namespace zombie
