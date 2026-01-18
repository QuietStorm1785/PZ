#pragma once
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace profiling {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TriggerGameProfilerFile {
public:
 bool discard;
 bool isRecording;
}
} // namespace profiling
} // namespace core
} // namespace zombie
