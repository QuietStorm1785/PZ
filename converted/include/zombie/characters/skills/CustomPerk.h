#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {
namespace skills {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class CustomPerk {
public:
 std::string m_id;
 std::string m_parent = "None";
 std::string m_translation;
 bool m_bPassive = false;
 public int[] m_xp = new int[10];

 public CustomPerk(const std::string& string) {
 this->m_id = string;
 }
}
} // namespace skills
} // namespace characters
} // namespace zombie
