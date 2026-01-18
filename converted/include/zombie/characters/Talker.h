#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class Talker {
public:
 virtual ~Talker() = default;
 bool IsSpeaking();

 void Say(const std::string& line);

 std::string getSayLine();

 std::string getTalkerType();
}
} // namespace characters
} // namespace zombie
