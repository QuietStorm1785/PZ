#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Talker {
public:
 virtual ~Talker() = default;
 bool IsSpeaking();

 void Say(std::string_view line);

 std::string getSayLine();

 std::string getTalkerType();
}
} // namespace characters
} // namespace zombie
