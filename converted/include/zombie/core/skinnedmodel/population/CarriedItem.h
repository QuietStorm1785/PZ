#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class CarriedItem {
public:
  std::string m_Model;
  std::string m_Texture;
  bool m_TwoHanded;
  std::string m_WeaponType;
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
