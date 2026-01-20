#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {

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
