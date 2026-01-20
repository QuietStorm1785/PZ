#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlRootElement.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimTransition {
public:
    std::string m_Target;
    std::string m_AnimName;
    float m_SyncAdjustTime = 0.0F;
    float m_blendInTime = float.POSITIVE_INFINITY;
    float m_blendOutTime = float.POSITIVE_INFINITY;
    float m_speedScale = float.POSITIVE_INFINITY;
   public List<AnimCondition> m_Conditions = std::make_unique<std::vector<>>();
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
