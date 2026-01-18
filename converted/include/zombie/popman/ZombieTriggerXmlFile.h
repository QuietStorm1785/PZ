#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlRootElement.h"

namespace zombie {
namespace popman {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ZombieTriggerXmlFile {
public:
 int spawnHorde = 0;
 bool setDebugLoggingEnabled = false;
 bool bDebugLoggingEnabled = false;
}
} // namespace popman
} // namespace zombie
