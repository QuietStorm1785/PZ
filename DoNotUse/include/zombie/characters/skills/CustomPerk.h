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

class CustomPerk {
public:
    std::string m_id;
    std::string m_parent = "None";
    std::string m_translation;
    bool m_bPassive = false;
   public const int[] m_xp = new int[10];

    public CustomPerk(const std::string& var1) {
      this.m_id = var1;
   }
}
} // namespace skills
} // namespace characters
} // namespace zombie
