#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/ImmutableColor.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class Outfit {
public:
    ImmutableColor m_hairColor;
    std::string m_maleHairName;
    std::string m_femaleHairName;
    std::string m_beardName;
    ImmutableColor m_topTint;
    ImmutableColor m_pantsTint;
    float m_pantsHue;
    bool m_hasTop;
    bool m_hasTShirt;
    bool m_hasTShirtDecal;
    std::string m_topTexture;
    std::string m_pantsTexture;
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
