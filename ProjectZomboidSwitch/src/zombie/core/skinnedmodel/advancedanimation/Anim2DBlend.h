#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlAttribute.h"
#include "javax/xml/bind/annotation/XmlID.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class Anim2DBlend {
public:
    std::string m_AnimName = "";
    float m_XPos = 0.0F;
    float m_YPos = 0.0F;
    float m_SpeedScale = 1.0F;
    std::string m_referenceID;
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
